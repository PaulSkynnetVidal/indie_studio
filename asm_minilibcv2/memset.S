global memset

section .text

memset:
	push rbp		;;prologue
	mov rbp, rsp

	mov rax, rdi		;;return le pointeur

loop:
	cmp rdx, 0		;;compare si n egal 0
	jle return		;;si egale ou inf passe à return
	mov byte [rdi], sil	;;ecrit l'octet dans la zone memoire
	dec rdx			;;décremente jusqu'à 0
	inc rdi			;;incremente la case de remplisage
	jmp loop		;;boucle sur loop

return:
	mov rsp, rbp		;;epilogue
	pop rbp
	ret
