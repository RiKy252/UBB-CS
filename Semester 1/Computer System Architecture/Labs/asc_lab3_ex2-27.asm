bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (d+d-c)-(c+c-a)+(c+a) a - byte, c - double word, d - qword - Signed representation
    a db 10
    c dd 200
    d dq 20
    ; result = -340

; our code starts here
segment code use32 class=code
    start:
        mov EAX, [d] ; EAX = d
        cdq ; EDX:EAX = d
        add EAX, dword[d]
        adc EDX, dword[d+4] ; EDX:EAX = d + d
        push EAX
        push EDX
        pop ECX
        pop EBX ; ECX:EBX = d + d
        mov EAX, [c] ; EAX = c
        cdq ; EDX:EAX = c
        sub EBX, EAX
        sbb ECX, EDX ; ECX:EBX = (d + d - c)
        mov EAX, [c] ; EAX = c
        add EAX, [c] ; EAX = c + c
        mov EDX, EAX ; EDX = c + c
        mov AL, [a] ; AL = a
        cbw ; AX = a
        cwde ; EAX = a
        sub EDX, EAX ; EDX = (c + c - a)
        mov EAX, EDX ; EAX = (c + c - a)
        cdq ; EDX:EAX = (c + c - a)
        sub EBX, EAX
        sbb ECX, EDX ; ECX:EBX = (d + d - c) - (c + c - a)
        mov AL, [a] ; AL = a
        cbw ; AX = a
        cwde ; EAX = a
        mov EDX, [c] ; EDX = c
        add EAX, EDX ; EAX = c + a
        cdq ; EDX:EAX = (c + a)
        add EBX, EAX
        adc ECX, EDX ; ECX:EBX = (d + d - c) - (c + c - a) + (c + a)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
