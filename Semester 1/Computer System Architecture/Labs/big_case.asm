bits 32 ; assembling for the 32 bits architecture
segment data use32
    result resb 256
segment code use32 public code
global upper_case
   
upper_case:
    ; Input the pointer to the input string
    ; Output - eax - the pointer to the string that contains only the lowercase letters
    mov esi, [esp + 4] ; esi points towards source input
    mov edi, result
    
    .loop_1:
        lodsb ; al = character from source string
        cmp al, 0 ; if al = 0 that means we've proccessed all the characters from the string
        je .end_loop
        
        cmp al, 'A'
        jl .not_uppercase
        cmp al, 'Z'
        jg .not_uppercase
        
        stosb ; we append the character that is lowercase to the result string
        .not_uppercase:
            jmp .loop_1
    .end_loop:
        mov eax, result
        ret 4
