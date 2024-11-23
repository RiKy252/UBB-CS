bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (100 + a + b * c) / (a - 100) + e + x / a, a,b-byte, c-word, e-doubleword, x-qword SIGNED
    a db -100
    b db 10
    c dw 100
    e dd -6
    x dq 500
    ; result = -16

; our code starts here
segment code use32 class=code
    start:
        mov AL, [b] ; AL = b
        cbw ; AX = b
        imul word[c] ; DX:AX = AX * c => DX:AX = b * c
        push DX
        push AX
        pop EAX ; EAX = DX:AX = b * c
        mov EDX, EAX ; EDX = b * c
        mov AL, [a] ; AL = a
        cbw ; AX = a
        add AX, 100 ; AX = a + 100
        cwde ; EAX = a + 100
        add EAX, EDX ; EAX = a + 100 + b * c
        push EAX
        pop BX
        pop CX ; CX:BX = a + 100 + b * c
        mov AL, [a] ; AL = a
        cbw ; AX = a
        sub AX, 100 ; AX = a - 100
        push CX
        push BX
        pop EDX ; EDX = a + 100 + b * c
        mov BX, AX ; BX = a - 100
        push EDX
        pop AX
        pop DX ; DX:AX = a + 100 + b * c
        idiv BX ; AX = DX:AX / BX => AX = (100 + a + b * c) / (a - 100)
        cwde ; EAX = (100 + a + b * c) / (a - 100)
        add EAX, [e] ; EAX = (100 + a + b * c) / (a - 100) + e
        mov ECX, EAX ; ECX = (100 + a + b * c) / (a - 100) + e
        mov AL, [a] ; AL = a
        cbw ; AX = a
        cwde ; EAX = a
        mov EBX, EAX ; EBX = a
        mov EAX, [x] ; EAX = x
        cdq ; EDX:EAX = x
        idiv EBX ; EAX = EDX:EAX / EBX => EAX = x / a
        add EAX, ECX ; EAX = x / a + (100 + a + b * c) / (a - 100) + e
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
