
AS := i686-elf-as
CC := i686-elf-gcc
LD := i686-elf-gcc

CFLAGS := -std=gnu99 -gdwarf-2 -ffreestanding -O2 -Wall -I.
LDFLAGS := -ffreestanding -O2 -nostdlib

OUTDIR := build
INITDIR := init
KERNELDIR := kernel
DRIVERDIR := drivers
INTERFACEDIR := interfaces

OBJS := $(addprefix $(OUTDIR)/, \
        boot.o \
		kernel.o \
		kutils.o \
		hub.o \
		dbgout.o \
		vga.o)

all: $(OUTDIR)/myos.bin

$(OUTDIR)/%.o: $(INITDIR)/%.S
	$(AS) $< -o $@

$(OUTDIR)/%.o: $(KERNELDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -Ikernel/include 

$(OUTDIR)/%.o: $(DRIVERDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -Ikernel/include

$(OUTDIR)/%.o: $(INTERFACEDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -Ikernel/include

$(OBJS): | $(OUTDIR)

$(OUTDIR)/myos.bin: $(OBJS) linker.ld
	$(LD) -T linker.ld -o $(OUTDIR)/myos.bin $(LDFLAGS) $(OBJS) -lgcc

clean: 
	rm -rf $(OUTDIR)

$(OUTDIR): 
	mkdir $(OUTDIR)

iso: $(OUTDIR)/myos.bin
	mkdir -p $(OUTDIR)/isodir/boot/grub
	cp $(OUTDIR)/myos.bin $(OUTDIR)/isodir/boot/myos.bin
	cp img/grub.cfg $(OUTDIR)/isodir/boot/grub/grub.cfg
	grub2-mkrescue -o $(OUTDIR)/myos.iso $(OUTDIR)/isodir
