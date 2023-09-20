.section .text
.global _start

_start:
    cli

    movq $0x1000, %rsp
    
    xorq %rax, %rax
    mov %rax, %ds
    mov %rax, %es

    movb $0x02, %ah
    xor %bh, %bh
    mov $10, %dh
    mov $20, %dl
    int $0x10

    movb $0x0E, %ah
    mov  $'H', %al
    int $0x10
    mov  $'e', %al
    int $0x10
    mov  $'l', %al
    int $0x10
    int $0x10
    mov  $'o', %al
    int $0x10
    mov  $',', %al
    int $0x10
    int $0x10
    mov  $'W', %al
    int $0x10
    mov  $'o', %al
    int $0x10
    mov  $'r', %al
    int $0x10
    mov  $'l', %al
    int $0x10
    mov  $'d', %al
    int $0x10
    mov  $'!', %al
    int $0x10
    

    call _kernel_start

    hlt

    jmp .

.fill 510 - (. - _start), 1, 0

.word 0xAA55
