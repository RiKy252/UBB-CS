bits 32
global start

extern exit, fopen, fread, printf, fclose, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
	file_descriptor dd -1
	file_name db "file.txt", 0
	mode db "a+", 0
	format db "%d", 0
	element dd 0
	minimum dd 0

segment code use32 class=code
start:
	push mode
	push file_name
	call [fopen]
	add esp, 4 * 2
	mov [file_descriptor], eax

	cmp eax, 0
	je ending
	mov edx, 55555

	read_loop:
		push dword [file_descriptor]
		push dword 1
		push dword 4
		push element
		call [fread]
		add esp, 4 * 4

		cmp eax, 0
		je end_of_file

		cmp edx, [element]
		jbe read_loop

		mov edx, [element]
		mov [minimum], edx
		jmp read_loop

	end_of_file:
		push dword [minimum]
		push format 
		push dword [file_descriptor]
		call [fprintf]
		add esp, 4 * 3
		push dword [file_descriptor]
		call [fclose]
		add esp, 4
	ending:
		push dword 0 
		call [exit] 
