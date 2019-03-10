	.file	"main.c"
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
	.globl	noOfChars
	.type	noOfChars, @function
noOfChars:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	addl	$1, -4(%rbp)
.L6:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L7
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	noOfChars, .-noOfChars
	.section	.rodata
.LC1:
	.string	""
	.string	""
	.text
	.globl	myConcat
	.type	myConcat, @function
myConcat:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	noOfChars
	movl	%eax, -20(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	noOfChars
	movl	%eax, -16(%rbp)
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	jmp	.L10
.L11:
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rcx
	movq	-8(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -28(%rbp)
.L10:
	movl	-28(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L11
	jmp	.L12
.L13:
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	-28(%rbp), %ecx
	movl	-24(%rbp), %edx
	addl	%ecx, %edx
	movslq	%edx, %rcx
	movq	-8(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -24(%rbp)
.L12:
	movl	-24(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L13
	movl	-28(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%edx, %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	myConcat, .-myConcat
	.section	.rodata
.LC3:
	.string	"%d"
	.text
	.globl	itoa
	.type	itoa, @function
itoa:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	cmpl	$0, -20(%rbp)
	je	.L16
	movl	-20(%rbp), %eax
	cltq
	cqto
	xorq	%rdx, %rax
	subq	%rdx, %rax
	movq	%rax, -40(%rbp)
	fildq	-40(%rbp)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	call	log10l@PLT
	addq	$16, %rsp
	fstpl	-32(%rbp)
	movsd	-32(%rbp), %xmm0
	call	floor@PLT
	movapd	%xmm0, %xmm1
	movsd	.LC2(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvttsd2si	%xmm0, %eax
	jmp	.L17
.L16:
	movl	$1, %eax
.L17:
	movl	%eax, -12(%rbp)
	cmpl	$0, -20(%rbp)
	jns	.L18
	addl	$1, -12(%rbp)
.L18:
	movl	-12(%rbp), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rsi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -8(%rbp)
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rsi
	movl	-20(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC3(%rip), %rdx
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	itoa, .-itoa
	.globl	decimalToBinary
	.type	decimalToBinary, @function
decimalToBinary:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	$0, -16(%rbp)
	movq	$1, -8(%rbp)
	jmp	.L21
.L22:
	movq	-40(%rbp), %rax
	cqto
	shrq	$63, %rdx
	addq	%rdx, %rax
	andl	$1, %eax
	subq	%rdx, %rax
	movl	%eax, -20(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdx
	shrq	$63, %rdx
	addq	%rdx, %rax
	sarq	%rax
	movq	%rax, -40(%rbp)
	movl	-20(%rbp), %eax
	cltq
	imulq	-8(%rbp), %rax
	addq	%rax, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	movq	%rax, -8(%rbp)
.L21:
	cmpq	$0, -40(%rbp)
	jne	.L22
	movq	-16(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	decimalToBinary, .-decimalToBinary
	.globl	stringTocharArray
	.type	stringTocharArray, @function
stringTocharArray:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	noOfChars
	movl	%eax, str1Len.4115(%rip)
	movl	str1Len.4115(%rip), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	movl	%eax, str2Len.4116(%rip)
	movl	str1Len.4115(%rip), %edx
	movl	str2Len.4116(%rip), %eax
	addl	%edx, %eax
	movl	%eax, combinedLen.4117(%rip)
	movl	combinedLen.4117(%rip), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, outputString.4112(%rip)
	jmp	.L25
.L26:
	movq	outputString.4112(%rip), %rdx
	movl	count2.4114(%rip), %eax
	cltq
	addq	%rdx, %rax
	movb	$91, (%rax)
	movl	count2.4114(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.4114(%rip)
	movl	count1.4113(%rip), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movq	outputString.4112(%rip), %rcx
	movl	count2.4114(%rip), %edx
	movslq	%edx, %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movl	count1.4113(%rip), %eax
	addl	$1, %eax
	movl	%eax, count1.4113(%rip)
	movl	count2.4114(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.4114(%rip)
	movq	outputString.4112(%rip), %rdx
	movl	count2.4114(%rip), %eax
	cltq
	addq	%rdx, %rax
	movb	$93, (%rax)
	movl	count1.4113(%rip), %edx
	movl	str1Len.4115(%rip), %eax
	cmpl	%eax, %edx
	jge	.L25
	movl	count2.4114(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.4114(%rip)
	movq	outputString.4112(%rip), %rdx
	movl	count2.4114(%rip), %eax
	cltq
	addq	%rdx, %rax
	movb	$44, (%rax)
	movl	count2.4114(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.4114(%rip)
.L25:
	movl	count1.4113(%rip), %edx
	movl	str1Len.4115(%rip), %eax
	cmpl	%eax, %edx
	jl	.L26
	movl	count2.4114(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.4114(%rip)
	movq	outputString.4112(%rip), %rdx
	movl	count2.4114(%rip), %eax
	cltq
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	outputString.4112(%rip), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	stringTocharArray, .-stringTocharArray
	.section	.rodata
.LC5:
	.string	"March"
.LC6:
	.string	"03"
.LC7:
	.string	"04"
	.text
	.globl	outputDate2OutputString
	.type	outputDate2OutputString, @function
outputDate2OutputString:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	24(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	leaq	.LC5(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, -52(%rbp)
	cmpl	$0, -52(%rbp)
	je	.L29
	leaq	.LC6(%rip), %rax
	movq	%rax, -48(%rbp)
	jmp	.L30
.L29:
	leaq	.LC7(%rip), %rax
	movq	%rax, -48(%rbp)
.L30:
	movl	36(%rbp), %eax
	movl	%eax, %edi
	call	itoa
	movq	%rax, -32(%rbp)
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	myConcat
	movq	%rax, -24(%rbp)
	movl	32(%rbp), %eax
	movl	%eax, %edi
	call	itoa
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	myConcat
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	outputDate2OutputString, .-outputDate2OutputString
	.section	.rodata
	.align 8
.LC8:
	.string	"\n----------------------------------------\nDemo Array Illustration through printf():\n----------------------------------------"
.LC9:
	.string	"\nChar String Array:"
.LC10:
	.string	"[%d]"
.LC11:
	.string	"[\\0]"
.LC12:
	.string	" %c "
	.align 8
.LC13:
	.string	"\nIndex \t Hex Address \t Char \t Hex / Dec \t Byte"
.LC14:
	.string	"%d\t %p\t %c\t %x / %u\t %ld \n"
.LC15:
	.string	"%d\t %p\t \\0\t  %x / %x\t\t %ld \n"
	.text
	.globl	dispDemoArray
	.type	dispDemoArray, @function
dispDemoArray:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	leaq	.LC8(%rip), %rdi
	call	puts@PLT
	movl	$0, -20(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	leaq	.LC9(%rip), %rdi
	call	puts@PLT
	movl	$0, -20(%rbp)
	jmp	.L33
.L34:
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC10(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -20(%rbp)
	addq	$1, -16(%rbp)
.L33:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L34
	leaq	.LC11(%rip), %rdi
	call	puts@PLT
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.L35
.L36:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC12(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$1, -16(%rbp)
.L35:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L36
	movl	$10, %edi
	call	putchar@PLT
	leaq	.LC13(%rip), %rdi
	call	puts@PLT
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L37
.L38:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	movq	%rax, %rdi
	call	decimalToBinary
	movq	%rax, %r8
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edi
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edx
	movl	-20(%rbp), %eax
	movslq	%eax, %rsi
	movq	-8(%rbp), %rax
	addq	%rax, %rsi
	movl	-20(%rbp), %eax
	subq	$8, %rsp
	pushq	%r8
	movl	%edi, %r9d
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movq	%rsi, %rdx
	movl	%eax, %esi
	leaq	.LC14(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$16, %rsp
	addq	$1, -8(%rbp)
	addl	$1, -20(%rbp)
.L37:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L38
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	movq	%rax, %rdi
	call	decimalToBinary
	movq	%rax, %rdi
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edx
	movl	-20(%rbp), %eax
	movslq	%eax, %rsi
	movq	-8(%rbp), %rax
	addq	%rax, %rsi
	movl	-20(%rbp), %eax
	movq	%rdi, %r9
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movq	%rsi, %rdx
	movl	%eax, %esi
	leaq	.LC15(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	dispDemoArray, .-dispDemoArray
	.globl	binary2hex
	.type	binary2hex, @function
binary2hex:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -12(%rbp)
	movl	$1, -8(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	movq	%rax, %rdi
	call	decimalToBinary
	movl	%eax, -16(%rbp)
	jmp	.L40
.L41:
	movl	-16(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	imull	-8(%rbp), %eax
	addl	%eax, -12(%rbp)
	sall	-8(%rbp)
	movl	-16(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%rbp)
.L40:
	cmpl	$0, -16(%rbp)
	jne	.L41
	movl	-12(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	binary2hex, .-binary2hex
	.globl	defineTMstruct
	.type	defineTMstruct, @function
defineTMstruct:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -72(%rbp)
	movl	%esi, -76(%rbp)
	movl	%edx, -80(%rbp)
	movl	%ecx, -84(%rbp)
	movl	-84(%rbp), %eax
	movl	%eax, -52(%rbp)
	movl	-80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -48(%rbp)
	movl	-76(%rbp), %eax
	subl	$1900, %eax
	movl	%eax, -44(%rbp)
	movl	$0, -56(%rbp)
	movl	$0, -60(%rbp)
	movl	$1, -64(%rbp)
	movl	$0, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rcx
	movq	%rdx, (%rax)
	movq	%rcx, 8(%rax)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	%rdx, 16(%rax)
	movq	%rcx, 24(%rax)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	%rdx, 32(%rax)
	movq	%rcx, 40(%rax)
	movq	-16(%rbp), %rdx
	movq	%rdx, 48(%rax)
	movq	-72(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	defineTMstruct, .-defineTMstruct
	.globl	compareStrings
	.type	compareStrings, @function
compareStrings:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$1, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L46
.L49:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-8(%rbp), %eax
	movslq	%eax, %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L47
	movl	$0, -4(%rbp)
	jmp	.L48
.L47:
	addl	$1, -8(%rbp)
.L46:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L49
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L49
.L48:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	compareStrings, .-compareStrings
	.section	.rodata
.LC16:
	.string	"A14"
.LC17:
	.string	"A3"
.LC18:
	.string	"M23"
.LC19:
	.string	"A11"
.LC20:
	.string	"M31"
.LC21:
	.string	"A18"
.LC22:
	.string	"A8"
.LC23:
	.string	"M28"
.LC24:
	.string	"A16"
.LC25:
	.string	"A5"
.LC26:
	.string	"M25"
.LC27:
	.string	"A13"
.LC28:
	.string	"A2"
.LC29:
	.string	"M22"
.LC30:
	.string	"A10"
.LC31:
	.string	"M30"
.LC32:
	.string	"A17"
.LC33:
	.string	"A7"
.LC34:
	.string	"M27"
	.text
	.globl	returnTableA
	.type	returnTableA, @function
returnTableA:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$272, %rsp
	movl	%edi, -260(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -240(%rbp)
	movl	$52, -236(%rbp)
	movl	$105, -232(%rbp)
	movl	$157, -228(%rbp)
	movl	$210, -224(%rbp)
	movl	$263, -220(%rbp)
	movl	$315, -216(%rbp)
	movl	$368, -212(%rbp)
	movl	$421, -208(%rbp)
	movl	$473, -204(%rbp)
	movl	$562, -200(%rbp)
	movl	$578, -196(%rbp)
	movl	$631, -192(%rbp)
	movl	$684, -188(%rbp)
	movl	$736, -184(%rbp)
	movl	$789, -180(%rbp)
	movl	$842, -176(%rbp)
	movl	$894, -172(%rbp)
	movl	$947, -168(%rbp)
	leaq	.LC16(%rip), %rax
	movq	%rax, -160(%rbp)
	leaq	.LC17(%rip), %rax
	movq	%rax, -152(%rbp)
	leaq	.LC18(%rip), %rax
	movq	%rax, -144(%rbp)
	leaq	.LC19(%rip), %rax
	movq	%rax, -136(%rbp)
	leaq	.LC20(%rip), %rax
	movq	%rax, -128(%rbp)
	leaq	.LC21(%rip), %rax
	movq	%rax, -120(%rbp)
	leaq	.LC22(%rip), %rax
	movq	%rax, -112(%rbp)
	leaq	.LC23(%rip), %rax
	movq	%rax, -104(%rbp)
	leaq	.LC24(%rip), %rax
	movq	%rax, -96(%rbp)
	leaq	.LC25(%rip), %rax
	movq	%rax, -88(%rbp)
	leaq	.LC26(%rip), %rax
	movq	%rax, -80(%rbp)
	leaq	.LC27(%rip), %rax
	movq	%rax, -72(%rbp)
	leaq	.LC28(%rip), %rax
	movq	%rax, -64(%rbp)
	leaq	.LC29(%rip), %rax
	movq	%rax, -56(%rbp)
	leaq	.LC30(%rip), %rax
	movq	%rax, -48(%rbp)
	leaq	.LC31(%rip), %rax
	movq	%rax, -40(%rbp)
	leaq	.LC32(%rip), %rax
	movq	%rax, -32(%rbp)
	leaq	.LC33(%rip), %rax
	movq	%rax, -24(%rbp)
	leaq	.LC34(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	-260(%rbp), %eax
	movl	%eax, %edi
	call	returnYearDiv19
	movl	%eax, -252(%rbp)
	movl	-252(%rbp), %eax
	movl	%eax, -248(%rbp)
	movl	-248(%rbp), %edx
	leaq	-240(%rbp), %rax
	movl	$19, %esi
	movq	%rax, %rdi
	call	findIndex
	movl	%eax, -244(%rbp)
	movl	-244(%rbp), %eax
	cltq
	movq	-160(%rbp,%rax,8), %rax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L53
	call	__stack_chk_fail@PLT
.L53:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	returnTableA, .-returnTableA
	.globl	returnTableAB
	.type	returnTableAB, @function
returnTableAB:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$336, %rsp
	movl	%edi, -324(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -308(%rbp)
	movl	$0, -304(%rbp)
	movl	$0, -300(%rbp)
	movl	$0, -296(%rbp)
	movl	$1, -292(%rbp)
	movl	$1, -288(%rbp)
	movl	$1, -284(%rbp)
	movl	$1, -280(%rbp)
	movl	$2, -276(%rbp)
	movl	$2, -272(%rbp)
	movl	$2, -268(%rbp)
	movl	$2, -264(%rbp)
	movl	$2, -260(%rbp)
	movl	$3, -256(%rbp)
	movl	$3, -252(%rbp)
	movl	$3, -248(%rbp)
	movl	$3, -244(%rbp)
	movl	$4, -240(%rbp)
	movl	$4, -236(%rbp)
	movl	$4, -232(%rbp)
	movl	$4, -228(%rbp)
	movl	$5, -224(%rbp)
	movl	$5, -220(%rbp)
	movl	$5, -216(%rbp)
	movl	$5, -212(%rbp)
	movl	$6, -208(%rbp)
	movl	$6, -204(%rbp)
	movl	$6, -200(%rbp)
	movl	$6, -196(%rbp)
	movl	$0, -176(%rbp)
	movl	$52, -172(%rbp)
	movl	$105, -168(%rbp)
	movl	$157, -164(%rbp)
	movl	$210, -160(%rbp)
	movl	$263, -156(%rbp)
	movl	$315, -152(%rbp)
	movl	$368, -148(%rbp)
	movl	$421, -144(%rbp)
	movl	$473, -140(%rbp)
	movl	$562, -136(%rbp)
	movl	$578, -132(%rbp)
	movl	$631, -128(%rbp)
	movl	$684, -124(%rbp)
	movl	$736, -120(%rbp)
	movl	$789, -116(%rbp)
	movl	$842, -112(%rbp)
	movl	$894, -108(%rbp)
	movl	$947, -104(%rbp)
	movl	-220(%rbp), %eax
	movl	%eax, -96(%rbp)
	movl	-292(%rbp), %eax
	movl	%eax, -92(%rbp)
	movl	-232(%rbp), %eax
	movl	%eax, -88(%rbp)
	movl	-272(%rbp), %eax
	movl	%eax, -84(%rbp)
	movl	-212(%rbp), %eax
	movl	%eax, -80(%rbp)
	movl	-268(%rbp), %eax
	movl	%eax, -76(%rbp)
	movl	-204(%rbp), %eax
	movl	%eax, -72(%rbp)
	movl	-260(%rbp), %eax
	movl	%eax, -68(%rbp)
	movl	-300(%rbp), %eax
	movl	%eax, -64(%rbp)
	movl	-256(%rbp), %eax
	movl	%eax, -60(%rbp)
	movl	-196(%rbp), %eax
	movl	%eax, -56(%rbp)
	movl	-236(%rbp), %eax
	movl	%eax, -52(%rbp)
	movl	-308(%rbp), %eax
	movl	%eax, -48(%rbp)
	movl	-244(%rbp), %eax
	movl	%eax, -44(%rbp)
	movl	-288(%rbp), %eax
	movl	%eax, -40(%rbp)
	movl	-228(%rbp), %eax
	movl	%eax, -36(%rbp)
	movl	-284(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-224(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-280(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-324(%rbp), %eax
	movl	%eax, %edi
	call	returnYearDiv19
	movl	%eax, -192(%rbp)
	movl	-192(%rbp), %eax
	movl	%eax, -188(%rbp)
	movl	-188(%rbp), %edx
	leaq	-176(%rbp), %rax
	movl	$19, %esi
	movq	%rax, %rdi
	call	findIndex
	movl	%eax, -184(%rbp)
	movl	-184(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %eax
	movl	%eax, -180(%rbp)
	movl	-180(%rbp), %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L56
	call	__stack_chk_fail@PLT
.L56:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	returnTableAB, .-returnTableAB
	.globl	returnYearDiv19
	.type	returnYearDiv19, @function
returnYearDiv19:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -36(%rbp)
	cvtsi2sd	-36(%rbp), %xmm0
	movsd	.LC35(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, -24(%rbp)
	cvtsi2sd	-24(%rbp), %xmm1
	movsd	-16(%rbp), %xmm0
	subsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm1
	movsd	.LC36(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	returnYearDiv19, .-returnYearDiv19
	.globl	returnTableD
	.type	returnTableD, @function
returnTableD:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	subl	$18, %eax
	cmpl	$15, %eax
	ja	.L60
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L62(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L62(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L62:
	.long	.L64-.L62
	.long	.L68-.L62
	.long	.L67-.L62
	.long	.L66-.L62
	.long	.L61-.L62
	.long	.L65-.L62
	.long	.L68-.L62
	.long	.L63-.L62
	.long	.L67-.L62
	.long	.L66-.L62
	.long	.L65-.L62
	.long	.L64-.L62
	.long	.L60-.L62
	.long	.L63-.L62
	.long	.L60-.L62
	.long	.L61-.L62
	.text
.L65:
	movl	$0, -4(%rbp)
	jmp	.L60
.L64:
	movl	$1, -4(%rbp)
	jmp	.L60
.L68:
	movl	$2, -4(%rbp)
	jmp	.L60
.L63:
	movl	$3, -4(%rbp)
	jmp	.L60
.L67:
	movl	$4, -4(%rbp)
	jmp	.L60
.L66:
	movl	$5, -4(%rbp)
	jmp	.L60
.L61:
	movl	$6, -4(%rbp)
	nop
.L60:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	returnTableD, .-returnTableD
	.globl	returnTableE
	.type	returnTableE, @function
returnTableE:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	cmpl	$18, -20(%rbp)
	ja	.L71
	movl	-20(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L73(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L73(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L73:
	.long	.L77-.L73
	.long	.L76-.L73
	.long	.L75-.L73
	.long	.L74-.L73
	.long	.L72-.L73
	.long	.L79-.L73
	.long	.L78-.L73
	.long	.L77-.L73
	.long	.L76-.L73
	.long	.L75-.L73
	.long	.L74-.L73
	.long	.L72-.L73
	.long	.L79-.L73
	.long	.L78-.L73
	.long	.L77-.L73
	.long	.L76-.L73
	.long	.L75-.L73
	.long	.L74-.L73
	.long	.L72-.L73
	.text
.L77:
	movl	$7, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L71
.L76:
	movl	$6, -8(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L71
.L75:
	movl	$5, -8(%rbp)
	movl	$2, -4(%rbp)
	jmp	.L71
.L74:
	movl	$4, -8(%rbp)
	movl	$3, -4(%rbp)
	jmp	.L71
.L72:
	movl	$3, -8(%rbp)
	movl	$4, -4(%rbp)
	jmp	.L71
.L79:
	movl	$2, -8(%rbp)
	movl	$5, -4(%rbp)
	jmp	.L71
.L78:
	movl	$1, -8(%rbp)
	movl	$6, -4(%rbp)
	nop
.L71:
	movl	-8(%rbp), %eax
	movl	%eax, returnArray.4264(%rip)
	movl	-4(%rbp), %eax
	movl	%eax, 4+returnArray.4264(%rip)
	leaq	returnArray.4264(%rip), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	returnTableE, .-returnTableE
	.globl	findIndex
	.type	findIndex, @function
findIndex:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L82
.L85:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	%eax, -32(%rbp)
	jne	.L83
	movl	-4(%rbp), %eax
	jmp	.L84
.L83:
	addl	$1, -4(%rbp)
.L82:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L85
	movl	$-1, %eax
.L84:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	findIndex, .-findIndex
	.section	.rodata
.LC37:
	.string	"Sunday"
.LC38:
	.string	"Monday"
.LC39:
	.string	"Tuesday"
.LC40:
	.string	"Wednesday"
.LC41:
	.string	"Thursday"
.LC42:
	.string	"Friday"
.LC43:
	.string	"Saturday"
.LC44:
	.string	"April"
	.text
	.globl	pfm_algorithm
	.type	pfm_algorithm, @function
pfm_algorithm:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$192, %rsp
	movq	%rdi, -184(%rbp)
	movl	%esi, -188(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC37(%rip), %rax
	movq	%rax, -64(%rbp)
	leaq	.LC38(%rip), %rax
	movq	%rax, -56(%rbp)
	leaq	.LC39(%rip), %rax
	movq	%rax, -48(%rbp)
	leaq	.LC40(%rip), %rax
	movq	%rax, -40(%rbp)
	leaq	.LC41(%rip), %rax
	movq	%rax, -32(%rbp)
	leaq	.LC42(%rip), %rax
	movq	%rax, -24(%rbp)
	leaq	.LC43(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	-188(%rbp), %eax
	movl	%eax, %edi
	call	returnTableAB
	movl	%eax, -164(%rbp)
	movl	-188(%rbp), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -160(%rbp)
	movl	-160(%rbp), %eax
	imull	$-100, %eax, %edx
	movl	-188(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -156(%rbp)
	movl	$0, -152(%rbp)
	movl	-156(%rbp), %eax
	movl	%eax, %edi
	call	returnTableD
	movl	%eax, -148(%rbp)
	movl	-164(%rbp), %edx
	movl	-152(%rbp), %eax
	addl	%eax, %edx
	movl	-148(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -144(%rbp)
	movl	-144(%rbp), %eax
	movl	%eax, %edi
	call	returnTableE
	movq	%rax, -120(%rbp)
	movl	$1, -140(%rbp)
	movl	-140(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-120(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -136(%rbp)
	movl	-188(%rbp), %eax
	movl	%eax, %edi
	call	returnTableA
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -165(%rbp)
	cmpb	$77, -165(%rbp)
	jne	.L87
	leaq	.LC5(%rip), %rax
	movq	%rax, -128(%rbp)
	jmp	.L88
.L87:
	leaq	.LC44(%rip), %rax
	movq	%rax, -128(%rbp)
.L88:
	movq	-112(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -132(%rbp)
	movl	-136(%rbp), %eax
	cltq
	movq	-64(%rbp,%rax,8), %rax
	movq	%rax, -96(%rbp)
	movl	-132(%rbp), %eax
	movl	%eax, -80(%rbp)
	movq	-128(%rbp), %rax
	movq	%rax, -88(%rbp)
	movl	-188(%rbp), %eax
	movl	%eax, -76(%rbp)
	movq	-184(%rbp), %rcx
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-80(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-184(%rbp), %rax
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L90
	call	__stack_chk_fail@PLT
.L90:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	pfm_algorithm, .-pfm_algorithm
	.globl	gauss_Easter_algorithm
	.type	gauss_Easter_algorithm, @function
gauss_Easter_algorithm:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
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
	movl	-100(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -92(%rbp)
	movl	-100(%rbp), %ecx
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
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -88(%rbp)
	movl	-100(%rbp), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -84(%rbp)
	movl	-84(%rbp), %eax
	sall	$3, %eax
	leal	13(%rax), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$3, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, -48(%rbp)
	movsd	-48(%rbp), %xmm0
	call	floor@PLT
	cvttsd2si	%xmm0, %eax
	movl	%eax, -80(%rbp)
	movl	-84(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	call	floor@PLT
	cvttsd2si	%xmm0, %eax
	movl	%eax, -76(%rbp)
	movl	$15, %eax
	subl	-80(%rbp), %eax
	movl	%eax, %edx
	movl	-84(%rbp), %eax
	addl	%edx, %eax
	subl	-76(%rbp), %eax
	movl	%eax, %ecx
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
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	imull	$30, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -72(%rbp)
	movl	-84(%rbp), %eax
	addl	$4, %eax
	subl	-76(%rbp), %eax
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
	movl	%eax, -68(%rbp)
	movl	-68(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -68(%rbp)
	movl	-96(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%eax, %edx
	movl	-72(%rbp), %eax
	leal	(%rdx,%rax), %ecx
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
	movl	%eax, -64(%rbp)
	movl	-64(%rbp), %eax
	imull	$30, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -64(%rbp)
	movl	-88(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-92(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-64(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	%ecx, %eax
	leal	(%rax,%rax), %edx
	movl	-68(%rbp), %eax
	leal	(%rdx,%rax), %ecx
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
	movl	%eax, -60(%rbp)
	movl	-60(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -60(%rbp)
	cmpl	$6, -60(%rbp)
	jne	.L92
	cmpl	$29, -64(%rbp)
	jne	.L93
	movl	$19, -104(%rbp)
	jmp	.L92
.L93:
	movl	-72(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	leal	(%rax,%rdx), %ecx
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
	imull	$30, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	cmpl	$8, %eax
	jg	.L92
	movl	$18, -104(%rbp)
.L92:
	movl	-64(%rbp), %eax
	leal	22(%rax), %edx
	movl	-60(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -104(%rbp)
	cmpl	$31, -104(%rbp)
	jle	.L94
	leaq	.LC44(%rip), %rax
	movq	%rax, -56(%rbp)
	subl	$31, -104(%rbp)
	jmp	.L95
.L94:
	leaq	.LC5(%rip), %rax
	movq	%rax, -56(%rbp)
.L95:
	leaq	.LC37(%rip), %rax
	movq	%rax, -32(%rbp)
	movl	-104(%rbp), %eax
	movl	%eax, -16(%rbp)
	movq	-56(%rbp), %rax
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
.LFE24:
	.size	gauss_Easter_algorithm, .-gauss_Easter_algorithm
	.globl	anonymous_Gregorian_algorithm
	.type	anonymous_Gregorian_algorithm, @function
anonymous_Gregorian_algorithm:
.LFB25:
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
	jne	.L98
	leaq	.LC5(%rip), %rax
	movq	%rax, -40(%rbp)
	jmp	.L99
.L98:
	leaq	.LC44(%rip), %rax
	movq	%rax, -40(%rbp)
.L99:
	leaq	.LC37(%rip), %rax
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
.LFE25:
	.size	anonymous_Gregorian_algorithm, .-anonymous_Gregorian_algorithm
	.section	.rodata
.LC45:
	.string	""
	.text
	.globl	meeus_Julian_algorithm
	.type	meeus_Julian_algorithm, @function
meeus_Julian_algorithm:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -88(%rbp)
	movl	%esi, -92(%rbp)
	movl	-92(%rbp), %eax
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -68(%rbp)
	movl	-72(%rbp), %ecx
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
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -64(%rbp)
	movl	-72(%rbp), %ecx
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
	movl	%eax, -60(%rbp)
	movl	-60(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
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
	movl	%eax, -56(%rbp)
	movl	-56(%rbp), %eax
	imull	$30, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -56(%rbp)
	movl	-64(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-68(%rbp), %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	-56(%rbp), %eax
	leal	34(%rax), %ecx
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
	movl	%eax, -52(%rbp)
	movl	-52(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -52(%rbp)
	movl	-56(%rbp), %edx
	movl	-52(%rbp), %eax
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
	movl	-56(%rbp), %edx
	movl	-52(%rbp), %eax
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
	jne	.L102
	leaq	.LC5(%rip), %rax
	movq	%rax, -40(%rbp)
	jmp	.L103
.L102:
	leaq	.LC44(%rip), %rax
	movq	%rax, -40(%rbp)
.L103:
	leaq	.LC45(%rip), %rax
	movq	%rax, -32(%rbp)
	movl	-44(%rbp), %eax
	movl	%eax, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	-92(%rbp), %eax
	movl	%eax, -12(%rbp)
	movq	-88(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-16(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-88(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	meeus_Julian_algorithm, .-meeus_Julian_algorithm
	.section	.rodata
	.align 8
.LC46:
	.string	"----------------------------------------\nEaster %d Dates:\n----------------------------------------\n"
	.align 8
.LC47:
	.string	"\nGauss Output:\n\t%s %d, %s %d -- Gregorian Calendar, mixed var array\n"
	.align 8
.LC48:
	.string	"\nAnonymous Output:\n\t%s %d, %s %d -- Gregorian Calendar, mixed var array\n"
	.align 8
.LC49:
	.string	"\nMeeus Output:\n\t%s %d, %s %d -- Julian Calendar, mixed var array\n"
	.align 8
.LC50:
	.string	"\nPaschal Full Moon (PFM) Output:\n\t%s %d, %s %d -- Gregorian Calendar, mixed var array\n\n"
	.align 8
.LC51:
	.string	"PFM output as a single char array value:\n\tString array: %s\n"
	.align 8
.LC52:
	.string	"\n------------------------\nThis following 'last line' line will be used as a string to input into Bash for any further POSIX formatted date calculations."
.LC53:
	.string	"\n%s"
	.text
	.globl	verboseDisplay
	.type	verboseDisplay, @function
verboseDisplay:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -36(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	-36(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC46(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-32(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	gauss_Easter_algorithm
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC47(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-80(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	anonymous_Gregorian_algorithm
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC48(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-80(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	meeus_Julian_algorithm
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC49(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-80(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	pfm_algorithm
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC50(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	subq	$8, %rsp
	pushq	-16(%rbp)
	pushq	-24(%rbp)
	pushq	-32(%rbp)
	call	outputDate2OutputString
	addq	$32, %rsp
	movq	%rax, outputString.4399(%rip)
	movq	outputString.4399(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC51(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	outputString.4399(%rip), %rax
	movq	%rax, %rdi
	call	dispDemoArray
	leaq	.LC52(%rip), %rdi
	call	puts@PLT
	movq	outputString.4399(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC53(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L106
	call	__stack_chk_fail@PLT
.L106:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	verboseDisplay, .-verboseDisplay
	.section	.rodata
.LC54:
	.string	"%s"
	.text
	.globl	simpleDisplay
	.type	simpleDisplay, @function
simpleDisplay:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	pfm_algorithm
	subq	$8, %rsp
	pushq	-16(%rbp)
	pushq	-24(%rbp)
	pushq	-32(%rbp)
	call	outputDate2OutputString
	addq	$32, %rsp
	movq	%rax, outputString.4404(%rip)
	movq	outputString.4404(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC54(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L108
	call	__stack_chk_fail@PLT
.L108:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	simpleDisplay, .-simpleDisplay
	.section	.rodata
	.align 8
.LC56:
	.string	"\nThe next Paschal Full Moon:\n\tThis year\n\tIn %f days\n\tOn %s %d %s %d"
	.text
	.globl	daysUntillPFM
	.type	daysUntillPFM, @function
daysUntillPFM:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$240, %rsp
	movl	%edi, -164(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-96(%rbp), %rax
	movl	-164(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	pfm_algorithm
	movl	-76(%rbp), %eax
	movl	%eax, -144(%rbp)
	movl	-80(%rbp), %eax
	movl	%eax, -140(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	leaq	.LC5(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, -136(%rbp)
	cmpl	$0, -136(%rbp)
	je	.L110
	movl	$3, -148(%rbp)
	jmp	.L111
.L110:
	movl	$4, -148(%rbp)
.L111:
	leaq	-240(%rbp), %rax
	movl	-140(%rbp), %ecx
	movl	-148(%rbp), %edx
	movl	-144(%rbp), %esi
	movq	%rax, %rdi
	call	defineTMstruct
	movq	-240(%rbp), %rax
	movq	-232(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-224(%rbp), %rax
	movq	-216(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-208(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -16(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	time@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	mktime@PLT
	movl	%eax, -132(%rbp)
	movq	-128(%rbp), %rdx
	movl	-132(%rbp), %eax
	cltq
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	difftime@PLT
	movq	%xmm0, %rax
	movq	%rax, -112(%rbp)
	movsd	-112(%rbp), %xmm0
	movsd	.LC55(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -104(%rbp)
	movl	-76(%rbp), %esi
	movq	-88(%rbp), %rcx
	movl	-80(%rbp), %edx
	movq	-96(%rbp), %rax
	movsd	-104(%rbp), %xmm0
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC56(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movsd	-104(%rbp), %xmm0
	cvttsd2si	%xmm0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L113
	call	__stack_chk_fail@PLT
.L113:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	daysUntillPFM, .-daysUntillPFM
	.section	.rodata
	.align 8
.LC57:
	.string	"\nThe next Paschal Ful Moon:\n\t NEXT year \n\tOn %s %d %s %d"
	.text
	.globl	nextPFM
	.type	nextPFM, @function
nextPFM:
.LFB30:
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
	movl	$2019, -40(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, %edi
	call	daysUntillPFM
	movl	%eax, -36(%rbp)
	cmpl	$0, -36(%rbp)
	jns	.L117
	movl	-40(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -40(%rbp)
	leaq	-32(%rbp), %rdx
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	pfm_algorithm
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC57(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L117:
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L116
	call	__stack_chk_fail@PLT
.L116:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	nextPFM, .-nextPFM
	.section	.rodata
.LC58:
	.string	"-v"
.LC59:
	.string	"-f"
	.text
	.globl	inputFlagType
	.type	inputFlagType, @function
inputFlagType:
.LFB31:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	leaq	.LC58(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, -8(%rbp)
	movq	-24(%rbp), %rax
	leaq	.LC59(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, -4(%rbp)
	cmpl	$0, -8(%rbp)
	je	.L119
	movl	$1, -12(%rbp)
	jmp	.L120
.L119:
	cmpl	$0, -4(%rbp)
	je	.L121
	movl	$2, -12(%rbp)
	jmp	.L120
.L121:
	movl	$0, -12(%rbp)
.L120:
	movl	-12(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE31:
	.size	inputFlagType, .-inputFlagType
	.globl	is4DigitChar
	.type	is4DigitChar, @function
is4DigitChar:
.LFB32:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	noOfChars
	movl	%eax, inputLength.4435(%rip)
	leaq	-16(%rbp), %rcx
	movq	-24(%rbp), %rax
	movl	$10, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strtol@PLT
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L124
	movl	inputLength.4435(%rip), %eax
	cmpl	$4, %eax
	jne	.L124
	movl	$1, isNumber.4436(%rip)
.L124:
	movl	isNumber.4436(%rip), %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L126
	call	__stack_chk_fail@PLT
.L126:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	is4DigitChar, .-is4DigitChar
	.globl	isVerboseFlag
	.type	isVerboseFlag, @function
isVerboseFlag:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC58(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, isVerbose.4441(%rip)
	movl	isVerbose.4441(%rip), %eax
	testl	%eax, %eax
	je	.L128
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	is4DigitChar
	movl	%eax, isNumber.4442(%rip)
.L128:
	movl	isNumber.4442(%rip), %eax
	testl	%eax, %eax
	je	.L129
	movl	$1, isVerbose.4441(%rip)
.L129:
	movl	isVerbose.4441(%rip), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	isVerboseFlag, .-isVerboseFlag
	.globl	isFileOutFlag
	.type	isFileOutFlag, @function
isFileOutFlag:
.LFB34:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC59(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, isFileOut.4447(%rip)
	movl	isFileOut.4447(%rip), %eax
	testl	%eax, %eax
	je	.L132
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	is4DigitChar
	movl	%eax, isNumber.4448(%rip)
.L132:
	movl	isNumber.4448(%rip), %eax
	testl	%eax, %eax
	jne	.L133
	movl	$1, isFileOut.4447(%rip)
.L133:
	movl	isFileOut.4447(%rip), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE34:
	.size	isFileOutFlag, .-isFileOutFlag
	.section	.rodata
.LC60:
	.string	"-h"
	.text
	.type	inspectMainInputs, @function
inspectMainInputs:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$2, -20(%rbp)
	je	.L136
	cmpl	$2, -20(%rbp)
	jg	.L137
	cmpl	$1, -20(%rbp)
	je	.L138
	jmp	.L139
.L137:
	cmpl	$3, -20(%rbp)
	je	.L140
	cmpl	$5, -20(%rbp)
	je	.L141
	jmp	.L139
.L138:
	movl	$1, isGoodInput.4458(%rip)
	jmp	.L142
.L136:
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	is4DigitChar
	movl	%eax, isNumber.4454(%rip)
	movq	-8(%rbp), %rax
	leaq	.LC60(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, isHelp.4455(%rip)
	movl	isNumber.4454(%rip), %eax
	testl	%eax, %eax
	jne	.L143
	movl	isHelp.4455(%rip), %eax
	testl	%eax, %eax
	je	.L152
.L143:
	movl	$1, isGoodInput.4458(%rip)
	jmp	.L152
.L140:
	movq	-32(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	isVerboseFlag
	movl	%eax, isVerbose.4456(%rip)
	movq	-32(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	isFileOutFlag
	movl	%eax, isFileOut.4457(%rip)
	movl	isVerbose.4456(%rip), %eax
	testl	%eax, %eax
	jne	.L145
	movl	isFileOut.4457(%rip), %eax
	testl	%eax, %eax
	je	.L153
.L145:
	movl	$1, isGoodInput.4458(%rip)
	jmp	.L153
.L141:
	movq	-32(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	isVerboseFlag
	movl	%eax, isVerbose.4456(%rip)
	movq	-32(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	isFileOutFlag
	movl	%eax, isFileOut.4457(%rip)
	movl	isVerbose.4456(%rip), %eax
	testl	%eax, %eax
	jne	.L147
	movl	isFileOut.4457(%rip), %eax
	testl	%eax, %eax
	je	.L148
.L147:
	movl	$1, isGoodInput.4458(%rip)
.L148:
	movq	-32(%rbp), %rax
	addq	$32, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	$24, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	isVerboseFlag
	movl	%eax, isVerbose.4456(%rip)
	movq	-32(%rbp), %rax
	addq	$32, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	$24, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	isFileOutFlag
	movl	%eax, isFileOut.4457(%rip)
	movl	isVerbose.4456(%rip), %eax
	testl	%eax, %eax
	jne	.L149
	movl	isFileOut.4457(%rip), %eax
	testl	%eax, %eax
	je	.L154
.L149:
	movl	$1, isGoodInput.4458(%rip)
	jmp	.L154
.L139:
	movl	$0, isGoodInput.4458(%rip)
	jmp	.L142
.L152:
	nop
	jmp	.L142
.L153:
	nop
	jmp	.L142
.L154:
	nop
.L142:
	movl	isGoodInput.4458(%rip), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	inspectMainInputs, .-inspectMainInputs
	.section	.rodata
.LC61:
	.string	"w+"
	.text
	.globl	print2file
	.type	print2file, @function
print2file:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	pfm_algorithm
	subq	$8, %rsp
	pushq	-16(%rbp)
	pushq	-24(%rbp)
	pushq	-32(%rbp)
	call	outputDate2OutputString
	addq	$32, %rsp
	movq	%rax, outputString.4470(%rip)
	movq	-64(%rbp), %rax
	leaq	.LC61(%rip), %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -40(%rbp)
	movq	outputString.4470(%rip), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fputs@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L156
	call	__stack_chk_fail@PLT
.L156:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	print2file, .-print2file
	.section	.rodata
.LC62:
	.string	"w"
	.align 8
.LC63:
	.string	"\n------------------------\nThis following 'last line' line will be used as a string to input into Bash for any further POSIX formatted date calculations.\n"
	.text
	.globl	print2fileVerbose
	.type	print2fileVerbose, @function
print2fileVerbose:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-64(%rbp), %rax
	leaq	.LC62(%rip), %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -40(%rbp)
	movl	-52(%rbp), %edx
	movq	-40(%rbp), %rax
	leaq	.LC46(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	leaq	-32(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	gauss_Easter_algorithm
	movl	-12(%rbp), %edi
	movq	-24(%rbp), %rsi
	movl	-16(%rbp), %ecx
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	%edi, %r9d
	movq	%rsi, %r8
	leaq	.LC47(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	leaq	-96(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	anonymous_Gregorian_algorithm
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-12(%rbp), %edi
	movq	-24(%rbp), %rsi
	movl	-16(%rbp), %ecx
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	%edi, %r9d
	movq	%rsi, %r8
	leaq	.LC48(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	leaq	-96(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	meeus_Julian_algorithm
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-12(%rbp), %edi
	movq	-24(%rbp), %rsi
	movl	-16(%rbp), %ecx
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	%edi, %r9d
	movq	%rsi, %r8
	leaq	.LC49(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	leaq	-96(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	pfm_algorithm
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-12(%rbp), %edi
	movq	-24(%rbp), %rsi
	movl	-16(%rbp), %ecx
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	%edi, %r9d
	movq	%rsi, %r8
	leaq	.LC50(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	subq	$8, %rsp
	pushq	-16(%rbp)
	pushq	-24(%rbp)
	pushq	-32(%rbp)
	call	outputDate2OutputString
	addq	$32, %rsp
	movq	%rax, outputString.4477(%rip)
	movq	outputString.4477(%rip), %rdx
	movq	-40(%rbp), %rax
	leaq	.LC51(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	movl	$153, %edx
	movl	$1, %esi
	leaq	.LC63(%rip), %rdi
	call	fwrite@PLT
	movq	outputString.4477(%rip), %rdx
	movq	-40(%rbp), %rax
	leaq	.LC53(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L158
	call	__stack_chk_fail@PLT
.L158:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	print2fileVerbose, .-print2fileVerbose
	.section	.rodata
	.align 8
.LC64:
	.ascii	"--------\n  Help\n--------\n\nCompile and build:\n\t gcc mai"
	.ascii	"n.c -o anyNameYouWant -lm\n\t gcc -o main main.c -lm\n\nExam"
	.ascii	"ple:\n\n  ./main -h\t\t## display this help display and retu"
	.ascii	"rn a 0-time to bash\n or\n  ./main\t\t## return the PFM for "
	.ascii	"this year\n or\n  ./main 2018\t\t## return the PFM for desir"
	.ascii	"ed year\n or\n  ./main -v 2018\t## return the PFM for desire"
	.ascii	"d year and Verbose info"
	.string	": Easter Day, next PFM, and memory allocation\n or\n  ./main -f ~/MyDocument/myOutputFile.txt\t\t## return the PFM for this year to a File\n or\n  ./main -v 2018 -f ~/MyDocument/myOutputFile.txt\t## return the PFM for desired year along with Verbose info\n\n0000000"
	.text
	.globl	helpDisplay
	.type	helpDisplay, @function
helpDisplay:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC64(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	helpDisplay, .-helpDisplay
	.section	.rodata
	.align 8
.LC65:
	.string	"------------------------\nBasic PMF Output Render:\n------------------------"
	.align 8
.LC66:
	.string	"\n\n\nVerbose PMF and Easter Output Render:"
	.align 8
.LC67:
	.string	"\n!!! Execution interupted !!!\nProvide valid inputs and try again :)"
	.text
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-80(%rbp), %rdx
	movl	-68(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	inspectMainInputs
	movl	%eax, isInputValid.4485(%rip)
	movl	isInputValid.4485(%rip), %eax
	testl	%eax, %eax
	je	.L161
	cmpl	$2, -68(%rbp)
	je	.L162
	cmpl	$2, -68(%rbp)
	jg	.L163
	cmpl	$1, -68(%rbp)
	je	.L164
	jmp	.L172
.L163:
	cmpl	$3, -68(%rbp)
	je	.L166
	cmpl	$5, -68(%rbp)
	je	.L167
	jmp	.L172
.L164:
	movl	$0, %eax
	call	returnYear
	movl	%eax, yearInt.4486(%rip)
	movl	yearInt.4486(%rip), %eax
	movl	%eax, %edi
	call	simpleDisplay
	jmp	.L172
.L162:
	movq	-80(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, yearInt.4486(%rip)
	movq	-80(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	leaq	.LC60(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, -60(%rbp)
	cmpl	$0, -60(%rbp)
	jne	.L168
	movl	yearInt.4486(%rip), %eax
	movl	%eax, %edi
	call	simpleDisplay
	jmp	.L172
.L168:
	movl	$0, %eax
	call	helpDisplay
	jmp	.L172
.L166:
	movq	-80(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	inputFlagType
	movl	%eax, flagInt.4487(%rip)
	movl	flagInt.4487(%rip), %eax
	cmpl	$1, %eax
	jne	.L170
	leaq	.LC65(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	nextPFM
	leaq	.LC66(%rip), %rdi
	call	puts@PLT
	movq	-80(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, yearInt.4486(%rip)
	movl	yearInt.4486(%rip), %eax
	movl	%eax, %edi
	call	verboseDisplay
	jmp	.L172
.L170:
	movl	$0, %eax
	call	returnYear
	movl	%eax, yearInt.4486(%rip)
	movq	-80(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -40(%rbp)
	movl	yearInt.4486(%rip), %eax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	print2file
	jmp	.L172
.L167:
	leaq	.LC65(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	nextPFM
	leaq	.LC66(%rip), %rdi
	call	puts@PLT
	movq	-80(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, yearInt.4486(%rip)
	movl	yearInt.4486(%rip), %eax
	movl	%eax, %edi
	call	verboseDisplay
	movq	-80(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -40(%rbp)
	movl	yearInt.4486(%rip), %eax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	print2fileVerbose
	nop
	jmp	.L172
.L161:
	leaq	.LC67(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	helpDisplay
	movl	$1, %edi
	call	exit@PLT
.L172:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.local	str1Len.4115
	.comm	str1Len.4115,4,4
	.local	str2Len.4116
	.comm	str2Len.4116,4,4
	.local	combinedLen.4117
	.comm	combinedLen.4117,4,4
	.local	outputString.4112
	.comm	outputString.4112,8,8
	.local	count2.4114
	.comm	count2.4114,4,4
	.local	count1.4113
	.comm	count1.4113,4,4
	.local	returnArray.4264
	.comm	returnArray.4264,8,8
	.local	outputString.4399
	.comm	outputString.4399,8,8
	.local	outputString.4404
	.comm	outputString.4404,8,8
	.local	inputLength.4435
	.comm	inputLength.4435,4,4
	.local	isNumber.4436
	.comm	isNumber.4436,4,4
	.local	isVerbose.4441
	.comm	isVerbose.4441,4,4
	.local	isNumber.4442
	.comm	isNumber.4442,4,4
	.local	isFileOut.4447
	.comm	isFileOut.4447,4,4
	.local	isNumber.4448
	.comm	isNumber.4448,4,4
	.local	isGoodInput.4458
	.comm	isGoodInput.4458,4,4
	.local	isNumber.4454
	.comm	isNumber.4454,4,4
	.local	isHelp.4455
	.comm	isHelp.4455,4,4
	.local	isVerbose.4456
	.comm	isVerbose.4456,4,4
	.local	isFileOut.4457
	.comm	isFileOut.4457,4,4
	.local	outputString.4470
	.comm	outputString.4470,8,8
	.local	outputString.4477
	.comm	outputString.4477,8,8
	.local	isInputValid.4485
	.comm	isInputValid.4485,4,4
	.local	yearInt.4486
	.comm	yearInt.4486,4,4
	.local	flagInt.4487
	.comm	flagInt.4487,4,4
	.section	.rodata
	.align 8
.LC2:
	.long	0
	.long	1072693248
	.align 8
.LC35:
	.long	0
	.long	1077084160
	.align 8
.LC36:
	.long	0
	.long	1083129856
	.align 8
.LC55:
	.long	0
	.long	1089804288
	.ident	"GCC: (GNU) 8.2.1 20181127"
	.section	.note.GNU-stack,"",@progbits
