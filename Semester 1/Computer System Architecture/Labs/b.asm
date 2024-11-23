bits 32      
global module
segment data use32 public data
    ranks resb 255
    counter db 0
    maximum db 0
    current_rank db 0
    sum db 0
segment code use32 public code
    module:
        ; INPUT - pointer to string of doublewords ([esp + 4])
        ; OUTPUT - pointer to the string of ranks (in eax)
        ;        - pointer to sum (in ebx)
        mov esi, [esp + 4]
        mov edi, ranks
        .repeat_loop:
            mov al, [counter]
            cmp al, 4
            jne .next
            mov al, [sum]
            add al, [maximum]
            mov [sum], al
            mov al, [current_rank]
            stosb
            mov byte[counter], 0
            mov byte[current_rank], 0
            mov byte[maximum], 0
            .next:
                lodsb
                cmp al, 0
                je .final
                cmp al, [maximum]
                jb .skip
                mov bl, 4
                sub bl, [counter]
                mov [current_rank], bl
                mov [maximum], al
                .skip:
                    inc byte[counter]
                    jmp .repeat_loop
        .final:
            mov eax, ranks
            mov ebx, [sum]
            ret 4