#include <stdint.h>

#ifndef __screen_h__

#define LINES 25
#define COLUMNS 80
#define BYTES 2
#define SCREENSIZE LINES * COLUMNS * BYTES
#define BLOCK 219
#define BGCOLOR 0x00
#define FONTCOLOR 0x07
#define HEADERFONTCOLOR 0x0D
#define SCROLLBACK SCREENSIZE - (COLUMNS * 4)

void kprint(const char *str);
void clear_screen(void);
void kprint_newline(void);
void kprint_backspace(void);
uint16_t get_current_loc(void);
uintptr_t* get_vidptr(void);

#define __screen_h__ 1
#endif