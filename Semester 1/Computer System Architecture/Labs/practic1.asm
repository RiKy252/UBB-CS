bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fprintf, scanf               
import exit msvcrt.dll    
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Sa se citeasca de la tastatura un numar n, apoi sa se citeasca mai multe cuvinte, pana cand se citeste cuvantul/caracterul "#". Sa se scrie intr-un fisier text toate cuvintele citite care incep si se termina cu aceeasi litera si au cel putin n litere
    temp db 0 
    char db 0
    first_letter db 0
    last_letter db 1
    file_name db "practic1.txt", 0
    new_line db 10, 0
    file_descriptor dd -1
    file_access db "w", 0
    string_read_format db "%s", 0
    char_format db "%c", 0
    integer_read_format db "%d", 0
    n db 0
    sentence db 0

; our code starts here
segment code use32 class=code
    start:
        mov bl, 1
        push file_access
        push file_name
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je ending
        mov [file_descriptor], eax
        push n
        push integer_read_format
        call [scanf]
        add esp, 4 * 2
        read_loop:
            mov al, [first_letter]
            cmp al, [last_letter]
            jne continue
            cmp bl, [n]
            jb continue
            mov [temp], bl
            mov cl, [temp]
            mov esi, sentence
            print_loop:
                lodsb
                mov [char], al
                push dword [char]
                push char_format
                push dword [file_descriptor]
                call [fprintf]
                add esp, 4 * 3
                sub cl, 1
                cmp cl, 0
                jne print_loop
            continue:
                mov bl, 1
                push sentence
                push string_read_format
                call [scanf]
                add esp, 4 * 2
                mov esi, sentence
                lodsb
                cmp al, '#'
                je end_loop
                mov [first_letter], al
                word_loop:
                    lodsb
                    cmp al, 0
                    je read_loop
                    mov [last_letter], al
                    inc bl
                    jmp word_loop
        end_loop:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        ending:   
            push    dword 0      
            call    [exit]       
