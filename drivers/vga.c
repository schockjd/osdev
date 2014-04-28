#include <ktypes.h>
#include <kutils.h>
#include <hub.h>

#include <interfaces/dbgout.h>

kstatus_t setcolor(dbgout_color_t fg, dbgout_color_t bg) {
    return 0;
}

kstatus_t writestr(const char* str) {
    return 0;
}

kstatus_t clrscr() {
    return 0;
}

DebugOutI dbgout_iface = {
    setcolor,
    writestr,
    clrscr,
};

kstatus_t initialize() {
    uuid_t dbgout_uuid = DebugOut_UUID;
    return hub_register(&dbgout_uuid, &dbgout_iface);
}