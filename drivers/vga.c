#include <ktypes.h>
#include <kutils.h>
#include <hub.h>

#include <interfaces/dbgout.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

size_t row;
size_t col;
uint8_t color;
uint16_t *v_buffer;

kstatus_t setcolor(dbgout_color_t fg, dbgout_color_t bg) {
    color = fg | bg << 4;
    return 0;
}

uint16_t make_vgaentry(char c, uint8_t color) {
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

void vga_init()
{
    row = 0;
    col = 0;
    color = setcolor(COLOR_LIGHT_GREY, COLOR_BLACK);
    v_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            v_buffer[index] = make_vgaentry(' ', color);
        }
    }
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    v_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c) {
    terminal_putentryat(c, color, col, row);
    if (++col == VGA_WIDTH) {
        col = 0;
        if (++row == VGA_HEIGHT) {
            row = 0;
        }
    }
}

kstatus_t writestr(const char* str) {
    size_t datalen = strlen(str);
    for (size_t i = 0; i < datalen; i++) {
        terminal_putchar(str[i]);
    }
    return 0;
}

kstatus_t clrscr() {
    for (size_t clr_row = 0; clr_row < VGA_HEIGHT; clr_row++) {
        for (size_t clr_col = 0; clr_col < VGA_WIDTH; clr_col++) {
            terminal_putentryat(' ', color, col, row);
        }
    }
    return 0;
}

DebugOutI dbgout_iface = {
    setcolor,
    writestr,
    clrscr,
};

kstatus_t vga_initialize() {
    return hub_register(&DebugOutUUID, &dbgout_iface);
}
