; =======================================================================
; int myprintf(const char *format, ...)
; Supported specifiers:
;   - %c - one character;
;   - %s - a c-string;
;   - %% - a single '%';
;   - %d - decimal integer (int32_t)
;   - %x - hex integer (uint32_t)
;   - %o - octal integer (uint32_t)
;   - %b - binary integer (uint32_t)
; =======================================================================

%define GLOBAL_FUNC_NAME _Z9my_printfPKcz
%define CHARBUF_SIZE 16

global GLOBAL_FUNC_NAME
;//TODO - исправить rsi на esi, потому что блин int, а не long
section .text

GLOBAL_FUNC_NAME:
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
            jmp hndl_specf

            ; ---------------
            ; slash
slash:

            ; ------------------------------------
            ; back to loop, if not 0x0
hndl_specf_end:
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
; hndl_specf - DON'T USE CALL, USE JMP
; Description:
;   Handles situation when specifier like '%S' is met in the format 
;   string. 'S' fully specifier which specifier it is.
; Supported specifiers (case sensitive!):
;   - %%    - just one character '%'   - no arg;
;   - %c    - one character            - uint8_t (unsigned char)
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

            cmp r10b, '%'           ; doesn't need arg, handled separately
            je specf_perc

            cmp r10b, SPECF_BIGGEST ; if unrecognized, skip
            ja hndl_specf_end       

            ; all the rest need an arg, getting it into rsi
            mov rsi, [rbp]
            add rbp, 0x8

            ; and now jmp to corresponding specifier handler
            sub r10b, SPECF_SMALLEST
            jmp [jmp_table + r10*8]

            ; treating '%%' specially
specf_perc: call print_char ; just print '%', which is already in the r10b 
            jmp hndl_specf_end

            ; there is no ret, because every specifier handler jmps to
            ; label 'hndl_specf_end', which is located in the main loop
; =======================================================================
; Specifiers handlers. 
; Expects:
;    Each of them expects the argument to be in rsi.
; ==========================================================================
; Macro for converting & printing, supports BIN, HEX (AND POTENTIALLY BASE 4)
; Macro argumets:
;   %1) number of bits to represent one digit (1 for BIN, 4 for HEX, etc)
;   %2) BIN | HEX
; Expects:
;   Number to convert and print in rsi
; ==========================================================================
%macro      ConvertBH 2

            xor rbx, rbx

            ; skipping leading zeroes
            mov ecx, 64 / %1
%%nzero:    rol rsi, %1
            mov bl, sil
            and bl, (1 << %1) - 1
            cmp bl, 0
            loope %%nzero

            jz %%num_0    ; the number to print is zero, special case
            ror rsi, %1
            inc ecx

%%loop:     rol rsi, %1
            mov bl, sil
            and bl, (1 << %1) - 1
            mov r10b, [%2 + rbx]
            mov r12, rcx ; saving
            call print_char
            mov rcx, r12  
            loop %%loop

            jmp hndl_specf_end ; instead of ret

            ; if the number to print is 0
%%num_0:    mov r10b, [%2]
            call print_char

            jmp hndl_specf_end ; instead of ret

%endmacro
; ==========================================================================
; Macro for converting into bases [2, 10]
; Macro argumets:
;   %1) the base: 2, or 3, or 4... or 10
; Expects:
;   Number to convert and print in esi
; ==========================================================================
%macro      ConvertCmn 1
            mov r12, rax    ; saving

            ; --------------------------------------------------------------
            ; if the base is 10 and number < 0, print '-' and turn off the highest bit
%if %1 == 10
            test esi, 1 << 31
            jz %%skip_abs
            mov r10b, '-'
            call print_char
            and esi, (1 << 32) - 1 - (1 << 31)
%endif

%%skip_abs: 
            xor rdx, rdx
            xor rax, rax
            mov eax, esi
            mov ebx, %1 ; because div doesn't support immc
            xor rcx, rcx

%%loop_fw:  div ebx
            push rdx
            inc rcx
            xor rdx, rdx
            cmp eax, 0
            jne %%loop_fw
            
            mov rax, r12 ; restoring rax

%%loop_bw:  pop r10
            add r10, '0'
            mov r12, rcx    ; saving
            call print_char
            mov rcx, r12
            loop %%loop_bw

%endmacro
; ==========================================================================
specf_b:    ConvertBH 1, BIN

            jmp hndl_specf_end ; instead of ret
; ==========================================================================
specf_c:    mov r10, rsi
            call print_char
            jmp hndl_specf_end ; instead of ret
; ==========================================================================
specf_d:    ConvertCmn 10

            jmp hndl_specf_end
; ==========================================================================
specf_o:    ConvertCmn 8

            jmp hndl_specf_end
; ==========================================================================
specf_s:

; ==========================================================================
specf_x:    ConvertBH 4, HEX

            jmp hndl_specf_end ; instead of ret
; ==========================================================================
section .rodata
HEX:        db '0123456789ABCDEF' 
OCT:        db '01234567'
BIN:        db '01'

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