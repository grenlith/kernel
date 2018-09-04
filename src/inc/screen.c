#define LINES 25
#define COLUMNS 80
#define BYTES 2
#define SCREENSIZE LINES * COLUMNS * BYTES
#define BLOCK 219
#define BGCOLOR 0x00
#define FONTCOLOR 0x07
#define HEADERFONTCOLOR 0x0D

const char *banner = "                                                                          grenos";

unsigned int current_loc = 0;
char *vidptr = (char*)0xb8000;

void kprint(const char *str) {
    unsigned int i = 0;
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
    unsigned int i = 0;
    while(i < SCREENSIZE) {
        vidptr[i++] = BLOCK;
        vidptr[i++] = BGCOLOR;
    }
    current_loc = 0;
    kprint(banner);
    return;
}

void kprint_bulk(char buffer[]) {
    unsigned int i = 0;
    while(i < SCREENSIZE - (COLUMNS * 2 * 2)) {
        vidptr[current_loc++] = buffer[i];
        i = i + 1;
    }
    return;
}

void scroll_screen(void) {
    unsigned int scr = COLUMNS * 2 * 2;
    char buffer[SCREENSIZE - scr];
    unsigned int i = 0;
    while(i < SCREENSIZE - scr) {
        buffer[i] = vidptr[i + (COLUMNS * 2 * 2)];
        i = i + 1;
    }
    i = 0;
    clear_screen();
    kprint_bulk(buffer);
    return;
}

void kprint_newline(void) {
    unsigned int line_size = BYTES * COLUMNS;
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