bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a DW 23
    b DW 13
    c DW 10
    d DW 5
    result DW 0 ; a+b-(c+d)+100h

; our code starts here
segment code use32 class=code
    start:
        mov ax, [a]
        add ax, [b]
        mov [result], ax
        mov ax, [c]
        add ax, [d]
        sub [result], ax
        mov ax, [result]
        add ax, 100h
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
