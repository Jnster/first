TITLE   Laba1st
.MODEL small
.DATA                                  
.STACK 256
.CODE                                  
.STARTUP                                   mov ax, 15
    add ax, 4
    div 4
    mul 5
    mov bx, 43 
    sub bx, ax
    
    mov ax, 36
    div 4
    mov cx, ax
    mov ax, 35
    div 8
    sub cx, ax

    mov ax, bx
    div cx
    add ax, 33 
.EXIT 0                                
END                                    