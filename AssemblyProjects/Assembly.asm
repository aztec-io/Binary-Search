INCLUDE Irvine32.inc
;basic asm setup
.386
.model flat,stdcall 
.stack 4096
ExitProcess PROTO, dwExitCode:DWORD

.data ; declare variables here
mainString BYTE "Report Salesperson (1-4): ",0
secondString BYTE "units: ",0
thirdString BYTE "product #: ",0

userInput DWORD ?
array WORD 0,0,0,0,0
RowSize = ($-array)/2
	  WORD 0,0,0,0,0
	  WORD 0,0,0,0,0
	  WORD 0,0,0,0,0

.code 

calc_row_sum PROC USES ebx ecx edx esi
	mul ecx
	add ebx, eax
	mov eax, 0
	mov esi, 0
	L1: movzx edx, BYTE PTR[ebx+esi]
	add eax, edx
	inc esi
	loop L1
	ret
calc_row_sum ENDP

main PROC ; write your code here

Start:
	mov edx, OFFSET mainString
	call WriteString
	call ReadInt
	mov userInput, eax
	cmp	userInput, 0 ; Jump if its a negative number.
	jl table
	cmp userInput, 5 ; jump if greater than or equal to 5.
	jge Start
	cmp userInput, 0 ;jump if equal to 0. Valid only 1-4 
	je Start

	sub userInput, 1
	mov ebx, OFFSET array
	mov edx, userInput
	mov eax, RowSize
	mul edx
	add ebx, edx


	mov edx, OFFSET secondString
	call WriteString
	call ReadInt
	mov ecx, eax


	mov edx, OFFSET thirdString
	call WriteString
	call ReadInt
	mov userInput, eax
	sub userInput, 1

	mov esi, userInput


	mov [ebx+esi], ecx

	jmp Start

;Display table output.
table:
	row_index = 0
	mov ecx, row_index*RowSize
	mov ebx, OFFSET array
	mov eax, 0
	call calc_row_sum

	INVOKE ExitProcess,0 
main ENDP ; (insert additional procedures here) 
END main