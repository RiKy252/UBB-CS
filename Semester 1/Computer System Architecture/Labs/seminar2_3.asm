bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a * b * c - d , a,b,c,d - byte , signed
    a db 5
    b db 6
    c db 7
    d db 8

; our code starts here
segment code use32 class=code
    start:
        mov AL, [a]
        mov AH, [b]
        imul AH ; AX = a * b
        mov BX, AX
        mov AL, [c]
        cbw ; AX = c 
        imul BX ; DX:AX = AX * BX = a * b * c
        push DX
        push AX
        pop EDX ; EDX = DX:AX
        mov AL, [d]
        cbw ; AX = d
        cwde ; EAX = d
        sub EDX, EAX ; EDX is the result
        push EDX
        pop AX
        pop DX ; DX:AX = EDX
        ; idiv word[e] ; AX = DX:AX / e , if we want the result to be (a * b * c - d) / e 
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
