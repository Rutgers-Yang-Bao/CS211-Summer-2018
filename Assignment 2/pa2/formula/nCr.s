	.file	"nCr.c"
	.text
	.globl	nCr
	.type	nCr, @function
nCr:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	-20(%rbp), %edi
	movl	$0, %eax
	call	Factorial
	movl	%eax, -4(%rbp)
	movl	-24(%rbp), %edi
	movl	$0, %eax
	call	Factorial
	movl	%eax, -8(%rbp)
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	subl	%edx, %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	Factorial
	movl	%eax, -12(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	movl	-8(%rbp), %eax
	imull	-12(%rbp), %eax
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	cltd
	idivl	%ecx
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	nCr, .-nCr
	.globl	Factorial
	.type	Factorial, @function
Factorial:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$20, -4(%rbp)
	jle	.L5
	movl	$0, %eax
	jmp	.L6
.L5:
	cmpl	$0, -4(%rbp)
	jg	.L7
	movl	$1, %eax
	jmp	.L6
.L7:
	movl	-4(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	Factorial
	imull	-4(%rbp), %eax
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	Factorial, .-Factorial
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-16)"
	.section	.note.GNU-stack,"",@progbits
