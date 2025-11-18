.syntax unified
.cpu cortex-m4
.thumb

.global _start

.section .text
_start:
    // Set stack pointer
    ldr r0, =_stack_top
    mov sp, r0
    
    // Call main
    bl main
    
    // If main returns, loop forever
    b .

// Stack space
.section .bss
.align 4
_stack:
    .space 1024
_stack_top:
