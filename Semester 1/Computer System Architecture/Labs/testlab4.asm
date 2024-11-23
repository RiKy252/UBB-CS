bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
		; msvcrt.dll contains exit, printf and all the other important C-runtime functions

; our variables are declared here (the segment is called data) 
segment data use32 class=data
    A dq 0xABCDEFABCDEFABCD
    B dd 0
    C db 0
    ; Given the quadword A, obtain the integer number N represented on the bits 35-37 of A. 
    ; Then obtain the the doubleword B by rotating the low doubleword of A N positions to the right. 
    ; Obtain the byte C as follows:
    ; the bits 0-3 of C are the same as the bits 8-11 of B
    ; the bits 4-7 of C are the same as the bits 16-19 of B
; the program code will be part of a segment called code
segment code use32 class=code
start:
    mov EAX, [A]
    mov EDX, [A + 4] ; EDX:EAX = A
    and EDX, 00000000000000000000000000000000b ; higher part of EDX:EAX are bits 0-31
    and EAX, 00011100000000000000000000000000b ; lower part of EDX:EAX are bits 32-64
    shl EAX, 3 ; EAX = 011000.... 32 bits
    push EAX
    pop DX
    pop AX ; DX = 011000... 16 bits
    mov CL, AH ; CL = 01100000 = 6 in decimal, CL = N
    mov EAX, [A] ; EAX = low doubleword of A
    ror EAX, CL ; EAX = B
    mov [B], EAX

	; call exit(0) ), 0 represents status code: SUCCESS
	push dword 0 ; saves on stack the parameter of the function exit
	call [exit] ; function exit is called in order to end the execution of the program