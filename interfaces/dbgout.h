#include <ktypes.h>

//Debug-Out UUID
//4cd1214d-80de-4ad9-b3b4-ca8eecee37e4
#define DEBUG_OUT_UUID \
    { 0x4c, 0xd1, 0x21, 0x4d, \
      0x80, 0xde, 0x4a, 0xd9, 0xb3, 0xb4, \
      0xca, 0x8e, 0xec, 0xee, 0x37, 0xe4 }

extern uuid_t DebugOutUUID;

typedef enum dbgout_color_t {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
} dbgout_color_t;

typedef kstatus_t (*setcolor_t)(dbgout_color_t fg, dbgout_color_t bg);
typedef kstatus_t (*writestr_t)(const char* data);
typedef kstatus_t (*clrscr_t)();

typedef struct DebugOutI {
    setcolor_t setcolor;
    writestr_t writestr;
    clrscr_t clrscr;
} DebugOutI;
