#include <stddef.h>
#include <stdint.h>
#include "screen.h"

uint16_t current_loc = 0;
termchar_t* vidptr = (termchar_t* )0xb8000;

const char* banner = "                                                                          grenos";
color_t default_colors = {.bg = color_black, .fg = color_lgray};

void kprint(const char* str) {
    for(ptrdiff_t i = 0; str[i] != '\0'; i++) {
        termchar_t value = {.code = str[i]};
        
        if(current_loc < COLUMNS) {
            value.colors.bg = color_black;
            value.colors.fg = color_lmagenta;
        }   
        else {
            value.colors = default_colors;
        }

        vidptr[current_loc++] = value;
    }
    
    return;
}

void clear_screen(void) {
    termchar_t value = {
        .code = BLOCK, 
        .colors.bg = default_colors.bg,
        .colors.fg = default_colors.bg
    };

    for(ptrdiff_t i = 0; i < SCREENSIZE; i++) {
        vidptr[i] = value;
    }

    current_loc = 0;
    kprint(banner);

    return;
}

void kprint_bulk(termchar_t buffer[]) {
    for(ptrdiff_t i = 0; i < SCROLLBACK; i++) {
        vidptr[current_loc++] = buffer[i];
    }
    return;
}

void scroll_screen(void) {
    termchar_t buffer[SCROLLBACK];

    for(ptrdiff_t i = 0; i < SCROLLBACK; i++) {
        buffer[i] = vidptr[i + (COLUMNS * 2)];
    }
    
    clear_screen();
    kprint_bulk(buffer);
    return;
}

void kprint_newline(void) {
    current_loc = current_loc + (COLUMNS - current_loc % (COLUMNS));

    if(current_loc >= SCREENSIZE) {
        scroll_screen();
    }

    return;
}

void kprint_backspace(void) {
    if(current_loc <= 80)
        return;

    termchar_t value = {
        .code = BLOCK,
        .colors.bg = default_colors.bg,
        .colors.fg = default_colors.bg
    };
    current_loc = current_loc - 1;
    vidptr[current_loc++] = value;
    current_loc = current_loc - 1;

    if(current_loc > SCREENSIZE) {
        current_loc = 0;
    }
    return;
}