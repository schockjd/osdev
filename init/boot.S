# Declare constants used for creating a multiboot header.
.set ALIGN,     1<<0                # align loaded modules on page boundaries
.set MEMINFO,   1<<1                # provide memory map
.set TXTMODE,   2<<1
.set FLAGS,     ALIGN | MEMINFO | TXTMODE # this is the Multiboot 'flag' field
.set MAGIC,     0x1BADB002          # 'magic number'
.set CHECKSUM,  -(MAGIC+FLAGS)      # checksum

# Declare multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Set up a stack
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KB stac
stack_top:

#setup entry point for kernel
.section .text
.global _start
.type _start, @function
_start:
    # Setup a stack
    movl    $stack_top, %esp

    # call the C-code kernel
    call    kernel_main

    #if kernel_main returns, halt
    cli
.Lhang:    
    hlt
    jmp .Lhang

.size _start, . - _start    

