#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#include <ktypes.h>
#include <hub.h>

// Sanity check
#if defined(__linux__)
#error "You are not using a cross-compiler!"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with ix86-elf compiler"
#endif



/**
 * Kernel Hub routines
 **/
kstatus_t hub_register(uuid_t uuid, void *interface) {
    kstatus_t status = 0;

    return status;
}

kstatus_t hub_find(uuid_t uuid, void **interface) {
    kstatus_t status = ENOTFOUND;
    return status;
}   

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
}
