; A text file is given. The text file contains numbers (in base 10) separated by spaces. Read the content of the file, determine ; the minimum number (from the numbers that have been read) and write the result at the end of file.
bits 32
global start

extern exit, fopen, fscanf, fclose, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
	file_descriptor dd -1
	file_name db "file.txt", 0
	mode db "a+", 0
	format db "%d", 0
	element dd 0
	minimum dd 2147483647

segment code use32 class=code
start:
	push mode
	push file_name
	call [fopen] ; eax = file descriptor
	add esp, 4 * 2 ; clean-up the stack
	mov [file_descriptor], eax

	cmp eax, 0 ; if file didnt open we go to the end
	je ending

	read_loop:
        ; fread(void * str, int size, int count, FILE * stream)
		push element ; address to store the element
        push format ; address to the format of integers
		push dword [file_descriptor]
		call [fscanf]
		add esp, 4 * 3 ; clean-up the stack
   
        cmp eax, -1 ; for fscanf if eax = -1 then we are encountered EOF (end of file)
        je end_of_file

        mov edx, [element]
		cmp [minimum], edx ; we compare minimum value with current element from the file
		jbe read_loop

		mov [minimum], edx ; this executes only when minimum > current_element
		jmp read_loop

	end_of_file:
		push dword [minimum] ; the number to be appended at the end of the file
		push format ; the format for the number
		push dword [file_descriptor] ; the corresponding file descriptor
		call [fprintf]
		add esp, 4 * 3 ; clean-up the stack
		push dword [file_descriptor] ; close the file
		call [fclose]
		add esp, 4 ; clean-up the stack
	ending:
		push dword 0 
		call [exit] 
