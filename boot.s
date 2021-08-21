[bits 16]
[org 0x7c00]

mov bp, 0x9000
mov sp, bp

;load kernel from disk
mov bx, 0x1000 
mov dh, 6 
mov dl, 0
call disk_load

;switch to 32 bits
cli                     
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 0x1 
mov cr0, eax
jmp CODE_SEG:init_32bit


disk_load:
    pusha
    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
    mov ch, 0x00
    mov dh, 0x00
    int 0x13
    popa
    ret


gdt_start:
    dq 0x0

gdt_code:
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

gdt_data:
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10010010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit)
    dd gdt_start ; address (32 bit)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

[bits 32]
init_32bit:
    mov ax, DATA_SEG 
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call 0x1000 ;call kernel

; padding
times 510 - ($-$$) db 0

; magic number
dw 0xaa55