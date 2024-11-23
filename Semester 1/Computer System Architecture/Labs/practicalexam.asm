bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, scanf, printf, fread
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
import exit msvcrt.dll    

segment data use32 class=data
    file_descriptor dd -1
    access_mode db "r", 0
    integer_format db "%d", 0
    string_format db "%s", 0
    char_format db "%c", 0
    L db 0
    two db 2
    word_index db 0
    word_length db 0
    file_name resb 255
    sentence resb 255
    word_to_print resb 255

; our code starts here
segment code use32 class=code
    start:
        push L
        push integer_format
        call [scanf]
        add esp, 4 * 2
        
        push file_name
        push string_format
        call [scanf]
        add esp, 4 * 2
        
        push access_mode
        push file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je ending
    
        push dword [file_descriptor]
        push dword 255
        push dword 1
        push sentence
        call [fread]
        add esp, 4 * 4
        
        mov esi, sentence
        mov edi, word_to_print
        
        parse_loop:
            continue:
            inc byte [word_index]
            mov byte [word_length], 0
            word_loop:
                lodsb
                cmp al, 0
                je end_loop
                cmp al, ' '
                je verify
                stosb
                inc byte [word_length]
            
                jmp word_loop
            verify:
                mov bl, 2
                mov al, [word_index]
                mov ah, 0
                div bl
                cmp ah, 1
                jne continue
                mov bl, [word_length]
                cmp bl, [L]
                jg continue
                print_s:
                    push edi
                    push string_format
                    call [printf]
                    add esp, 4 * 2
                    
                jmp continue
        end_loop:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        ending:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
