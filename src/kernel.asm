;;stub.asm
bits 32                     ;nasm directive (32bit)
section .text
    ;mutiboot spec
    align 4
    dd 0x1BADB002           ;magic
    dd 0x00                 ;flags
    dd - (0x1BADB002 + 0x00);checksum

global start
global keyboard_handler
global read_port
global write_port
global load_idt

extern kmain                ;defined in kernel.c
extern keyboard_handler_main

read_port:
    mov edx, [esp + 4]
    in al, dx
    ret

write_port:
    mov edx, [esp + 4]
    mov al, [esp + 4 + 4]
    out dx, al
    ret

load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret

keyboard_handler:
    call keyboard_handler_main
    iretd

start:
    cli                     ;block interrupts
    mov esp, stack_space    ;set stack pointer
    call kmain              
    hlt                     ;halt the cpu

section .bss
resb 8192                   ;8kb for the stack
stack_space: