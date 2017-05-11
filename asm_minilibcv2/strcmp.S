global strcmp

section .text

strcmp:
	push rbp		;;prologue
	mov rbp, rsp

	mov rax, 0		;;met le return à NULL

cmp:
	mov r10b, byte [rdi]	;;sauvegarde le premier param
	mov r11b, byte [rsi]	;;sauvegarde le deuxieme param
	cmp r10b, 0		;;compare premier param avec NULL
	je mismatch		;;si NULL passe a la fonction mismatch
	cmp r11b, 0		;;compare deuxieme param avec NULL
	je mismatch		;;si NULL passe a la fonction mismatch
	cmp r10b, r11b		;;compare les deux chaine
	je match		;;si egal passe a la fonction match
	jmp mismatch		;;passe a la fonction mismatch si different

match:
	inc rdi			;;incremente rdi
	inc rsi			;;incremente rsi
	jmp cmp			;;boucle sur cmp

mismatch:
	mov r8b, [rdi]		;;place le premier param dans r8b
	mov r9b, [rsi]		;;place le deuxieme param dans r9b
	sub r8b, r9b		;;soustraction entre les deux param
	movsx rax, r8b		;;met le resultat dans le return

return:
	mov rsp, rbp		;;epilogue
	pop rbp

	ret
