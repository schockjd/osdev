#include <ktypes.h>
#include <kutils.h>
#include <hub.h>

#include <drivers/vga.h>
#include <interfaces/dbgout.h>

// Sanity check
#if defined(__linux__)
#error "You are not using a cross-compiler!"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with ix86-elf compiler"
#endif

void kernel_main() {
    DebugOutI *dout;

    hub_init();
    vga_initialize();
    
    hub_find(&DebugOutUUID, (void **)&dout);

    dout->writestr("Hello, Kernel World!");

}

