global strcspn

section .text

strcspn:
	push rbp
	mov rbp, rsp

	mov rax, 0
	mov rcx, 0

	jmp loop

start:
	inc rdi
	inc rcx

loop:
	cmp byte [rdi], 0
	je return

	mov r8, rsi
	jmp find

start_find:
	inc r8

find:
	mov r9b, byte [rdi]
	mov r10b, byte [r8]

	cmp r9b, r10b
	je return

	cmp r10b, 0
	je start

	cmp r9b, r10b
	jne start_find

return:
	mov rax, rcx

	mov rsp, rbp
	pop rbp

	ret
