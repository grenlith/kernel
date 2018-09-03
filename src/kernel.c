#include "inc/screen.c"
#include "inc/keyboard.c"

char *prompt = "> ";

void kmain(void) {
    const char* bootmsg = "Welcome to the gren kernel!";
    
    clear_screen();
    kprint(bootmsg);
    kprint_newline();
    kprint(prompt);

    idt_init();
    kb_init();

    while(1);
}