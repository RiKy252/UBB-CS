bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (a+c)-(d+b) a - byte, b - word, c - double word, d - qword - Unsigned representation
    a db 144
    b dw 180
    c dd 426
    d dq 320
    ; result = 70 

; our code starts here
segment code use32 class=code
    start:
        mov EAX, [d] ; EAX = d
        mov EDX, 0 ; EDX:EAX = d
        mov BX, [b] ; BX = b
        mov CX, 0 ; CX:BX = b
        push CX
        push BX
        pop EBX ; EBX = b
        mov ECX, 0 ; ECX:EBX = b
        add EAX, EBX
        adc EDX, ECX ; EDX:EAX = d + b
        mov BL, [a] ; BL = a
        mov BH, 0 ; BX = a
        mov CX, 0 ; CX:BX = a
        push CX
        push BX
        pop EBX ; EBX = a
        mov ECX, [c] ; ECX = c
        add EBX, ECX ; EBX = a + c
        mov ECX, 0 ; ECX:EBX = a + c
        sub EBX, EAX
        sbb ECX, EDX ; ECX:EBX = (a+c)-(d+b)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
