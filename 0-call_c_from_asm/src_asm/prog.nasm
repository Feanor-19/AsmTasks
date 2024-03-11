; =======================================================================
;       Second test: call C-func from asm.
; =======================================================================

section .text

extern printf
extern my_add

global _start

%define first_num 0x2
%define second_num 0x3

_start:     
            mov edi, first_num
            mov esi, second_num
            call my_add     ; eax = edi + esi
            
            mov rdi, Msg
            mov esi, first_num
            mov edx, second_num
            mov ecx, eax
            call printf            

            mov rax, 0x3C      ; exit64 (rdi)
            xor rdi, rdi
            syscall
            
section     .data
            
Msg:        db "%d+%d = %d! (It is printed using 'printf'!!!)", 0x0a, 0
