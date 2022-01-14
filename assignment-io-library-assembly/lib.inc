section .text


; Принимает код возврата и завершает текущий процесс
exit:
    mov rax, 60                     ; 'exit' syscall number
    syscall


; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
                                    ; rdi - string pointer

    xor rax, rax                    ; rax will hold string length
    
    .loop:                          ; main loop starts here
        cmp byte [rdi+rax], 0       ; Check if the current symbol is null-terminator

        je .end                     ; Jump if we found null-terminator

        inc rax                     ; Otherwise go to next symbol and increase counter
        jmp .loop

    .end:
        ret


; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
	call string_length              ; find length of our string

    mov rsi, rdi                    ; where do we take data from
    mov rdx, rax                    ; the amount of bytes to write
    mov rax, 1                      ; 'write' syscall identifier
    mov rdi, 1                      ; stdout file descriptor

    syscall                         ; printing string
    ret


; Принимает код символа и выводит его в stdout
print_char:
	push rdi
	mov rdi, rsp
	call print_string
	pop rdi
    ret


; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov rdi, 0xA                    ; 0xA = '\n' = newline
    jmp print_char


; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
    mov r8, rsp                     ; save the stack
	mov r9, 10                      ; the base of ns
	mov rax, rdi
	push 0

	.loop:
		xor rdx, rdx                ; clear
		div r9                      ; unsigned division
		add rdx, '0'	
		dec rsp		
		mov byte[rsp], dl           ; put the number in stack
		cmp rax, 0			
		jnz .loop
	
		mov rdi, rsp
		push r8
		call print_string	
		pop r8		
		mov rsp, r8

    ret


; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
    cmp rdi, 0                      ; sign checking
    jl .if_negative
    call print_uint

    ret

    .if_negative:
        push rdi
        mov rdi,'-'
        call print_char
        pop rdi
        neg rdi
        
        jmp print_uint


; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    .loop:
		mov al, byte[rsi]
		cmp al, byte[rdi]

		jne .not_equal
		inc rdi
		inc rsi
		test al, al
		jnz .loop
		mov eax, 1                  ; resetting the register

		ret

	.not_equal:
		xor rax, rax                ; resetting the register

		ret


; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
	xor rax, rax                    ; resetting the register
	push 0

    mov rdi, 0                      ; stdin file descriptor
    mov rsi, rsp                    ; where do we store data in
    mov rdx, 1                      ; the amount of bytes to read
    syscall

    pop rax

    ret


; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор

read_word:
                                    ;rdi - buffer pointer
                                    ;rsi - buffer size
	
	xor rdx, rdx                    ; resetting the register

    .loop:                          ; main loop
        cmp rdx, rsi                ; if buff sz = 0
        je .error
        							
                                    ; read next char
    	push rdx
    	push rdi
    	push rsi
    	
        call read_char 
        
        pop rsi
        pop rdi
        pop rdx
       								
                                    ; check for ' ', '\t', '\n'
        cmp rax, 0x20               ; 0x20 = ' ' = whitespace				
        je .skipping_whitespace
        cmp rax, 0x9                ; 0x9 = '\t' = tabulation
        je .skipping_whitespace
        cmp rax, 0xA                ; 0xA = '\n' = newline
        je .skipping_whitespace

                                    ; check for end of string
        cmp rax, 0
        je .end_of_string
        
        mov byte[rdi+rdx], al       ; adding symbol
        
        inc rdx
        jmp .loop                   ; next iteration
        
    .error:                         ; error case
    	xor rax, rax
    	ret

    .skipping_whitespace:           ; whitespaces case
    	test rdx, rdx
    	je .loop

    .end_of_string:                 ; successfull ending
    	mov rax, rdi
    	mov byte[rdi+rdx], 0
    	ret
 

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
                                    ; rdi - string pointer

    xor rax, rax                    ; resetting register
    xor rdx, rdx                    ; resetting register
    xor rcx, rcx                    ; resetting register

    .loop:                          ; main loop
        mov dl, byte [rdi + rcx]

        cmp dl, '9'
        jg .exit
        cmp dl, '0'
        jl .exit

        sub dl, '0'
        imul rax, 10 
        add rax, rdx
        inc rcx

        jmp .loop

    .exit:
    	mov rdx, rcx
        ret


; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
                                    ; rdi - string pointer
									
    xor rax, rax                    ; resetting register
    xor rdx, rdx                    ; resetting register

    cmp byte[rdi], '-'

                                    ; negative number case
    jne parse_uint

                                    ; to all numbers
  	inc rdi
    call parse_uint
    neg rax
    inc rdx

    ret


; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
                                    ; rdi - string pointer
                                    ; rsi - buffer pointer
                                    ; rdx - buffer size
	
	xor rax, rax                    ; resetting register

                                    ; saving params
    push rdi						
    push rsi
    push rdx

    call string_length

                                    ; restoring params
    pop rdx
    pop rsi
    pop rdi

    inc rax                         ; accounting for the null terminator
    
    cmp rax, rdx                    ; check for buffer capacity
    ja .buffer_capacity_error
    
    xor rcx, rcx

	.loop:                          ; main loop - string copy
    	mov r8b, byte[rdi + rcx]
    	mov [rsi + rcx], r8b
    	inc rcx
    	cmp rcx, rax
    	jb .loop

	.exit:                          ; successfull exit from func
    	dec rax
    	ret
	
	.buffer_capacity_error:         ; buffer capacity is not enough
    	xor rax, rax        
    	ret
