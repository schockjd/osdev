#include <ktypes.h>
#include <kutils.h>
#include <hub.h>

// Sanity check
#if defined(__linux__)
#error "You are not using a cross-compiler!"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with ix86-elf compiler"
#endif


typedef struct hubentry_t {
    bool                inUse;
    uuid_t              uuid;
    void                *interface;
    struct hubentry_t   *next;
} hubentry_t;

// Hub Storage
hubentry_t  hub_storage[4096];

// Hub List Heads
hubentry_t *hub_heads[64];


kstatus_t hub_init() {
    memset(&hub_storage, 0, sizeof(hub_storage));
    memset(&hub_heads, 0, sizeof(hub_heads));
    return 0;
}
kstatus_t get_free_hub(hubentry_t **hub) {
    size_t hubIdx;
    for (hubIdx = 0; hubIdx < 4096; hubIdx++) {
        if (!hub_storage[hubIdx].inUse) {
            hub_storage[hubIdx].inUse = true;
            *hub = &hub_storage[hubIdx];
            return 0;
        }
    }
    return EINSUFFICIENT;
}

/**
 * Kernel Hub routines
 **/
kstatus_t hub_register(uuid_t *uuid, void *interface) {
    kstatus_t status;
    uint8_t headidx;
    hubentry_t *hub;
    
    headidx = *uuid[0] & 0x3f;
    hub = hub_heads[headidx];
    
    if (hub == NULL) {
        status = get_free_hub(&hub);
        if (ERROR(status)) {
            return status;
        }
        hub_heads[headidx]=hub;
    } else {
        while (hub->next != NULL) {
            hub = hub->next;
        }
        status = get_free_hub(&hub->next);
        if (ERROR(status)) {
            return status;
        }
        hub = hub->next;
    }
    memcpy(&hub->uuid, uuid, sizeof(uuid_t));
    hub->interface = interface;

    return 0;
}

kstatus_t hub_find(uuid_t *uuid, void **interface) {
    uint8_t headidx;
    hubentry_t *hub;
 
    headidx = *uuid[0] & 0x3f;
    hub = hub_heads[headidx];

    if (hub == NULL) {
        return ENOTFOUND;
    }
    while( hub != NULL) {
        if (memcmp(uuid, hub->uuid, sizeof(uuid_t)) == 0) {
            *interface = hub->interface;
            return 0;
        }
        hub = hub->next;
    }
    return ENOTFOUND;
}   


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
    hub_init();
}
