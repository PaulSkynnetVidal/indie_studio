global memcpy

section .text

memcpy:
	push rbp		;;prologue
	mov rbp, rsp

	mov rcx, 0
	mov rax, rdi		;;return le pointeur

.loop:
	cmp rdi, rsi
	je .return		;;si egale passe à return
	cmp rcx, rdx
	jge .return
	mov r8b, [rsi]
	mov [rdi], r8b
	inc rdi			;;va a la prochaine case du pointeur
	inc rsi			;;incremente la deuxieme chaine
	inc rcx
	jmp .loop		;;bloucle sur loop

.return:
	mov rsp, rbp		;;epilogue
	pop rbp
	ret
