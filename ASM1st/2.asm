.MODEL SMALL,C
.DATA  
    len1 dw 0
    len2 dw 0
.STACK 256
.CODE
.STARTUP
    func PROC NEAR USES SI DI, str1:WORD, str2:WORD, n:WORD
    LOCAL len1:WORD,len2:WORD
    MOV len1, 0
    mov len2, 0  
    mov SI, str1     
length1: ;1
     cmp [SI], '$'
     inc SI
     inc len1
     jz m1 
     jmp length1
m1:
    mov ZF, 0  
    mov DI, str2
length2:
    cmp DI,'$'
    inc DI
    inc len2
    jz m2
    jmp length2
m2:      ;2  
    mov DI, str2
    mov cx, 5 
    mov ZF,0
z5:
    cmp [DI], '$'
    jz m3       
    mov bx, 6
    sub bx, cx
    mov WORD PTR [DI], bx          
    LOOP z5
m3:      ;3
    mov ZF, 0
    mov cx, 5
z:
    cmp [DI],'$'
    jnz h
    dec str1
h:  mov WORD PTR [DI], ' '
    dec str1
    LOOP z    
         ;4
    sub length1, n
    mov ax, length1
    RET
    func ENDP
.EXIT 0
END