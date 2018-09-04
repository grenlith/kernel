#include "inc/screen.c"
#include "inc/keyboard.c"

char *prompt = "> ";

void kmain(void) {
    
    clear_screen();
    
    idt_init();
    kb_init();

    while(1);
}