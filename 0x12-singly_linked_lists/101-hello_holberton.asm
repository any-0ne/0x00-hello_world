section .data
	hello db "Hello, Holberton", 10

section .text
	extern printf
	global main

main:
    ; Set up the stack frame
	push rbp
	mov rbp, rsp

    ; Prepare the arguments for printf
	mov rdi, hello
	mov eax, 0
	call printf

    ; Restore the stack frame and return
    pop rbp
    ret

