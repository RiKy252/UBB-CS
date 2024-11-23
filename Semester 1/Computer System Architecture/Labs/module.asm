bits 32
; Read from file numbers.txt a string of numbers (odd and even). Build two strings using readen numbers:
; P – only with even numbers
; N – only with odd numbers
; Display the strings on the screen. 

extern _fscanf
extern _fopen
extern _fclose
global _even_numbers
global _odd_numbers

segment data public data use32
    file_descriptor dd -1
    file_name db "numbers.txt", 0
    mode db "r", 0
    format db "%d", 0
    element db 0
    odd_string_address dd 0
    even_string_address dd 0

segment code public code use32
    _even_numbers:
        push ebp
        mov ebp, esp

        mov eax, [ebp + 8]
        mov [even_string_address], eax
        
        push mode
        push file_name
        call _fopen
        add esp, 4 * 2
        
        mov [file_descriptor], eax 
        cmp eax, 0
        je _ending
            
        mov edi, [even_string_address]
        
        _read_loop:
            push element ; address to store the element
            push format ; address to the format of integers
            push dword [file_descriptor]
            call _fscanf
            add esp, 4 * 3 ; clean-up the stack
           
            cmp eax, -1 ; for fscanf if eax = -1 then we are encountered EOF (end of file)
            je _end_of_file   
            
            mov esi, element
            
            mov al, [element]
            mov ah, 0
            mov bl, 2
            div bl
            cmp ah, 0
            je _read_loop
            ;
            movsb
            jmp _read_loop
                
        _end_of_file:
            push dword[file_descriptor]
            call _fclose
            add esp, 4 * 1
            
            mov esp, ebp
            pop ebp
            _ending:
                ret 