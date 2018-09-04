#include <stdint.h>
#include "keyboard_map.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define ENTER_KEY 0x1c
#define BACKSPACE_KEY 0x0e

extern uint8_t keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(uint16_t port);
extern void write_port(uint16_t port, uint8_t data);
extern void load_idt(uintptr_t *idt_ptr);

struct IDT_entry {
    uint16_t offset_lowerbits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void) {
    uint32_t keyboard_address;
    uint32_t idt_address;
    uint32_t idt_ptr[2];

    //populate idt entry of kbd interrupt
    keyboard_address = (uintptr_t)keyboard_handler;
    IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
    IDT[0x21].selector = 0x08;  // kernel code segment offset
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = 0x8e; // int gate
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    //begin init
    write_port(0x20, 0x11); //pic1 command
    write_port(0xA0, 0x11); //pic2 command
    write_port(0x21, 0x20); //pic1 data - remap the pic beyond 0x20
    write_port(0xA1, 0x28); //pic2 data - remap the pic beyond 0x20
    //cascading?
    write_port(0x21, 0x00);
    write_port(0xA1, 0x00);
    //environment info
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);
    //end init

    //mask interrupts
    write_port(0x21, 0xff);
    write_port(0xA1, 0xff);

    //fill idt descriptor
    idt_address = (uintptr_t)IDT;
    idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}

void kb_init(void) {
    write_port(0x21, 0xFD);
}

void keyboard_handler_main(void) {
    uint8_t status;
    int8_t keycode;

    write_port(0x20, 0x20); //write EOI

    status = read_port(KEYBOARD_STATUS_PORT);
    //lowest bit of status will be set if buffer is not empty
    if(status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        
        if(keycode < 0) {
            return;
        }

        if(keycode == ENTER_KEY) {
            kprint_newline();
            return;
        }

        if(keycode == BACKSPACE_KEY) {
            kprint_backspace();
            return;
        }

        vidptr[current_loc++] = keyboard_map[keycode];
        vidptr[current_loc++] = 0x07;
    }
}