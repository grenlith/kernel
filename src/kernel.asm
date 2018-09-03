;;stub.asm
bits 32                     ;nasm directive (32bit)
section .text
    ;mutiboot spec
    align 4
    dd 0x1BADB002           ;magic
    dd 0x00                 ;flags
    dd - (0x1BADB002 + 0x00);checksum

global start
extern kmain                ;defined in kernel.c

start:
    cli                     ;block interrupts
    mov esp, stack_space    ;set stack pointer
    call kmain              
    hlt                     ;halt the cpu

section .bss
resb 8192                   ;8kb for the stack
stack_space: