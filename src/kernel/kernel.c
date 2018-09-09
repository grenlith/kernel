#include "screen.h"
#include "keyboard.h"

void kmain(void) {
    
    clear_screen();

    idt_init();
    kb_init();

    while(1);
}