; =======================================================================
; int myprintf(const char *format, ...)
; Supported specifiers:
;   - %c - one character;
;   - %s - a c-string;
;   - %% - a single '%';
;   - %d - decimal integer (int32_t)
;   - %x - hex integer (int32_t)
;   - %o - octal integer (int32_t)
;   - %b - binary integer (int32_t)
; =======================================================================

global _Z9my_printfPKc

%define CHARBUF_SIZE 20

section .text

_Z9my_printfPKc:
            push rbx
            push rbp
            push r12
            push r13
            push r14
            push r15

            ; before first call of print_char
            xor eax, eax
            xor r11, r11

            ; =====================================
            ; main loop
main_loop:  mov r10b, [rdi]
            inc rdi
            
            cmp r10b, '%'
            je specf
            
            cmp r10b, '\'
            je slash

            ; common char or 0x0
            call print_char

            cmp r10b, 0x0
            jne main_loop
            jmp printf_end
            ; ---------------
            ; specf
specf:

            ; ---------------
            ; slash
slash:

            jmp main_loop
            ; =====================================
            ; end of main_loop
printf_end: 

            pop r15
            pop r14
            pop r13
            pop r12
            pop rbp
            pop rbx

            ret

; =======================================================================
; print_char
; Description:
;   Gets one char, stores it into internal buffer. When it's full, calls
;   syscall write to stdout and resets the buffer. If given char is zero 
;   byte ('\0'), doesn't store it and flushes buffer immediately. 
;   Increments number of written bytes (see args) or sets it to -1 in 
;   case of writing error.
; Args:
;   - r10b - char to store to buffer and print.
;   - eax  - stores number of already written bytes here, or sets it to -1
;           in case of error.
; Other used regs: 
;   - r11 - index in the buffer, must be set to 0 before first call of 
;           this func; must not be changed outside of this func.
; =======================================================================
print_char:
            cmp r10b, 0x0
            je flush_buf

            cmp eax, -1     ; check if error already happened
            je prn_chr_end

            mov [charbuf + r11], r10b
            inc r11

            cmp r11, CHARBUF_SIZE
            je flush_buf
            
            ret

flush_buf:  
            push rdi
            push rsi
            push rdx
            push rax 

            mov rdx, r11            ; num of bytes to write
            mov rax, 0x1            ; syscall number - write
            mov rdi, 0x1            ; stdout
            lea rsi, [charbuf]      ; buffer pointer
            syscall

            ; now eax stores -1 or number of written bytes
            cmp eax, -1
            je prn_chr_end
            add eax, [rsp] ; adding to eax its previous value 

            xor r11, r11

prn_chr_end: 
            ; if eax equals -1, it must be -1 still; otherwise
            ; it already has the needed value
            add rsp, 0x8    ; skipping eax

            pop rdx
            pop rsi
            pop rdi
            ret



section .data

charbuf: db CHARBUF_SIZE dup(0)