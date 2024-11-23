bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf               
import exit msvcrt.dll  
import scanf msvcrt.dll  
                          

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se citeste de la tastatura un cuvant si un numar. Daca numarul este par se cere criptarea cuvantului prin adunarea la fiecare caracter a numarului 20. Daca numarul este impar se cere criptarea cuvantului prin adaugarea dupa fiecare vocala a gruparii "p"+vocala.Se cere afisarea cuvantului criptat
    number_format db "%d", 0
    string_format db "%s", 0
    sentence db 0
    number db 0
    two db 2
    result db 0

; our code starts here
segment code use32 class=code
    start:
        push sentence
        push string_format
        call [scanf]
        add esp, 4 * 2
        
        push number
        push number_format
        call [scanf]
        add esp, 4 * 2
        
        mov ax, [number]
        div byte[two]
        cmp ah, 0
        je par
        impar:
            
        par:
            
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
