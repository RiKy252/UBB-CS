bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (a - b * c) / d , a,b,c,d - byte, unsigned
    a db 10
    b db 2
    c db 3
    d db 4
    
; our code starts here
segment code use32 class=code
    start:
        mov al, [b]
        mul byte[c] ; ax = ah * al
        mov dl, [a]
        mov dh, 0 ; dx = ah
        sub dx, ax
        mov ax, dx
        div byte[d] ; ah = ax % d, al = ax / d
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
