	.file	"simple-easter.c"
	.text
	.section	.rodata
.LC0:
	.string	"%Y"
	.text
	.globl	returnYear
	.type	returnYear, @function
returnYear:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	time@PLT
	cmpq	$-1, %rax
	je	.L2
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	localtime@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L2
	movq	-24(%rbp), %rdx
	leaq	-13(%rbp), %rax
	movq	%rdx, %rcx
	leaq	.LC0(%rip), %rdx
	movl	$5, %esi
	movq	%rax, %rdi
	call	strftime@PLT
	testq	%rax, %rax
	je	.L2
	leaq	-13(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -36(%rbp)
.L2:
	movl	-36(%rbp), %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	returnYear, .-returnYear
	.section	.rodata
.LC1:
	.string	"March"
.LC2:
	.string	"April"
.LC3:
	.string	"Sunday"
	.text
	.globl	anonymous_Gregorian_algorithm
	.type	anonymous_Gregorian_algorithm, @function
anonymous_Gregorian_algorithm:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -120(%rbp)
	movl	%esi, -124(%rbp)
	movl	-124(%rbp), %eax
	movl	%eax, -100(%rbp)
	movl	-100(%rbp), %ecx
	movl	$1808407283, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$3, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -96(%rbp)
	movl	-100(%rbp), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -92(%rbp)
	movl	-100(%rbp), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	imull	$100, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -88(%rbp)
	movl	-92(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -84(%rbp)
	movl	-92(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -80(%rbp)
	movl	-92(%rbp), %eax
	leal	8(%rax), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$3, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -76(%rbp)
	movl	-92(%rbp), %eax
	subl	-76(%rbp), %eax
	leal	1(%rax), %ecx
	movl	$1431655766, %edx
	movl	%ecx, %eax
	imull	%edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -72(%rbp)
	movl	-96(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%eax, %edx
	movl	-92(%rbp), %eax
	addl	%edx, %eax
	subl	-84(%rbp), %eax
	subl	-72(%rbp), %eax
	leal	15(%rax), %ecx
	movl	$-2004318071, %edx
	movl	%ecx, %eax
	imull	%edx
	leal	(%rdx,%rcx), %eax
	sarl	$4, %eax
	movl	%eax, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -68(%rbp)
	movl	-68(%rbp), %eax
	imull	$30, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -68(%rbp)
	movl	-88(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -64(%rbp)
	movl	-88(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -60(%rbp)
	movl	-80(%rbp), %eax
	leal	16(%rax), %edx
	movl	-64(%rbp), %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	-68(%rbp), %eax
	subl	-60(%rbp), %eax
	movl	%eax, %ecx
	movl	$-1840700269, %edx
	movl	%ecx, %eax
	imull	%edx
	leal	(%rdx,%rcx), %eax
	sarl	$2, %eax
	movl	%eax, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -56(%rbp)
	movl	-56(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -56(%rbp)
	movl	-68(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%eax, %edx
	movl	-96(%rbp), %eax
	addl	%eax, %edx
	movl	-56(%rbp), %eax
	imull	$22, %eax, %eax
	leal	(%rdx,%rax), %ecx
	movl	$1218970763, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$7, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -52(%rbp)
	movl	-68(%rbp), %edx
	movl	-56(%rbp), %eax
	addl	%eax, %edx
	movl	-52(%rbp), %eax
	movl	%eax, %ecx
	sall	$3, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	%edx, %eax
	leal	114(%rax), %ecx
	movl	$-2078209981, %edx
	movl	%ecx, %eax
	imull	%edx
	leal	(%rdx,%rcx), %eax
	sarl	$4, %eax
	movl	%eax, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -48(%rbp)
	movl	-68(%rbp), %edx
	movl	-56(%rbp), %eax
	addl	%eax, %edx
	movl	-52(%rbp), %eax
	movl	%eax, %ecx
	sall	$3, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	%edx, %eax
	leal	114(%rax), %ecx
	movl	$-2078209981, %edx
	movl	%ecx, %eax
	imull	%edx
	leal	(%rdx,%rcx), %eax
	sarl	$4, %eax
	movl	%eax, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	sall	$5, %edx
	subl	%eax, %edx
	movl	%ecx, %eax
	subl	%edx, %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	cmpl	$3, -48(%rbp)
	jne	.L6
	leaq	.LC1(%rip), %rax
	movq	%rax, -40(%rbp)
	jmp	.L7
.L6:
	leaq	.LC2(%rip), %rax
	movq	%rax, -40(%rbp)
.L7:
	leaq	.LC3(%rip), %rax
	movq	%rax, -32(%rbp)
	movl	-44(%rbp), %eax
	movl	%eax, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	-124(%rbp), %eax
	movl	%eax, -12(%rbp)
	movq	-120(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-16(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-120(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	anonymous_Gregorian_algorithm, .-anonymous_Gregorian_algorithm
	.section	.rodata
	.align 8
.LC4:
	.string	"Anonymous Output:\n\t%s %d, %s %d -- Gregorian Calendar, mixed var array\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, %eax
	call	returnYear
	movl	%eax, -36(%rbp)
	leaq	-32(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	anonymous_Gregorian_algorithm
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdi
	xorq	%fs:40, %rdi
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.2.1 20181127"
	.section	.note.GNU-stack,"",@progbits
