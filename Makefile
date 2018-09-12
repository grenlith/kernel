SRCDIR=src
ODIR=obj
CC=gcc
CFLAGS=-Wall -fno-stack-protector -m32 -std=gnu11 -c -g
MKDIR_P=mkdir -p

.PHONY: directories

default: directories asm c link
	
asm:
	nasm -f elf32 $(SRCDIR)/kernel/kernel.asm -o $(ODIR)/kasm.o

c:
	$(CC) $(CFLAGS) $(SRCDIR)/kernel/kernel.c $(SRCDIR)/kernel/screen.c $(SRCDIR)/kernel/keyboard.c
	mv *.o $(ODIR)

link:
	ld -m elf_i386 -T link.ld -o kernel $(ODIR)/kasm.o $(ODIR)/kernel.o $(ODIR)/screen.o $(ODIR)/keyboard.o

directories: $(ODIR)

$(ODIR):
	$(MKDIR_P) $(ODIR)

clean:
	rm -rf $(ODIR)
	rm -f kernel