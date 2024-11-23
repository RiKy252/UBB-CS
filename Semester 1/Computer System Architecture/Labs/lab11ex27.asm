bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
extern upper_case
extern lower_case

; our data is declared here (the variables needed by our program)
segment data use32
    ; Read a sentence from the keyboard containing different characters (lowercase letters, big letters, numbers, special ones, etc). Obtain a new string with only the small case letters and another string with only the big case letters. Print both strings on the screen.
    input_message db "Enter a sentence: ", 0
    sentence resb 256
    format db "%s", 0
    endline db 10, 0

; our code starts here
segment code use32 public code
    start:
        push input_message
        call [printf] ; print on the console the input message
        add esp, 4
    
        push sentence ; offset to sentence
        push format ; offset to format %s
        call [scanf] ; read from keyboard the sentence
        add esp, 4 * 2
        
        push sentence
        call lower_case ; small_case.asm
    
        push eax
        call [printf] ; print result from the lower_case subprogram
        add esp, 4
        
        push endline
        call [printf] ; print an endline
        add esp, 4
        
        push sentence
        call upper_case ; big_case.asm
        
        push eax
        call [printf] ; print result from upper_case subprogram
        add esp, 4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
