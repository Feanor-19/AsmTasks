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

global _Z9my_printfPKcz

%define CHARBUF_SIZE 10

section .text

_Z9my_printfPKcz:
            ; ============================================    
            ; preparing stack frame, so that all POTENTIAL
            ; arguments are located in order in stack

            pop r10 ; saving ret code

            ; pushing POTENTIAL arguments in reverse order
            push r9
            push r8
            push rcx
            push rdx
            push rsi

            mov r11, rsp ; saving reference stack pointer

            push r10 ; pushing ret code

            ; ============================================
            push rbx
            push rbp
            push r12
            push r13
            push r14
            push r15

            mov rbp, r11 ; now r11 is free

            ; before first call of print_char
            xor eax, eax
            xor r11, r11
            xor r10, r10

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
specf:      mov r10b, [rdi]
            inc rdi
            call hndl_specf

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

            ; ======================================
            ; fixig stack frame and ret

            pop r11         ; popping ret code
            add rsp, 5*8    ; throwing out potential register args
            push r11        ; ret code
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
; Expects: 
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

; =======================================================================
; hndl_specf
; Description:
;   Handles situation when specifier like '%S' is met in the format 
;   string. 'S' fully specifier which specifier it is.
; Supported specifiers (case sensitive!):
;   - %%    - just one character '%'   - no arg;
;   - %c    - one character            - int8_t (char)
;   - %s    - C-string                 - const char *
;   - %d    - decimal integer          - int32_t
;   - %x    - hex integer              - int32_t
;   - %o    - octal integer            - int32_t
;   - %b    - binary integer           - int32_t
; Arguments:
;   - r10   - the character 'S' (see description)
; Expects:
;   - rbp - to point at the next to be used argument in stack 
;           (considering all args as 8 bytes)
; ATTENTION:
;   Nothing happens if the specifier is not identified.
; =======================================================================
hndl_specf:
%define SPECF_SMALLEST 'b' ; specifier with the smallest ascii value
%define SPECF_BIGGEST  'x' ; specifier with the biggest ascii value

            cmp r10b, '%'
            je specf_perc

            cmp r10b, SPECF_BIGGEST
            ja hndl_specf_end       ; unrecognized, skipping

            sub r10b, SPECF_SMALLEST
            jmp [jmp_table + r10*8]

specf_b:    

specf_c:    mov r10b, [rbp]
            call print_char
            add rbp, 0x8
            ret

specf_d:    

specf_o:

specf_s:

specf_x:

specf_perc: call print_char ; just print '%', which is already in the r10b 

hndl_specf_end:
            ret

section .rodata
align 8
jmp_table:
dq specf_b
dq specf_c
dq specf_d
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq specf_o
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq specf_s
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq hndl_specf_end
dq specf_x

section .data

charbuf: db CHARBUF_SIZE dup(0)