#define LINES 25
#define COLUMNS 80
#define BYTES 2
#define SCREENSIZE LINES * COLUMNS * BYTES
#define BLOCK 219
#define BGCOLOR 0x00
#define FONTCOLOR 0x07

unsigned int current_loc = 0;
char *vidptr = (char*)0xb8000;

void kprint(const char *str) {
    unsigned int i = 0;
    while(str[i] != '\0') {
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = FONTCOLOR;
    }
}

void kprint_newline(void) {
    unsigned int line_size = BYTES * COLUMNS;
    current_loc = current_loc + (line_size - current_loc % (line_size));
}

void kprint_backspace(void) {
    current_loc = current_loc - 2;
    vidptr[current_loc++] = BLOCK;
    vidptr[current_loc++] = BGCOLOR;
    current_loc = current_loc - 2;
}

void clear_screen(void) {
    unsigned int i = 0;
    while(i < SCREENSIZE) {
        vidptr[i++] = BLOCK;
        vidptr[i++] = BGCOLOR;
    }
}