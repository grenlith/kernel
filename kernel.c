/*
 * kernel.c
 */

void kmain(void) {
    const char *str = "communism will win";
    char *vidptr = (char*)0xb8000; //video memory start
    unsigned int i = 0;
    unsigned int j = 0;

    //clear the screen: 25 lines of 80 columns, each space takes two bytes
    while(j < 80 * 25 * 2) {
        vidptr[j] = 219; //blank
        vidptr[j+1] = 0x04; //07 is gray 05 is magenta!
        j = j + 2;
    }

    j = 0;
    i = 984*2; //should be center of screen

    //write the string to video memory
    while(str[j] != '\0') {
        vidptr[i] = str[j];
        vidptr[i+1] = 0x4E;
        ++j;
        i = i + 2;
    }

    return;
}