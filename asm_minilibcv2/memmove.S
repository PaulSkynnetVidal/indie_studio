global memmove

section .text

memmove:
	push rbp		;;prologue
	mov rbp, rsp

	mov rax, rdi		;;valeur de return sur 1er arg
	mov rcx, rdx		;;save n dans un tmp
	sub rcx, 1		;;sub le tmp de 1
	mov r9, -1		;;met r9 a -1
	mov r10, -1		;;same

	cmp rdi, rsi		;;compare les deux chaine
	jg loop			;;si superieur passe a loop

	mov rcx, 0		;;met le tmp a 0
	mov r9, 1		;;r9 a 1
	mov r10, rdx		;;r10 prend n

loop:
	cmp rcx, r10		;;cmp tmp et n
	je return		;;si egale return

	mov r8b, [rsi + rcx]	;;place dans un tmp2: src + tmp1
	mov [rdi + rcx], r8b	;;met le tmp2 dans dest + tmp1

	add rcx, r9		;;add r9 a rcx
	jmp loop		;;boucle

return:

	mov rsp, rbp		;;epilogue
	pop rbp

	ret
