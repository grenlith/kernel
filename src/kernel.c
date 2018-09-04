#include "inc/screen.c"
#include "inc/keyboard.c"

void kmain(void) {
    
    clear_screen();

    idt_init();
    kb_init();

    while(1);
}