TITLE Laba1st
.MODEL TINY
.DATA 
x dw 0 
y dw 0
.STACK 256
.CODE
.STARTUP
    mov ax, 15
    add ax, 4
    mov bx, 4
    div bx   
    mov cx, 5
    mul cx
    mov bx, 43 
    sub bx, ax

    mov ax, 36
    mov cx,4
    div cx 
    mov y, ax 
   
    mov ax, 35
    mov x, 8
    div x
    sub y, ax
    
    mov ax, bx
    div y
    add ax, 33 
.EXIT 0 
END