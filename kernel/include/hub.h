/**
 * Kernel HUB definitions.
 **/

#include <ktypes.h>

kstatus_t hub_register(uuid_t *uuid, void *interface);
kstatus_t hub_find(uuid_t *uuid, void **interface);

