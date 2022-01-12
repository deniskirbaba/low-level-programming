global _start
section .data
input:   db "d234", 0

section .text

;;  after this function:
;;  if rdi pointed at a correct textual representation of a number,
;;  then rdx = 1, rax = 1
;;  otherwise rdx = 0, rax can be any value
check_number:

state_a:
mov al, [rdi]
add rdi, 1

cmp al, '-'
je state_b
cmp al, '+'
je state_b
cmp al, '9'
ja state_e
cmp al, '0'
jb state_e
jmp state_c

state_b:
mov al, [rdi]
add rdi, 1
cmp al, '9'
ja state_e
cmp al, '0'
jb state_e	
jmp state_c

state_c:
mov al, [rdi]
add rdi, 1
cmp al, 0
je state_d
cmp al, '9'
ja state_e
cmp al, '0'
jb state_e
jmp state_c
state_d:
mov rax, 1
ret
state_e:
mov rax, 0
ret
;;  rdi = program return code
exit_with_code:
mov rdi, rax
mov rax, 60
syscall
_start:
mov rdi, input
call check_number
call exit_with_code
