global strlen

section .text

strlen:
	push rbp		;;prologue
	mov rbp, rsp

	mov rcx, 0		;;initilisation du compteur

loop:				;;boucle du compteur
	cmp byte [rdi], 0		;;compare la chaine de caratere avec \0
	je return		;;si egal passe à return
	inc rcx			;;sinon incremente compteur
	inc rdi
	jmp loop		;;boucle sur loop

return:
	mov rsp, rbp		;;epilogue
	pop rbp
	mov rax, rcx		;;place le compteur dans le return
	ret
