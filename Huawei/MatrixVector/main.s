	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC8:
	.string	"Finished: %f, GFLOPS: %f\n"
.LC9:
	.string	"%9.1f "
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB4781:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	$2400, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	malloc@PLT
	movl	$3200, %edi
	movq	%rax, %rbp
	call	malloc@PLT
	movl	$2400, %edi
	movq	%rax, %r12
	call	malloc@PLT
	movq	%rbp, %rdi
	movq	%rax, %rbx
	xorl	%ecx, %ecx
	movdqa	.LC1(%rip), %xmm2
	movl	$20, %r8d
	movdqa	.LC2(%rip), %xmm3
	movdqa	.LC3(%rip), %xmm4
	movdqa	.LC4(%rip), %xmm5
	movdqa	.LC5(%rip), %xmm6
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L36:
	movq	$0x000000000, (%rdi)
	movl	$19, %esi
	movl	$1, 12(%rsp)
.L6:
	movd	12(%rsp), %xmm7
	movl	%r8d, %r9d
	subl	%eax, %r9d
	movl	%eax, %eax
	pshufd	$0, %xmm7, %xmm0
	addq	%rcx, %rax
	movl	%r9d, %r10d
	leaq	0(%rbp,%rax,8), %rax
	shrl	$2, %r10d
	cmpl	$5, %r10d
	movdqa	%xmm0, %xmm7
	movdqa	%xmm0, %xmm1
	paddd	%xmm2, %xmm7
	cvtdq2pd	%xmm7, %xmm8
	pshufd	$238, %xmm7, %xmm7
	paddd	%xmm3, %xmm1
	movaps	%xmm8, (%rax)
	cvtdq2pd	%xmm1, %xmm8
	pshufd	$238, %xmm1, %xmm1
	cvtdq2pd	%xmm7, %xmm7
	movaps	%xmm7, 16(%rax)
	movdqa	%xmm0, %xmm7
	movaps	%xmm8, 32(%rax)
	cvtdq2pd	%xmm1, %xmm1
	paddd	%xmm4, %xmm7
	cvtdq2pd	%xmm7, %xmm8
	pshufd	$238, %xmm7, %xmm7
	movaps	%xmm1, 48(%rax)
	movdqa	%xmm0, %xmm1
	paddd	%xmm6, %xmm0
	cvtdq2pd	%xmm7, %xmm7
	movaps	%xmm7, 80(%rax)
	paddd	%xmm5, %xmm1
	cvtdq2pd	%xmm1, %xmm7
	pshufd	$238, %xmm1, %xmm1
	movaps	%xmm8, 64(%rax)
	cvtdq2pd	%xmm1, %xmm1
	movaps	%xmm7, 96(%rax)
	movaps	%xmm1, 112(%rax)
	jne	.L4
	cvtdq2pd	%xmm0, %xmm1
	pshufd	$238, %xmm0, %xmm0
	movaps	%xmm1, 128(%rax)
	cvtdq2pd	%xmm0, %xmm0
	movaps	%xmm0, 144(%rax)
.L4:
	movl	%r9d, %r10d
	andl	$-4, %r10d
	subl	%r10d, %esi
	movl	12(%rsp), %eax
	addl	%r10d, %eax
	cmpl	%r10d, %r9d
	je	.L3
	pxor	%xmm0, %xmm0
	leal	(%rdx,%rax), %r9d
	cmpl	$1, %esi
	movslq	%r9d, %r9
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, 0(%rbp,%r9,8)
	leal	1(%rax), %r9d
	je	.L3
	pxor	%xmm0, %xmm0
	leal	(%rdx,%r9), %r10d
	addl	$2, %eax
	cmpl	$2, %esi
	movslq	%r10d, %r10
	cvtsi2sd	%r9d, %xmm0
	movsd	%xmm0, 0(%rbp,%r10,8)
	je	.L3
	pxor	%xmm0, %xmm0
	addl	%eax, %edx
	movslq	%edx, %rdx
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, 0(%rbp,%rdx,8)
.L3:
	addq	$20, %rcx
	addq	$160, %rdi
	cmpq	$300, %rcx
	je	.L35
.L2:
	movq	%rdi, %rax
	movl	%ecx, %edx
	shrq	$3, %rax
	andl	$1, %eax
	jne	.L36
	movl	$20, %esi
	movl	$0, 12(%rsp)
	jmp	.L6
.L35:
	movq	%r12, %rdi
	xorl	%ecx, %ecx
	movl	$20, %r8d
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L37:
	movq	$0x000000000, (%rdi)
	movl	$19, %esi
	movl	$1, 12(%rsp)
.L11:
	movd	12(%rsp), %xmm1
	movl	%r8d, %r9d
	subl	%eax, %r9d
	movl	%eax, %eax
	pshufd	$0, %xmm1, %xmm0
	addq	%rcx, %rax
	movl	%r9d, %r10d
	leaq	(%r12,%rax,8), %rax
	shrl	$2, %r10d
	cmpl	$5, %r10d
	movdqa	%xmm0, %xmm7
	movdqa	%xmm0, %xmm1
	paddd	%xmm2, %xmm7
	cvtdq2pd	%xmm7, %xmm8
	pshufd	$238, %xmm7, %xmm7
	paddd	%xmm3, %xmm1
	movaps	%xmm8, (%rax)
	cvtdq2pd	%xmm1, %xmm8
	pshufd	$238, %xmm1, %xmm1
	cvtdq2pd	%xmm7, %xmm7
	movaps	%xmm7, 16(%rax)
	movdqa	%xmm0, %xmm7
	movaps	%xmm8, 32(%rax)
	cvtdq2pd	%xmm1, %xmm1
	paddd	%xmm4, %xmm7
	cvtdq2pd	%xmm7, %xmm8
	pshufd	$238, %xmm7, %xmm7
	movaps	%xmm1, 48(%rax)
	movdqa	%xmm0, %xmm1
	paddd	%xmm6, %xmm0
	cvtdq2pd	%xmm7, %xmm7
	movaps	%xmm7, 80(%rax)
	paddd	%xmm5, %xmm1
	cvtdq2pd	%xmm1, %xmm7
	pshufd	$238, %xmm1, %xmm1
	movaps	%xmm8, 64(%rax)
	cvtdq2pd	%xmm1, %xmm1
	movaps	%xmm7, 96(%rax)
	movaps	%xmm1, 112(%rax)
	jne	.L9
	cvtdq2pd	%xmm0, %xmm1
	pshufd	$238, %xmm0, %xmm0
	movaps	%xmm1, 128(%rax)
	cvtdq2pd	%xmm0, %xmm0
	movaps	%xmm0, 144(%rax)
.L9:
	movl	%r9d, %r10d
	andl	$-4, %r10d
	subl	%r10d, %esi
	movl	12(%rsp), %eax
	addl	%r10d, %eax
	cmpl	%r9d, %r10d
	je	.L8
	pxor	%xmm0, %xmm0
	leal	(%rdx,%rax), %r9d
	cmpl	$1, %esi
	movslq	%r9d, %r9
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, (%r12,%r9,8)
	leal	1(%rax), %r9d
	je	.L8
	pxor	%xmm0, %xmm0
	leal	(%r9,%rdx), %r10d
	addl	$2, %eax
	cmpl	$2, %esi
	movslq	%r10d, %r10
	cvtsi2sd	%r9d, %xmm0
	movsd	%xmm0, (%r12,%r10,8)
	je	.L8
	pxor	%xmm0, %xmm0
	addl	%eax, %edx
	movslq	%edx, %rdx
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, (%r12,%rdx,8)
.L8:
	addq	$20, %rcx
	addq	$160, %rdi
	cmpq	$400, %rcx
	je	.L10
.L5:
	movq	%rdi, %rax
	movl	%ecx, %edx
	shrq	$3, %rax
	andl	$1, %eax
	jne	.L37
	movl	$20, %esi
	movl	$0, 12(%rsp)
	jmp	.L11
.L10:
	leaq	16(%rsp), %rsi
	movl	$5, %edi
	leaq	2400(%rbx), %r13
	call	clock_gettime@PLT
	subq	$8, %rsp
	.cfi_def_cfa_offset 120
	movq	%r12, %r9
	movl	$20, %r8d
	pushq	$20
	.cfi_def_cfa_offset 128
	pushq	%rbx
	.cfi_def_cfa_offset 136
	movq	%rbp, %rcx
	pushq	$20
	.cfi_def_cfa_offset 144
	movl	$20, %edx
	movl	$20, %esi
	movl	$15, %edi
	leaq	.LC9(%rip), %r12
	call	dgemm@PLT
	addq	$32, %rsp
	.cfi_def_cfa_offset 112
	movl	$5, %edi
	leaq	32(%rsp), %rsi
	call	clock_gettime@PLT
	pxor	%xmm0, %xmm0
	movq	32(%rsp), %rax
	pxor	%xmm1, %xmm1
	subq	16(%rsp), %rax
	movsd	.LC6(%rip), %xmm2
	leaq	.LC8(%rip), %rsi
	cvtsi2sdq	40(%rsp), %xmm0
	movl	$1, %edi
	cvtsi2sdq	24(%rsp), %xmm1
	subsd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm1
	movl	$2, %eax
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	.LC7(%rip), %xmm1
	divsd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	call	__printf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L13:
	leaq	160(%rbx), %rbp
	.p2align 4,,10
	.p2align 3
.L14:
	movsd	(%rbx), %xmm0
	movq	%r12, %rsi
	movl	$1, %edi
	movl	$1, %eax
	addq	$8, %rbx
	call	__printf_chk@PLT
	cmpq	%rbp, %rbx
	jne	.L14
	movl	$10, %edi
	call	putchar@PLT
	cmpq	%rbx, %r13
	jne	.L13
	xorl	%eax, %eax
	movq	56(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L38
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L38:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE4781:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC2:
	.long	4
	.long	5
	.long	6
	.long	7
	.align 16
.LC3:
	.long	8
	.long	9
	.long	10
	.long	11
	.align 16
.LC4:
	.long	12
	.long	13
	.long	14
	.long	15
	.align 16
.LC5:
	.long	16
	.long	17
	.long	18
	.long	19
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC6:
	.long	0
	.long	1104006501
	.align 8
.LC7:
	.long	0
	.long	1086428160
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
