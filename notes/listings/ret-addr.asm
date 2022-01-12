global _start

section .text
f:
  sub rsp, 24
  ; ...
  add rsp, 24
  ret

_start:
   call f
   mov rax, 60
   mov rdi, 0
   syscall

