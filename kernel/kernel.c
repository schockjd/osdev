#include <ktypes.h>
#include <kutils.h>
#include <hub.h>

#include <drivers/vga.h>

// Sanity check
#if defined(__linux__)
#error "You are not using a cross-compiler!"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with ix86-elf compiler"
#endif

void kernel_main() {
    hub_init();
    vga_initialize();
}
