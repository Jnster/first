TITLE   Laba1st
.MODEL small
.DATA                                  
 x dw, 0
.STACK 256

.CODE                                  

.STARTUP                                   mov dx, 15
    add dx, 4
    div 4
    mov ax, dx
    mul 5
    mov bx, 43 
    sub bx, ax
    
    mov dx, 36
    div 4
    mov x, dx
    mov dx, 35
    div 8
    sub x, dx

    mov dx, bx
    div x
    add dx, 33 
.EXIT 0                                
END                                    