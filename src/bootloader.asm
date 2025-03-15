bits 16

org 0x7C00

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
	
   	mov ax, 0x000
	   mov ss, ax
   	mov sp, 0x7C00

    mov ah, 0x02
    mov al, 2
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x7E00
    int 0x13

    jc disk_error

    jmp 0x0000:0x7E00

disk_error:
    mov si, disk_error_msg
    call print_string
    hlt

print_string:
   mov ah, 0x0E
.print_char:
   lodsb
   cmp al, 0
   je .done
   int 0x10
   jmp .print_char
.done:
   ret

disk_error_msg db "Disk read error!", 0

times 510-($-$$) db 0
dw 0xAA55    
