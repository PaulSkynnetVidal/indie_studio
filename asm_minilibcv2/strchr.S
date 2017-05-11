global strchr

section .text

strchr:
	push rbp		;;prologue
	mov rbp, rsp

	mov rax, 0		;;return à NULL cas sans occurence

.loop:
	cmp [rdi], sil		;;compare la chaine et le caractere
	je .occurence		;;saut a occurence
	cmp byte[rdi], 0	;;compare chaine de caractere avec NULL
	je .return		;;si chaine egale a NULL va return NULL
	inc rdi			;;incremente chaine de charact
	jmp .loop		;;boucle sur loop

.occurence:
	mov rax, rdi		;;met l'occurence en valeur de retour

.return:
	mov rsp, rbp		;;epilogue
	pop rbp

	ret
