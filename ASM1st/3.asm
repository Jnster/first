.MODEL SMALL, C
.STACK 256
.DATA
X DB 0
Y DB 0
A DB 0
U DB 0
.CODE

public var9

var9 PROC NEAR C USES SI, row:word, col:word, attr:word, n:word

PUSHA

MOV DX, row
MOV Y, DL
MOV DX, col
MOV X, DL
MOV DX, attr
MOV A, DL
MOV CX, n

M1:     ;stavim kursor

MOV AH, 2
MOV BH, 0
MOV DH, Y
MOV DL, X
INT 10H

MOV DI, CX   ;pishem
MOV AH, 9
MOV BH, 0
MOV BL, A   
INC U
MOV AL, U 
MOV CX, 1
INT 10H  

MOV AL, ' '
INT 10H

CMP X, 79
JE NEWSTR
JMP CONTINUE
         
NEWSTR:
INC Y         
CMP Y, 19
JE _OUT
     
CONTINIE:         
INC X
MOV CX, DI
LOOP M1

_OUT: 

POPA

RET
var9 ENDP     
.EXIT 0
END