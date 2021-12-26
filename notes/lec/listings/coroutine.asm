global _start

section .data
message: db  'world!', 10
hello:   db  'hello '

section .text
print_hello:
    mov rdi, hello
    mov rsi, 6          ; string length in bytes
print_string:
    mov     rdx, rsi    ; rdx <- length
    mov     rsi, rdi    ; rsi <- string address
    mov     rdi, 1      ; stdout
    mov     rax, 1      ; 'write' syscall number
    syscall
    ret
_start:
    call print_hello
    mov rdi, message
    mov rsi, 7
    call print_string

    mov     rax, 60     ; 'exit' syscall number
    xor     rdi, rdi
    syscall
