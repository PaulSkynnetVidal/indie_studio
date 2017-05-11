global rindex

section .text

rindex:
	push rbp		;;prologue
	mov rbp, rsp

	mov rax, 0		;;valeur de return initialisé a NULL

loop:
	mov r8b, byte [rdi]

	cmp r8b, 0
	je return

	cmp r8b, sil
	je match

	jmp mismatch


match:
	xor rax, rax
	mov rax, rdi		;;met la charactere en valeur de return
	inc rdi
	jmp loop

mismatch:
	inc rdi
	jmp loop

return:
	mov rsp, rbp		;;epilogue
	pop rbp

	ret
