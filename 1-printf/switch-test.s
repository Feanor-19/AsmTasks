	.file	"switch-test.cpp"
	.intel_syntax noprefix
	.text
	.globl	_Z4testc
	.type	_Z4testc, @function
_Z4testc:
.LFB0:
	.cfi_startproc
	endbr64
	cmp	dil, 37
	je	.L10
	sub	edi, 98
	movzx	edi, dil
	lea	rdx, .L5[rip]
	movsx	rax, DWORD PTR [rdx+rdi*4]
	add	rax, rdx
	notrack jmp	rax
	.section	.rodata
	.align 4
	.align 4
.L5:
	.long	.L9-.L5
	.long	.L8-.L5
	.long	.L7-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L6-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L11-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.long	.L4-.L5
	.text
.L8:
	mov	eax, 99
	ret
.L7:
	mov	eax, 100
	ret
.L4:
	mov	eax, 120
	ret
.L6:
	mov	eax, 111
	ret
.L9:
	mov	eax, 98
	ret
.L10:
	mov	eax, 37
	ret
.L11:
	mov	eax, 115
	ret
	.cfi_endproc
.LFE0:
	.size	_Z4testc, .-_Z4testc
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
