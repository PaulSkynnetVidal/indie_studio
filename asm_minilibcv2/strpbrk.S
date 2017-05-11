global strpbrk

section .text

strpbrk:
	push rbp
	mov rbp, rsp		;;prologue

	mov rax, 0		;;valeur de retur initialisé a NULL

loop:
	mov r9, rsi
	cmp byte [rdi], 0	;;compare premier param avec NULL
	je return		;;si NULL passe a la fonction return
	mov r10b, byte [rsi]
	cmp byte [rdi], r10b	;;compare les deux param
	je match		;;si egal passe a la fonction match
	jmp check_next_accept

check_next_accept:
	cmp byte [r9], 0
	je check_s
	mov r11b, byte [r9]
	cmp byte [rdi], r11b
	je match
	inc r9
	jmp check_next_accept

check_s:
	inc rdi
	jmp loop

match:
	mov rax, rdi		;;met le pointeur en valeur de return

return:
	mov rsp, rbp		;;epilogue
	pop rbp

	ret
