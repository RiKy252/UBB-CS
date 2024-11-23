bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (a * b) / d - c , b - word, a,c,d - byte signed
    a db 5
    b dw 15
    c db 10
    d db 20
    x dw 0

; our code starts here
segment code use32 class=code
    start:
        mov AX, [a]
        CBW ; AX = a
        IMUL byte[b]
        mov BX, AX
        mov AL, [d]
        CBW ; AX = d 
        mov CX, AX ; CX = d
        mov AX, BX; DX:AX = a * b
        IDIV CX; DX:AX / CX = AX, DX:AX % CX = DX
        mov DX, AX ; DX = (a * b) / d
        mov AL, [c]
        CBW
        sub DX, AX
        mov [x], DX
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
