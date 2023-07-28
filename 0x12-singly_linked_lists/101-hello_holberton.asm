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
    lea rdi, [hello]              ; Pointer to the format string
    xor eax, eax                  ; Clear EAX to indicate printf (syscall number 0)
    call printf                   ; Call the printf function

    ; Restore the stack frame and return
    pop rbp
    ret

