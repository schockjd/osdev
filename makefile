
AS := i686-elf-as
CC := i686-elf-gcc
LD := i686-elf-gcc

CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall
LDFLAGS := -ffreestanding -O2 -nostdlib

OUTDIR := build
INITDIR := init
KERNELDIR := kernel


OBJS := $(addprefix $(OUTDIR)/, \
        boot.o \
		kernel.o)

all: myos.bin

$(OUTDIR)/%.o: $(INITDIR)/%.S
	$(AS) $< -o $@

$(OUTDIR)/%.o: $(KERNELDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -Ikernel/include 

$(OBJS): | $(OUTDIR)

myos.bin: $(OBJS) linker.ld
	$(LD) -T linker.ld -o $(OUTDIR)/myos.bin $(LDFLAGS) $(OBJS) -lgcc

clean: 
	rm -rf $(OUTDIR)

$(OUTDIR): 
	mkdir $(OUTDIR)
