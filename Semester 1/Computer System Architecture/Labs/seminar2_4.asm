bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a * b - c * d , a,b,c,d - words, unsigned
    a dw
    b dw
    c dw 
    d dw

; our code starts here
segment code use32 class=code
    start:
        mov AX, [a]
        mul word[b] ; DX:AX = a * b
        mov CX, DX
        mov BX, AX ; CX:BX = a * b
        mov AX, [c]
        mul word[d] ; DX:AX = c * d
        sub BX, AX ; sets the CF
        sbb CX, DX ; subtract with borrow 
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
