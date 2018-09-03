SRCDIR=src
ODIR=obj
MKDIR_P=mkdir -p

.PHONY: directories

default: directories asm c link
	
asm:
	nasm -f elf32 $(SRCDIR)/kernel.asm -o $(ODIR)/kasm.o

c:
	gcc -fno-stack-protector -m32 -c $(SRCDIR)/kernel.c -o $(ODIR)/kc.o

link: 
	ld -m elf_i386 -T link.ld -o kernel $(ODIR)/kasm.o $(ODIR)/kc.o

directories: $(ODIR)

$(ODIR):
	$(MKDIR_P) $(ODIR)

clean:
	rm -rf $(ODIR)
	rm -f kernel