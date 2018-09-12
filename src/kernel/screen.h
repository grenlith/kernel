#include <stdint.h>

#ifndef __screen_h__

#define LINES 25
#define COLUMNS 80
#define SCREENSIZE LINES * COLUMNS
#define BLOCK 219
#define SCROLLBACK SCREENSIZE - (COLUMNS * 2)

typedef struct {
    uint8_t fg : 4;
    uint8_t bg : 4;
} color_t;

typedef struct {
    uint8_t code;
    color_t colors;
} termchar_t;

enum cga_colors {
    color_black = 0,
    color_blue,
    color_green,
    color_cyan,
    color_red,
    color_magenta,
    color_brown,
    color_lgray,
    color_gray,
    color_lblue,
    color_lgreen,
    color_lcyan,
    color_lred,
    color_lmagenta,
    color_yellow,
    color_white
};

void kprint(const char *str);
void clear_screen(void);
void kprint_newline(void);
void kprint_backspace(void);

#define __screen_h__ 1
#endif