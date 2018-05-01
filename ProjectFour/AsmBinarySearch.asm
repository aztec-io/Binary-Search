TITLE AsmBinarySearch Procedure (AsmBinarySearch.asm)

	.586
	.model flat,C

	AsmBinarySearch PROTO, searchValue:DWORD, arrayPTR:PTR DWORD, count:DWORD

	.data

	.code
	;----------------------------------------------------------
	AsmBinarySearch PROC USES edi, searchValue:DWORD, arrayPTR:PTR DWORD, count:DWORD
	;
	; Performs a binary search for a 32 - bit integer
	; in an array of integers. Returns the value of the subscript
	; of the matching array element in EAX, or -1 in EAX if the
	; search value was not found in the array.
	; ----------------------------------------------------------
	LOCAL first:DWORD,
	last:DWORD,
	mid:DWORD

	mov first,0
	mov eax, count
	dec eax
	mov last, eax
	mov edi, searchValue ; edi is searchValue
	mov ebx, arrayPTR ; ebx points to the array

L1:
	mov eax, first
	cmp eax, last
	jg L5 ;Quit search

	mov eax, last
	add eax, first
	shr eax, 1
	mov mid, eax

	mov esi, mid
	shl esi, 2
	mov edx, [ebx+esi]

	cmp edx, edi
	jge L2
	
	mov eax, mid
	inc eax
	mov first, eax
	jmp L4

L2:
	cmp edx, edi
	jle L3

	mov eax, mid
	dec eax
	mov last, eax
	jmp L4

L3:
	mov eax, mid
	jmp L0

L4:
	jmp L1

L5:
	mov eax, -1 ;search didnt work

L0:
	ret


	
	;mov	eax,searchValue		; Set the return value to indicate that
	;jmp	short omega	; the search value was not found.

;omega:
	;ret			; return
AsmBinarySearch ENDP
END
