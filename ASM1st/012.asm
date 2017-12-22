Title l12
.MODEL TINY
.DATA
.STACK 256
.CODE
.STARTUP
    mov ax, 49CBh
    ror ax, 8
    mov bx, 7F6Eh 
    ror bx, 8
        
    mov ch, ah
    mov ah, bh
    mov bh, ch
    
    mov cl, al
    mov al, bl
    mov bl, cl 
.EXIT 0
END