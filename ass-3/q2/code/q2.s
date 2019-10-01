	.file	"q2.c"
	.text
	.globl	Qfirst
	.bss
	.align 8
	.type	Qfirst, @object
	.size	Qfirst, 8
Qfirst:
	.zero	8
	.globl	Qlast
	.align 8
	.type	Qlast, @object
	.size	Qlast, 8
Qlast:
	.zero	8
	.text
	.globl	store
	.type	store, @function
store:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	$24, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movl	-20(%rbp), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movl	-24(%rbp), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 4(%rax)
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	Qlast(%rip), %rax
	testq	%rax, %rax
	jne	.L2
	movq	-8(%rbp), %rax
	movq	%rax, Qlast(%rip)
	movq	Qlast(%rip), %rax
	movq	%rax, Qfirst(%rip)
	movq	Qlast(%rip), %rax
	movq	$0, 16(%rax)
	jmp	.L4
.L2:
	movq	Qlast(%rip), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, Qlast(%rip)
	movq	-8(%rbp), %rax
	movq	$0, 16(%rax)
.L4:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	store, .-store
	.globl	first
	.bss
	.align 8
	.type	first, @object
	.size	first, 8
first:
	.zero	8
	.globl	last
	.align 8
	.type	last, @object
	.size	last, 8
last:
	.zero	8
	.globl	length
	.align 4
	.type	length, @object
	.size	length, 4
length:
	.zero	4
	.text
	.globl	insert
	.type	insert, @function
insert:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$24, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	-20(%rbp), %edx
	movl	%edx, (%rax)
	movq	last(%rip), %rax
	testq	%rax, %rax
	jne	.L6
	movq	-8(%rbp), %rax
	movq	%rax, last(%rip)
	movq	last(%rip), %rax
	movq	%rax, first(%rip)
	movq	first(%rip), %rax
	movq	$0, 16(%rax)
	movq	last(%rip), %rax
	movq	$0, 8(%rax)
	jmp	.L7
.L6:
	movq	last(%rip), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	last(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, last(%rip)
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
.L7:
	movl	length(%rip), %eax
	addl	$1, %eax
	movl	%eax, length(%rip)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	insert, .-insert
	.globl	XORi2l
	.type	XORi2l, @function
XORi2l:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movl	%edi, -68(%rbp)
	movl	-68(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	movl	$0, -52(%rbp)
	jmp	.L9
.L10:
	movl	-68(%rbp), %eax
	cltq
	salq	$3, %rax
	movl	-52(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,8), %rcx
	movq	-24(%rbp), %rdx
	leaq	(%rcx,%rdx), %rbx
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, (%rbx)
	addl	$1, -52(%rbp)
.L9:
	movl	-52(%rbp), %eax
	cmpl	-68(%rbp), %eax
	jl	.L10
	movq	first(%rip), %rax
	movq	%rax, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rdx
	movl	(%rdx), %edx
	movl	%edx, (%rax)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -32(%rbp)
	movl	$1, -48(%rbp)
	jmp	.L11
.L12:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	-48(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	subq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-32(%rbp), %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	-48(%rbp), %esi
	movslq	%esi, %rsi
	salq	$2, %rsi
	addq	%rsi, %rax
	xorl	%ecx, %edx
	movl	%edx, (%rax)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -32(%rbp)
	addl	$1, -48(%rbp)
.L11:
	movl	-48(%rbp), %eax
	cmpl	-68(%rbp), %eax
	jl	.L12
	movl	$1, -44(%rbp)
	jmp	.L13
.L18:
	movl	$0, -40(%rbp)
	jmp	.L14
.L15:
	movl	-44(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	$-1, (%rax)
	addl	$1, -40(%rbp)
.L14:
	movl	-40(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L15
	movl	-44(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	.L16
.L17:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	-44(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	subq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	-36(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-44(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rsi
	movq	-24(%rbp), %rax
	addq	%rsi, %rax
	movq	(%rax), %rax
	movl	-36(%rbp), %esi
	movslq	%esi, %rsi
	salq	$2, %rsi
	addq	%rsi, %rax
	xorl	%ecx, %edx
	movl	%edx, (%rax)
	addl	$1, -36(%rbp)
.L16:
	movl	-36(%rbp), %eax
	cmpl	-68(%rbp), %eax
	jl	.L17
	addl	$1, -44(%rbp)
.L13:
	movl	-44(%rbp), %eax
	cmpl	-68(%rbp), %eax
	jl	.L18
	movq	-24(%rbp), %rax
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	XORi2l, .-XORi2l
	.globl	count
	.type	count, @function
count:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movl	$0, -8(%rbp)
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.L21
.L23:
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	subq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movl	-32(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$2, %rcx
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L22
	movl	-32(%rbp), %edx
	movl	-4(%rbp), %ecx
	movl	-28(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	store
	addl	$1, -8(%rbp)
.L22:
	addl	$1, -4(%rbp)
.L21:
	movl	-4(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jle	.L23
	movl	-8(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	count, .-count
	.globl	countTriplets
	.type	countTriplets, @function
countTriplets:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movl	$0, -20(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, %edi
	call	XORi2l
	movq	%rax, -8(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L26
.L30:
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.L27
.L29:
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L28
	movl	-36(%rbp), %ecx
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %esi
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	count
	addl	%eax, -20(%rbp)
.L28:
	addl	$1, -12(%rbp)
.L27:
	movl	-12(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L29
	addl	$1, -16(%rbp)
.L26:
	movl	-16(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L30
	movl	-20(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	countTriplets, .-countTriplets
	.section	.rodata
.LC0:
	.string	"( %d , %d , %d )\n"
	.text
	.globl	showTriplets
	.type	showTriplets, @function
showTriplets:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	Qfirst(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L33
.L34:
	movq	-8(%rbp), %rax
	movl	8(%rax), %ecx
	movq	-8(%rbp), %rax
	movl	4(%rax), %edx
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
.L33:
	cmpq	$0, -8(%rbp)
	jne	.L34
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	showTriplets, .-showTriplets
	.section	.rodata
.LC2:
	.string	"%d\n"
	.align 8
.LC4:
	.string	"\nTotal Execution time is : %f (sec)\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -48(%rbp)
	call	clock@PLT
	movq	%rax, -40(%rbp)
	movl	$5, -20(%rbp)
	movl	$2, -16(%rbp)
	movl	$7, -12(%rbp)
	movl	$3, %edi
	call	insert
	movl	$4, %edi
	call	insert
	movl	$0, %edi
	call	insert
	movl	$7, %edi
	call	insert
	movl	$8, %edi
	call	insert
	movl	$12, %edi
	call	insert
	movl	$5, %edi
	call	insert
	movl	$9, %edi
	call	insert
	movl	$3, %edi
	call	insert
	movl	length(%rip), %eax
	movl	%eax, %edi
	call	countTriplets
	movl	%eax, -52(%rbp)
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	call	showTriplets
	call	clock@PLT
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	subq	-40(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC3(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	-48(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	leaq	.LC4(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L37
	call	__stack_chk_fail@PLT
.L37:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC3:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
