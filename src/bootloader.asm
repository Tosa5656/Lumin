bits 16

org 0x7C00

start:
    mov ah, 0x02
    mov al, 2
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x7E00
    int 0x13

    jmp 0x0000:0x7E00

times 510-($-$$) db 0
dw 0xAA55    
