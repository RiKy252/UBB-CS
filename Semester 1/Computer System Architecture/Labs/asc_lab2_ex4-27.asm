bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a DB 20
    b DB 30
    c DB 15
    d DW 80
    result DW 0 ; d/[(a+b)-(c+c)]

; our code starts here
segment code use32 class=code
    start:
        mov ax, [d]
        mov bx, [a]
        add bx, [b]
        mov [result], bx
        mov bx, [c]
        add bx, [c]
        sub [result], bx
        mov bl, [result]
        div bl ; al stores the final result because of the div operation
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
