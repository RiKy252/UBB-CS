bits 32
global start

extern printf, exit
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data
    sir dq 1110111b, 100000000h, 0ABCD0002E7FCh, 5
    sir_len equ ($ - sir) / 8
    rez resd sir_len+1

    degree db 0
    print_format db "%d", 0
    space_format db "%s", 0
    formatc db "%c",0
    temp dd 0
    print_string times 32 db 0
    space db 32, 0

segment code use32 class=code
start:
    mov esi, sir ; source
    mov edi, rez ; destination
    mov bl, 0
    cld
    mov ecx, sir_len * 2
    loop_1:
        lodsd ; eax = double words from sir, little endian representation
        mov [temp], eax
        mov byte[degree], 0
        mov dl, 0
        inc bl
        cmp bl, 1
        je parse
        jne skip
        parse:
            cmp eax, 0
            je end_parse_loop
            test eax, 1
            jz not_set_bit
            inc dl
            cmp dl, 3
            jne not_set_bit
            inc byte[degree]
            mov dl, 0
            jmp not_set_bit
            not_set_bit:
                shr eax, 1
                jmp parse
        end_parse_loop:
            mov dl, [degree]
            cmp dl, 2
            jb skip
            mov eax, [temp]
            stosd ; rez = this dword
            jmp final_1
        skip:
            mov bl, 0
        final_1:
    loop loop_1

    mov esi, rez
    mov edi, print_string

    repeta:
        push space
        push space_format
        call [printf]
        add esp, 8
        lodsd
        cmp eax,0
        je end_end
        mov ecx,32
        repeta_shift:
            mov ebx,0
            mov bl,0
            shl eax,1
            jnc bit0
            inc bl
            bit0:
            pusha
            push ebx
            push print_format
            call[printf]
            add esp,4*2
            popa
        loop repeta_shift
    jmp repeta
    end_end:
        push dword 0 
        call [exit] 