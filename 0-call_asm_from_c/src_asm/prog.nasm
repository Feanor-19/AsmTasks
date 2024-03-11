; =======================================================================
;       Third test: call asm-func from C.
; How to learn mangled function's name:  
; 1) gcc -o lst/c.s -S -masm=intel src_c/c.cpp
; 2) Find 'call *your func*' and copy the name.
; =======================================================================

section .text

global _Z6my_mulii

_Z6my_mulii:     
            mov eax, edi
            imul eax, esi
            ret
