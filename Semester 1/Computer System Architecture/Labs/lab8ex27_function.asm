; A character string is given (defined in the data segment). 
; Read one character from the keyboard, 
; then count the number of occurences of that character in the given string 
; and display the character along with its number of occurences.

bits 32
global start
extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
	string db "ana are mere"
	str_len equ $ - string
	character db 0
	input_message db "Enter a character: ", 0
	char_format db "%c", 0
	output_format db "The character %c appears %d times in the string", 0

segment code use32 class=code
start:
	push input_message
	call [printf]
	add esp, 4

	push character
	push char_format
	call [scanf]
	add esp, 4 * 2

	mov ecx, str_len
	mov esi, string
	jecxz ending

	mov ebx, 0 ; ebx counts the number of occurences of the character in the given string

	str_loop:
		lodsb ; al = s[i]
		cmp al, [character]
		je inc_occ
	loop str_loop

	inc_occ:
		jecxz after
		inc ebx
		loop str_loop
	after:
		push ebx
		push dword[character]
		push output_format
		call [printf]
		add esp, 4 * 3

	ending:
		push dword 0 
		call [exit] 
