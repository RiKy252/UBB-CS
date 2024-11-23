bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (100 + a + b * c) / (a - 100) + e + x / a, a,b-byte, c-word, e-doubleword, x-qword UNSIGNED
    a db 110
    b db 3
    c dw 30
    e dd 17
    x dq 330
    ; result = 50

; our code starts here
segment code use32 class=code
    start:
        mov AL, [b] ; AL = b
        mov AH, 0 ; AX = b
        mul word[c] ; DX:AX = AX * c = b * c
        mov BL, [a] ; BL = a 
        add BL, 100; BL = a + 100
        mov BH, 0 ; BX = a + 100
        mov CX, 0 ; CX:BX = a + 100
        add AX, BX
        adc DX, CX ; DX:AX = (100 + a + b * c)       
        mov CL, [a]
        sub CL, 100 ; CL = a - 100
        mov CH, 0 ; CX = a - 100
        div CX ; AX = DX:AX / CX -> AX = (100 + a + b * c) / (a - 100), DX = (100 + a + b * c) % (a - 100)
        mov DX, 0 ; DX:AX = (100 + a + b * c) / (a - 100)
        push DX
        push AX
        pop EAX ; EAX = (100 + a + b * c) / (a - 100)     
        add EAX, [e] ; EAX = (100 + a + b * c) / (a - 100) + e       
        mov BL, [a] ; BL = a
        mov BH, 0 ; BX = a
        mov CX, 0 ; CX:BX = a
        push CX
        push BX
        pop EBX ; EBX = a    
        mov ECX, EAX ; ECX = (100 + a + b * c) / (a - 100) + e
        mov EAX, [x] ; EAX = x
        mov EDX, 0 ; EDX:EAX = x
        div EBX ; EAX = EDX:EAX / EBX = x / a
        add EAX, ECX ; EAX = (100 + a + b * c) / (a - 100) + e + x / a
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
