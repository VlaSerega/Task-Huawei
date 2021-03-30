	.file	"dgemm.c"
	.text
	.p2align 4,,15
	.globl	dgemm
	.type	dgemm, @function
dgemm:
.LFB4793:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movl	%esi, %r14d
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	movq	200(%rsp), %rax
	movl	%edi, 108(%rsp)
	movslq	%edx, %rdi
	movq	%rdi, %rbx
	salq	$3, %rdi
	movl	%esi, 104(%rsp)
	movq	%rcx, 112(%rsp)
	movl	%r8d, 120(%rsp)
	movq	%rax, 80(%rsp)
	movl	208(%rsp), %eax
	movq	%r9, 48(%rsp)
	movl	192(%rsp), %r15d
	movl	%eax, 124(%rsp)
	movslq	%esi, %rax
	imulq	%rax, %rdi
	call	malloc@PLT
	testl	%ebx, %ebx
	jle	.L2
	testl	%r14d, %r14d
	jle	.L2
	leal	-1(%rbx), %edx
	leal	-8(%rbx), %ecx
	leal	(%rbx,%rbx), %edi
	leal	0(,%rbx,4), %esi
	leal	0(,%r15,8), %r13d
	movq	48(%rsp), %r9
	andl	$-8, %edx
	movl	%edi, 4(%rsp)
	addl	%ebx, %edi
	subl	%edx, %ecx
	leal	0(,%rbx,8), %edx
	movl	%edi, 8(%rsp)
	movl	%ecx, 92(%rsp)
	addl	%edi, %edi
	movl	%esi, 16(%rsp)
	movslq	%edx, %rcx
	addl	%ebx, %esi
	subl	%ebx, %edx
	salq	$3, %rcx
	movl	%edi, 32(%rsp)
	movslq	%r13d, %r13
	movq	%rcx, 56(%rsp)
	leal	-1(%r14), %ecx
	movl	%esi, 24(%rsp)
	movl	%edx, 40(%rsp)
	movl	%ebx, 88(%rsp)
	movl	%ebx, %edi
	shrl	$3, %ecx
	movq	$0, 72(%rsp)
	movq	$0, 64(%rsp)
	leaq	8(,%rcx,8), %rcx
	movq	%rcx, 96(%rsp)
	.p2align 4,,10
	.p2align 3
.L10:
	cmpl	$8, %edi
	movl	$8, %r14d
	cmovle	%edi, %r14d
	testl	%edi, %edi
	jle	.L4
	movq	72(%rsp), %rsi
	movq	96(%rsp), %rdx
	movq	64(%rsp), %r8
	addq	%rsi, %rdx
	leaq	0(,%rsi,8), %rdi
	movl	104(%rsp), %esi
	leaq	0(,%rdx,8), %rcx
	movq	%rcx, 48(%rsp)
	.p2align 4,,10
	.p2align 3
.L7:
	testl	%esi, %esi
	jle	.L5
	leaq	(%r9,%rdi), %r11
	leaq	(%rax,%r8), %r10
	movl	$1, %ecx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L6:
	movsd	(%r11), %xmm0
	cmpl	$1, %esi
	movsd	%xmm0, (%r10)
	jle	.L8
	leal	(%rdx,%rbx), %ebp
	movslq	%ecx, %r12
	cmpl	$2, %esi
	leaq	(%r9,%r12,8), %r12
	movslq	%ebp, %rbp
	leaq	(%rax,%rbp,8), %rbp
	movsd	(%r12,%rdi), %xmm0
	movsd	%xmm0, 0(%rbp,%r8)
	je	.L8
	movl	4(%rsp), %ebp
	addl	%edx, %ebp
	cmpl	$3, %esi
	movslq	%ebp, %rbp
	leaq	(%rax,%rbp,8), %r12
	leal	1(%rcx), %ebp
	movslq	%ebp, %rbp
	leaq	(%r9,%rbp,8), %rbp
	movsd	0(%rbp,%rdi), %xmm0
	movsd	%xmm0, (%r12,%r8)
	je	.L8
	movl	8(%rsp), %ebp
	addl	%edx, %ebp
	cmpl	$4, %esi
	movslq	%ebp, %rbp
	leaq	(%rax,%rbp,8), %r12
	leal	2(%rcx), %ebp
	movslq	%ebp, %rbp
	leaq	(%r9,%rbp,8), %rbp
	movsd	0(%rbp,%rdi), %xmm0
	movsd	%xmm0, (%r12,%r8)
	je	.L8
	movl	16(%rsp), %ebp
	addl	%edx, %ebp
	cmpl	$5, %esi
	movslq	%ebp, %rbp
	leaq	(%rax,%rbp,8), %r12
	leal	3(%rcx), %ebp
	movslq	%ebp, %rbp
	leaq	(%r9,%rbp,8), %rbp
	movsd	0(%rbp,%rdi), %xmm0
	movsd	%xmm0, (%r12,%r8)
	je	.L8
	movl	24(%rsp), %ebp
	addl	%edx, %ebp
	cmpl	$6, %esi
	movslq	%ebp, %rbp
	leaq	(%rax,%rbp,8), %r12
	leal	4(%rcx), %ebp
	movslq	%ebp, %rbp
	leaq	(%r9,%rbp,8), %rbp
	movsd	0(%rbp,%rdi), %xmm0
	movsd	%xmm0, (%r12,%r8)
	je	.L8
	movl	32(%rsp), %ebp
	addl	%edx, %ebp
	cmpl	$7, %esi
	movslq	%ebp, %rbp
	leaq	(%rax,%rbp,8), %r12
	leal	5(%rcx), %ebp
	movslq	%ebp, %rbp
	leaq	(%r9,%rbp,8), %rbp
	movsd	0(%rbp,%rdi), %xmm0
	movsd	%xmm0, (%r12,%r8)
	jle	.L8
	movl	40(%rsp), %ebp
	addl	%edx, %ebp
	movslq	%ebp, %rbp
	leaq	(%rax,%rbp,8), %r12
	leal	6(%rcx), %ebp
	movslq	%ebp, %rbp
	leaq	(%r9,%rbp,8), %rbp
	movsd	0(%rbp,%rdi), %xmm0
	movsd	%xmm0, (%r12,%r8)
.L8:
	addl	$1, %edx
	addq	%r13, %r11
	addq	$8, %r10
	addl	%r15d, %ecx
	cmpl	%edx, %r14d
	jg	.L6
.L5:
	subl	$8, %esi
	addq	$64, %rdi
	addq	56(%rsp), %r8
	cmpq	48(%rsp), %rdi
	jne	.L7
.L4:
	subl	$8, 88(%rsp)
	addq	$64, 64(%rsp)
	movl	88(%rsp), %edi
	addq	%r13, 72(%rsp)
	cmpl	92(%rsp), %edi
	jne	.L10
.L2:
	movl	108(%rsp), %edi
	subl	$2, %edi
	testl	%edi, %edi
	movl	%edi, 4(%rsp)
	jle	.L11
	movl	120(%rsp), %esi
	movl	124(%rsp), %ecx
	movl	%ebx, %r12d
	movl	104(%rsp), %edi
	andl	$-4, %r12d
	leal	0(,%r15,8), %edx
	movslq	%r12d, %r12
	leal	0(,%rsi,8), %r11d
	leal	0(,%rcx,8), %ebp
	salq	$3, %r12
	cmpl	$3, %edi
	movslq	%edx, %rdx
	movslq	%r11d, %r11
	movslq	%ebp, %rbp
	jle	.L11
	leal	(%rcx,%rcx,2), %ecx
	subl	$4, %edi
	movq	112(%rsp), %r10
	xorl	%r14d, %r14d
	xorl	%r15d, %r15d
	movslq	%ecx, %rcx
	movq	%rcx, 16(%rsp)
	leal	(%rsi,%rsi,2), %ecx
	movl	%edi, %esi
	shrl	$2, %esi
	movslq	%ecx, %rcx
	salq	$3, %rcx
	movq	%rcx, 24(%rsp)
	leal	0(,%rbx,4), %ecx
	leaq	0(,%rsi,4), %rbx
	movq	%rbx, 8(%rsp)
	leaq	(%rax,%r12), %rbx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	movq	%rbx, 32(%rsp)
	movq	80(%rsp), %rbx
	addq	$32, %rbx
	movq	%rbx, 40(%rsp)
	.p2align 4,,10
	.p2align 3
.L13:
	movq	80(%rsp), %rbx
	movq	32(%rsp), %rdi
	leaq	(%rbx,%r14,8), %rsi
	movq	8(%rsp), %rbx
	leaq	(%rbx,%r14), %r8
	movq	40(%rsp), %rbx
	leaq	(%rbx,%r8,8), %r13
	.p2align 4,,10
	.p2align 3
.L12:
	movq	%rdi, %r8
	subq	%r12, %r8
#APP
# 24 "dgemm.c" 1
	.intel_syntax noprefix
	vxorpd  ymm0, ymm0, ymm0
	vxorpd  ymm1, ymm1, ymm1
	vxorpd  ymm2, ymm2, ymm2
	vxorpd  ymm3, ymm3, ymm3
	vxorpd  ymm4, ymm4, ymm4
	vxorpd  ymm5, ymm5, ymm5
	vxorpd  ymm6, ymm6, ymm6
	vxorpd  ymm7, ymm7, ymm7
	vxorpd  ymm8, ymm8, ymm8
	vxorpd  ymm9, ymm9, ymm9
	vxorpd  ymm10, ymm10, ymm10
	vxorpd  ymm11, ymm11, ymm11
	jmp .LLL2
	.LLL1:
	vmovupd ymm12, [%r10]
	mov rbx, %r10
	add rbx, %r11
	vmovupd ymm13, [rbx]
	add rbx, %r11
	vmovupd ymm14, [rbx]
	vmovupd ymm15, [%r8]
	vfmadd231pd ymm0, ymm12, ymm15
	vfmadd231pd ymm1, ymm13, ymm15
	vfmadd231pd ymm2, ymm14, ymm15
	mov rbx, %r8
	add rbx, %rdx
	vmovupd ymm15, [rbx]
	vfmadd231pd ymm3, ymm12, ymm15
	vfmadd231pd ymm4, ymm13, ymm15
	vfmadd231pd ymm5, ymm14, ymm15
	add rbx, %rdx
	vmovupd ymm15, [rbx]
	vfmadd231pd ymm6, ymm12, ymm15
	vfmadd231pd ymm7, ymm13, ymm15
	vfmadd231pd ymm8, ymm14, ymm15
	add rbx, %rdx
	vmovupd ymm15, [rbx]
	vfmadd231pd ymm9, ymm12, ymm15
	vfmadd231pd ymm10, ymm13, ymm15
	vfmadd231pd ymm11, ymm14, ymm15
	add %r10, 32
	add %r8, 32
	.LLL2:
	cmp %rdi, %r8
	jne .LLL1
	vhaddpd ymm0, ymm0, ymm0
	vextractf128    xmm15, ymm0, 0x1
	vaddsd xmm0, xmm0, xmm15
	vaddsd xmm0, xmm0, [%rsi]
	vmovsd [%rsi], xmm0
	vhaddpd ymm3, ymm3, ymm3
	vextractf128    xmm15, ymm3, 0x1
	vaddsd xmm3, xmm3, xmm15
	vaddsd xmm3, xmm3, [%rsi+8]
	vmovsd [%rsi+8], xmm3
	vhaddpd ymm6, ymm6, ymm6
	vextractf128    xmm15, ymm6, 0x1
	vaddsd xmm6, xmm6, xmm15
	vaddsd xmm6, xmm6, [%rsi+16]
	vmovsd [%rsi+16], xmm6
	vhaddpd ymm9, ymm9, ymm9
	vextractf128    xmm15, ymm9, 0x1
	vaddsd xmm9, xmm9, xmm15
	vaddsd xmm9, xmm9, [%rsi+24]
	vmovsd [%rsi+24], xmm9
	mov rbx, %rsi
	add rbx, %rbp
	vhaddpd ymm1, ymm1, ymm1
	vextractf128    xmm15, ymm1, 0x1
	vaddsd xmm1, xmm1, xmm15
	vaddsd xmm1, xmm1, [rbx]
	vmovsd [rbx], xmm1
	vhaddpd ymm4, ymm4, ymm4
	vextractf128    xmm15, ymm4, 0x1
	vaddsd xmm4, xmm4, xmm15
	vaddsd xmm4, xmm4, [rbx+8]
	vmovsd [rbx+8], xmm4
	vhaddpd ymm7, ymm7, ymm7
	vextractf128    xmm15, ymm7, 0x1
	vaddsd xmm7, xmm7, xmm15
	vaddsd xmm7, xmm7, [rbx+16]
	vmovsd [rbx+16], xmm7
	vhaddpd ymm10, ymm10, ymm10
	vextractf128    xmm15, ymm10, 0x1
	vaddsd xmm10, xmm10, xmm15
	vaddsd xmm10, xmm10, [rbx+24]
	vmovsd [rbx+24], xmm10
	add rbx, %rbp
	vhaddpd ymm2, ymm2, ymm2
	vextractf128    xmm15, ymm2, 0x1
	vaddsd xmm2, xmm2, xmm15
	vaddsd xmm2, xmm2, [rbx]
	vmovsd [rbx], xmm2
	vhaddpd ymm5, ymm5, ymm5
	vextractf128    xmm15, ymm5, 0x1
	vaddsd xmm5, xmm5, xmm15
	vaddsd xmm5, xmm5, [rbx+8]
	vmovsd [rbx+8], xmm5
	vhaddpd ymm8, ymm8, ymm8
	vextractf128    xmm15, ymm8, 0x1
	vaddsd xmm8, xmm8, xmm15
	vaddsd xmm8, xmm8, [rbx+16]
	vmovsd [rbx+16], xmm8
	vhaddpd ymm11, ymm11, ymm11
	vextractf128    xmm15, ymm11, 0x1
	vaddsd xmm11, xmm11, xmm15
	vaddsd xmm11, xmm11, [rbx+24]
	vmovsd [rbx+24], xmm11
	mov %r8, %r10
	mov %r9, %r8
	.att_syntax 
	
# 0 "" 2
#NO_APP
	addq	$32, %rsi
	addq	%rcx, %rdi
	cmpq	%r13, %rsi
	jne	.L12
	addl	$3, %r15d
	addq	16(%rsp), %r14
	addq	24(%rsp), %r10
	cmpl	4(%rsp), %r15d
	jl	.L13
.L11:
	addq	$136, %rsp
	.cfi_def_cfa_offset 56
	movq	%rax, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.cfi_endproc
.LFE4793:
	.size	dgemm, .-dgemm
	.p2align 4,,15
	.globl	transpose
	.type	transpose, @function
transpose:
.LFB4794:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	testl	%edi, %edi
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movl	%esi, -4(%rsp)
	jle	.L36
	testl	%esi, %esi
	jle	.L36
	sall	$3, %ecx
	movq	%rdx, -32(%rsp)
	leal	-8(%rdi), %edx
	movslq	%ecx, %r10
	leal	0(,%r9,8), %r14d
	movl	%edi, %r15d
	leaq	0(,%r10,8), %rax
	movq	%r8, -24(%rsp)
	movl	$8, %r13d
	movslq	%r14d, %r14
	movq	%rax, -16(%rsp)
	leal	-1(%rdi), %eax
	movslq	%r9d, %rdi
	salq	$3, %r14
	salq	$3, %rdi
	andl	$-8, %eax
	subl	%eax, %edx
	leal	-1(%rsi), %eax
	movl	%edx, -8(%rsp)
	leal	-8(%rsi), %edx
	andl	$-8, %eax
	subl	%eax, %edx
	movl	%edx, -36(%rsp)
.L43:
	movl	-4(%rsp), %ebx
	movq	-32(%rsp), %r12
	cmpl	$8, %r15d
	movq	-24(%rsp), %rbp
	movl	%r13d, %r11d
	cmovle	%r15d, %r11d
	.p2align 4,,10
	.p2align 3
.L41:
	cmpl	$8, %ebx
	movl	%r13d, %esi
	movq	%r12, %rcx
	cmovle	%ebx, %esi
	movq	%rbp, %r9
	xorl	%r8d, %r8d
	.p2align 4,,10
	.p2align 3
.L39:
	movq	%r9, %rdx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L40:
	movsd	(%rcx,%rax,8), %xmm0
	addq	$1, %rax
	movsd	%xmm0, (%rdx)
	addq	%rdi, %rdx
	cmpl	%eax, %esi
	jg	.L40
	addl	$1, %r8d
	addq	$8, %r9
	addq	%r10, %rcx
	cmpl	%r8d, %r11d
	jg	.L39
	subl	$8, %ebx
	addq	%r14, %rbp
	addq	$64, %r12
	cmpl	-36(%rsp), %ebx
	jne	.L41
	subl	$8, %r15d
	addq	$64, -24(%rsp)
	movq	-16(%rsp), %rbx
	addq	%rbx, -32(%rsp)
	cmpl	-8(%rsp), %r15d
	jne	.L43
.L36:
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE4794:
	.size	transpose, .-transpose
	.p2align 4,,15
	.globl	transposeBlock
	.type	transposeBlock, @function
transposeBlock:
.LFB4795:
	.cfi_startproc
	testl	%edi, %edi
	jle	.L50
	testl	%esi, %esi
	jle	.L50
	leal	-1(%rdi), %eax
	movslq	%ecx, %rcx
	movslq	%r9d, %rdi
	leaq	0(,%rcx,8), %r11
	salq	$3, %rdi
	leaq	8(%r8,%rax,8), %r10
	leal	-1(%rsi), %eax
	leaq	8(,%rax,8), %r9
	.p2align 4,,10
	.p2align 3
.L52:
	leaq	(%r9,%rdx), %rsi
	movq	%r8, %rcx
	movq	%rdx, %rax
	.p2align 4,,10
	.p2align 3
.L53:
	movsd	(%rax), %xmm0
	addq	$8, %rax
	movsd	%xmm0, (%rcx)
	addq	%rdi, %rcx
	cmpq	%rsi, %rax
	jne	.L53
	addq	$8, %r8
	addq	%r11, %rdx
	cmpq	%r10, %r8
	jne	.L52
.L50:
	rep ret
	.cfi_endproc
.LFE4795:
	.size	transposeBlock, .-transposeBlock
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
