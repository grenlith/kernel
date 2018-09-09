#include <stdint.h>

#ifndef __keyboard_h__

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define ENTER_KEY 0x1c
#define BACKSPACE_KEY 0x0e

extern void keyboard_handler(void);
extern char read_port(uint16_t port);
extern void write_port(uint16_t port, uint8_t data);
extern void load_idt(uintptr_t *idt_ptr);

void idt_init(void);
void kb_init(void);
void keyboard_handler_main(void);

struct IDT_entry {
    uint16_t offset_lowerbits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
};

#define __keyboard_h__ 1
#endif