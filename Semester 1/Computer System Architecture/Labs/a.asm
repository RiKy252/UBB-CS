bits 32

global start        

extern printf, exit          
import printf msvcrt.dll
import exit msvcrt.dll    
extern module

segment data use32 public data
    string dd 0x1234A678, 0x12345678, 0x1AC3B47D, 0xFEDC9876, 0
    ranks dd 0
    print_format db "%d", 0
    endline db 10, 0
segment code use32 public code
    start:
        push string
        call module
        mov [ranks], eax
        mov esi, [ranks]
        ranks_loop:
            lodsb
            cmp al, 0
            je end_loop
            mov ah, 0
            cwde
            push eax
            push print_format
            call [printf]
            add esp, 4 * 2
            loop ranks_loop
        end_loop:
            push endline
            call [printf]
            add esp, 4
            mov al, bl
            cbw
            cwde
            push eax
            push print_format
            call [printf]
            add esp, 4 * 2
        push    dword 0      
        call    [exit]       
