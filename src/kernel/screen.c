#include <stdint.h>
#include "screen.h"

uint16_t current_loc = 0;
uintptr_t* vidptr = (uintptr_t* )0xb8000;

const char* banner = "                                                                          grenos";

//TODO: check for screen buffer overflow prior to print
void kprint(const char* str) {
    uint16_t i = 0;
    while(str[i] != '\0') {
        vidptr[current_loc++] = str[i++];
        if(current_loc <= COLUMNS * 2)
            vidptr[current_loc++] = HEADERFONTCOLOR;
        else
            vidptr[current_loc++] = FONTCOLOR;
    }
    return;
}

void clear_screen(void) {
    uint16_t i = 0;
    while(i < SCREENSIZE) {
        vidptr[i++] = BLOCK;
        vidptr[i++] = BGCOLOR;
    }
    current_loc = 0;
    kprint(banner);
    return;
}

void kprint_bulk(char buffer[]) {
    for(uint16_t i = 0; i < SCROLLBACK; i++) {
        vidptr[current_loc++] = buffer[i];
    }

    return;
}

void scroll_screen(void) {
    char buffer[SCROLLBACK];

    for(uint16_t i = 0; i < SCROLLBACK; i++) {
        buffer[i] = vidptr[i + (COLUMNS * 4)];
    }
    
    clear_screen();
    kprint_bulk(buffer);
    return;
}

void kprint_newline(void) {
    uint16_t line_size = BYTES * COLUMNS;
    current_loc = current_loc + (line_size - current_loc % (line_size));
    if(current_loc >= SCREENSIZE) {
        scroll_screen();
    }
    return;
}

void kprint_backspace(void) {
    if(current_loc == 160)
        return;
    current_loc = current_loc - 2;
    vidptr[current_loc++] = BLOCK;
    vidptr[current_loc++] = BGCOLOR;
    current_loc = current_loc - 2;
    if(current_loc > SCREENSIZE) {
        current_loc = 0;
    }
    return;
}

uint16_t get_current_loc(void) {
    return current_loc;
}

uintptr_t* get_vidptr(void) {
    return vidptr;
}