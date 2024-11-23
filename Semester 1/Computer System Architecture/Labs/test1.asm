bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fprintf, fopen, fclose              
import exit msvcrt.dll  
import scanf msvcrt.dll
import fprintf msvcrt.dll 
import fopen msvcrt.dll
import fclose msvcrt.dll 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "test1.txt", 0
    string_format db "%s", 0
    file_descriptor dd -1
    file_mode db "a", 0
    mesaj db 0

; our code starts here
segment code use32 class=code
    start:
        push file_mode
        push file_name
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je ending
        mov [file_descriptor], eax
        
        push mesaj
        push string_format
        call [scanf]
        add esp, 4 * 2
        
        push dword mesaj
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 2
    
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
    
        ending:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
