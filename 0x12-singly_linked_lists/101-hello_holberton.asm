section .data
	hello db "Hello, Holberton", 10
section .text
	extern printf
	global main

main:
	push rbp
	mov rbp, rsp

	mov rdi, hello
	mov eax, 0
	call printf

	pop rbp
	ret
