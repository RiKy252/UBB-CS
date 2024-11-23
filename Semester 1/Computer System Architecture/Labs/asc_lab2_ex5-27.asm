bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    b DB 3
    c DB 7
    e DW 60
    f DW 30
    g DW 70 ; result = 10
    result DW 0 ; [(e+f-g}+(b+c)*3]/5

; our code starts here
segment code use32 class=code
    start:
        mov bl, 3
        mov al, [b]
        add al, [c]
        mul bl ; ax = al * bl
        mov [result], ax
        mov ax, [e]
        add ax, [f]
        sub ax, [g]
        add ax, [result]
        mov bl, 5
        div bl ; al stores the result because of the div
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
