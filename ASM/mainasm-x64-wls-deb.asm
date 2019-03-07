	.file	"main.c"
	.section	.rodata
.LC20:
	.string	"%Y"
	.text
	.globl	returnYear
	.type	returnYear, @function
returnYear:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	time@PLT
	cmpq	$-1, %rax
	je	.L2
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	localtime@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L2
	movq	-16(%rbp), %rdx
	leaq	-21(%rbp), %rax
	movq	%rdx, %rcx
	leaq	.LC20(%rip), %rdx
	movl	$5, %esi
	movq	%rax, %rdi
	call	strftime@PLT
	testq	%rax, %rax
	je	.L2
	leaq	-21(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	returnYear, .-returnYear
	.globl	noOfChars
	.type	noOfChars, @function
noOfChars:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L5
.L6:
	addl	$1, -4(%rbp)
.L5:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L6
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	noOfChars, .-noOfChars
	.section	.rodata
.LC21:
	.string	""
	.string	""
	.text
	.globl	myConcat
	.type	myConcat, @function
myConcat:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	leaq	.LC21(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -28(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	noOfChars
	movl	%eax, -20(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	noOfChars
	movl	%eax, -24(%rbp)
	movl	-20(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	jmp	.L9
.L10:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-40(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -4(%rbp)
.L9:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L10
	jmp	.L11
.L12:
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	addq	%rax, %rdx
	movl	-8(%rbp), %eax
	movslq	%eax, %rcx
	movq	-48(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -8(%rbp)
.L11:
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L12
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	myConcat, .-myConcat
	.section	.rodata
.LC23:
	.string	"%d"
	.text
	.globl	itoa
	.type	itoa, @function
itoa:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	cmpl	$0, -20(%rbp)
	je	.L15
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
	movsd	.LC22(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvttsd2si	%xmm0, %eax
	jmp	.L16
.L15:
	movl	$1, %eax
.L16:
	movl	%eax, -4(%rbp)
	cmpl	$0, -20(%rbp)
	jns	.L17
	addl	$1, -4(%rbp)
.L17:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rsi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -16(%rbp)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rsi
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC23(%rip), %rdx
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	itoa, .-itoa
	.globl	decimalToBinary
	.type	decimalToBinary, @function
decimalToBinary:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	$0, -8(%rbp)
	movq	$1, -16(%rbp)
	jmp	.L20
.L21:
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
	imulq	-16(%rbp), %rax
	addq	%rax, -8(%rbp)
	movq	-16(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	movq	%rax, -16(%rbp)
.L20:
	cmpq	$0, -40(%rbp)
	jne	.L21
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	decimalToBinary, .-decimalToBinary
	.globl	stringTocharArray
	.type	stringTocharArray, @function
stringTocharArray:
.LFB7:
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
	movl	%eax, str1Len.3943(%rip)
	movl	str1Len.3943(%rip), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	movl	%eax, str2Len.3944(%rip)
	movl	str1Len.3943(%rip), %edx
	movl	str2Len.3944(%rip), %eax
	addl	%edx, %eax
	movl	%eax, combinedLen.3945(%rip)
	movl	combinedLen.3945(%rip), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, outputString.3940(%rip)
	jmp	.L24
.L25:
	movq	outputString.3940(%rip), %rdx
	movl	count2.3942(%rip), %eax
	cltq
	addq	%rdx, %rax
	movb	$91, (%rax)
	movl	count2.3942(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.3942(%rip)
	movq	outputString.3940(%rip), %rdx
	movl	count2.3942(%rip), %eax
	cltq
	addq	%rax, %rdx
	movl	count1.3941(%rip), %eax
	movslq	%eax, %rcx
	movq	-8(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movl	count1.3941(%rip), %eax
	addl	$1, %eax
	movl	%eax, count1.3941(%rip)
	movl	count2.3942(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.3942(%rip)
	movq	outputString.3940(%rip), %rdx
	movl	count2.3942(%rip), %eax
	cltq
	addq	%rdx, %rax
	movb	$93, (%rax)
	movl	count1.3941(%rip), %edx
	movl	str1Len.3943(%rip), %eax
	cmpl	%eax, %edx
	jge	.L24
	movl	count2.3942(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.3942(%rip)
	movq	outputString.3940(%rip), %rdx
	movl	count2.3942(%rip), %eax
	cltq
	addq	%rdx, %rax
	movb	$44, (%rax)
	movl	count2.3942(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.3942(%rip)
.L24:
	movl	count1.3941(%rip), %edx
	movl	str1Len.3943(%rip), %eax
	cmpl	%eax, %edx
	jl	.L25
	movl	count2.3942(%rip), %eax
	addl	$1, %eax
	movl	%eax, count2.3942(%rip)
	movq	outputString.3940(%rip), %rdx
	movl	count2.3942(%rip), %eax
	cltq
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	outputString.3940(%rip), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	stringTocharArray, .-stringTocharArray
	.section	.rodata
.LC25:
	.string	"March"
.LC26:
	.string	"03"
.LC27:
	.string	"04"
	.text
	.globl	outputDate2OutputString
	.type	outputDate2OutputString, @function
outputDate2OutputString:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	leaq	.LC25(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	je	.L28
	leaq	.LC26(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L29
.L28:
	leaq	.LC27(%rip), %rax
	movq	%rax, -8(%rbp)
.L29:
	movl	36(%rbp), %eax
	movl	%eax, %edi
	call	itoa
	movq	%rax, -32(%rbp)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	myConcat
	movq	%rax, -40(%rbp)
	movl	32(%rbp), %eax
	movl	%eax, %edi
	call	itoa
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	myConcat
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	outputDate2OutputString, .-outputDate2OutputString
	.section	.rodata
	.align 8
.LC28:
	.string	"\n----------------------------------------\nDemo Array Illustration through printf():\n----------------------------------------"
.LC29:
	.string	"\nChar String Array:"
.LC30:
	.string	"[%d]"
.LC31:
	.string	"[\\0]"
.LC32:
	.string	" %c "
	.align 8
.LC33:
	.string	"\nIndex \t Hex Address \t Char \t Hex / Dec \t Byte"
.LC34:
	.string	"%d\t %p\t %c\t %x / %u\t %ld \n"
.LC35:
	.string	"%d\t %p\t \\0\t  %x / %x\t\t %ld \n"
	.text
	.globl	dispDemoArray
	.type	dispDemoArray, @function
dispDemoArray:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	leaq	.LC28(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	leaq	.LC29(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L32
.L33:
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC30(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
	addq	$1, -16(%rbp)
.L32:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L33
	leaq	.LC31(%rip), %rdi
	call	puts@PLT
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.L34
.L35:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC32(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$1, -16(%rbp)
.L34:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L35
	movl	$10, %edi
	call	putchar@PLT
	leaq	.LC33(%rip), %rdi
	call	puts@PLT
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L36
.L37:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	movq	%rax, %rdi
	call	decimalToBinary
	movq	%rax, %r8
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edi
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rsi
	movq	-24(%rbp), %rax
	addq	%rax, %rsi
	movl	-4(%rbp), %eax
	subq	$8, %rsp
	pushq	%r8
	movl	%edi, %r9d
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movq	%rsi, %rdx
	movl	%eax, %esi
	leaq	.LC34(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$16, %rsp
	addq	$1, -24(%rbp)
	addl	$1, -4(%rbp)
.L36:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L37
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	movq	%rax, %rdi
	call	decimalToBinary
	movq	%rax, %rdi
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rsi
	movq	-24(%rbp), %rax
	addq	%rax, %rsi
	movl	-4(%rbp), %eax
	movq	%rdi, %r9
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movq	%rsi, %rdx
	movl	%eax, %esi
	leaq	.LC35(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	dispDemoArray, .-dispDemoArray
	.globl	binary2hex
	.type	binary2hex, @function
binary2hex:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -8(%rbp)
	movl	$1, -12(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	movq	%rax, %rdi
	call	decimalToBinary
	movl	%eax, -4(%rbp)
	jmp	.L39
.L40:
	movl	-4(%rbp), %ecx
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
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	imull	-12(%rbp), %eax
	addl	%eax, -8(%rbp)
	sall	-12(%rbp)
	movl	-4(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -4(%rbp)
.L39:
	cmpl	$0, -4(%rbp)
	jne	.L40
	movl	-8(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	binary2hex, .-binary2hex
	.globl	defineTMstruct
	.type	defineTMstruct, @function
defineTMstruct:
.LFB11:
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
	movq	%rdx, (%rax)
	movq	-56(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-48(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-40(%rbp), %rdx
	movq	%rdx, 24(%rax)
	movq	-32(%rbp), %rdx
	movq	%rdx, 32(%rax)
	movq	-24(%rbp), %rdx
	movq	%rdx, 40(%rax)
	movq	-16(%rbp), %rdx
	movq	%rdx, 48(%rax)
	movq	-72(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	defineTMstruct, .-defineTMstruct
	.globl	compareStrings
	.type	compareStrings, @function
compareStrings:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$1, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L45
.L48:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L46
	movl	$0, -8(%rbp)
	jmp	.L47
.L46:
	addl	$1, -4(%rbp)
.L45:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L48
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L48
.L47:
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	compareStrings, .-compareStrings
	.section	.rodata
.LC0:
	.string	"A14"
.LC1:
	.string	"A3"
.LC2:
	.string	"M23"
.LC3:
	.string	"A11"
.LC4:
	.string	"M31"
.LC5:
	.string	"A18"
.LC6:
	.string	"A8"
.LC7:
	.string	"M28"
.LC8:
	.string	"A16"
.LC9:
	.string	"A5"
.LC10:
	.string	"M25"
.LC11:
	.string	"A13"
.LC12:
	.string	"A2"
.LC13:
	.string	"M22"
.LC14:
	.string	"A10"
.LC15:
	.string	"M30"
.LC16:
	.string	"A17"
.LC17:
	.string	"A7"
.LC18:
	.string	"M27"
	.data
	.align 32
.LC36:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.quad	.LC5
	.quad	.LC6
	.quad	.LC7
	.quad	.LC8
	.quad	.LC9
	.quad	.LC10
	.quad	.LC11
	.quad	.LC12
	.quad	.LC13
	.quad	.LC14
	.quad	.LC15
	.quad	.LC16
	.quad	.LC17
	.quad	.LC18
	.text
	.globl	returnTableA
	.type	returnTableA, @function
returnTableA:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$272, %rsp
	movl	%edi, -260(%rbp)
	movl	$0, -96(%rbp)
	movl	$52, -92(%rbp)
	movl	$105, -88(%rbp)
	movl	$157, -84(%rbp)
	movl	$210, -80(%rbp)
	movl	$263, -76(%rbp)
	movl	$315, -72(%rbp)
	movl	$368, -68(%rbp)
	movl	$421, -64(%rbp)
	movl	$473, -60(%rbp)
	movl	$562, -56(%rbp)
	movl	$578, -52(%rbp)
	movl	$631, -48(%rbp)
	movl	$684, -44(%rbp)
	movl	$736, -40(%rbp)
	movl	$789, -36(%rbp)
	movl	$842, -32(%rbp)
	movl	$894, -28(%rbp)
	movl	$947, -24(%rbp)
	leaq	-256(%rbp), %rax
	leaq	.LC36(%rip), %rdx
	movl	$19, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movl	-260(%rbp), %eax
	movl	%eax, %edi
	call	returnYearDiv19
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %edx
	leaq	-96(%rbp), %rax
	movl	$19, %esi
	movq	%rax, %rdi
	call	findIndex
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	cltq
	movq	-256(%rbp,%rax,8), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	returnTableA, .-returnTableA
	.globl	returnTableAB
	.type	returnTableAB, @function
returnTableAB:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$304, %rsp
	movl	%edi, -292(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	$1, -20(%rbp)
	movl	$1, -24(%rbp)
	movl	$1, -28(%rbp)
	movl	$1, -32(%rbp)
	movl	$2, -36(%rbp)
	movl	$2, -40(%rbp)
	movl	$2, -44(%rbp)
	movl	$2, -48(%rbp)
	movl	$2, -52(%rbp)
	movl	$3, -56(%rbp)
	movl	$3, -60(%rbp)
	movl	$3, -64(%rbp)
	movl	$3, -68(%rbp)
	movl	$4, -72(%rbp)
	movl	$4, -76(%rbp)
	movl	$4, -80(%rbp)
	movl	$4, -84(%rbp)
	movl	$5, -88(%rbp)
	movl	$5, -92(%rbp)
	movl	$5, -96(%rbp)
	movl	$5, -100(%rbp)
	movl	$6, -104(%rbp)
	movl	$6, -108(%rbp)
	movl	$6, -112(%rbp)
	movl	$6, -116(%rbp)
	movl	$0, -208(%rbp)
	movl	$52, -204(%rbp)
	movl	$105, -200(%rbp)
	movl	$157, -196(%rbp)
	movl	$210, -192(%rbp)
	movl	$263, -188(%rbp)
	movl	$315, -184(%rbp)
	movl	$368, -180(%rbp)
	movl	$421, -176(%rbp)
	movl	$473, -172(%rbp)
	movl	$562, -168(%rbp)
	movl	$578, -164(%rbp)
	movl	$631, -160(%rbp)
	movl	$684, -156(%rbp)
	movl	$736, -152(%rbp)
	movl	$789, -148(%rbp)
	movl	$842, -144(%rbp)
	movl	$894, -140(%rbp)
	movl	$947, -136(%rbp)
	movl	-92(%rbp), %eax
	movl	%eax, -288(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -284(%rbp)
	movl	-80(%rbp), %eax
	movl	%eax, -280(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -276(%rbp)
	movl	-100(%rbp), %eax
	movl	%eax, -272(%rbp)
	movl	-44(%rbp), %eax
	movl	%eax, -268(%rbp)
	movl	-108(%rbp), %eax
	movl	%eax, -264(%rbp)
	movl	-52(%rbp), %eax
	movl	%eax, -260(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -256(%rbp)
	movl	-56(%rbp), %eax
	movl	%eax, -252(%rbp)
	movl	-116(%rbp), %eax
	movl	%eax, -248(%rbp)
	movl	-76(%rbp), %eax
	movl	%eax, -244(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -240(%rbp)
	movl	-68(%rbp), %eax
	movl	%eax, -236(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -232(%rbp)
	movl	-84(%rbp), %eax
	movl	%eax, -228(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -224(%rbp)
	movl	-88(%rbp), %eax
	movl	%eax, -220(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -216(%rbp)
	movl	-292(%rbp), %eax
	movl	%eax, %edi
	call	returnYearDiv19
	movl	%eax, -120(%rbp)
	movl	-120(%rbp), %eax
	movl	%eax, -124(%rbp)
	movl	-124(%rbp), %edx
	leaq	-208(%rbp), %rax
	movl	$19, %esi
	movq	%rax, %rdi
	call	findIndex
	movl	%eax, -128(%rbp)
	movl	-128(%rbp), %eax
	cltq
	movl	-288(%rbp,%rax,4), %eax
	movl	%eax, -132(%rbp)
	movl	-132(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	returnTableAB, .-returnTableAB
	.globl	returnYearDiv19
	.type	returnYearDiv19, @function
returnYearDiv19:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -36(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2sd	-36(%rbp), %xmm0
	movsd	.LC37(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, -12(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2sd	-12(%rbp), %xmm0
	movsd	-8(%rbp), %xmm1
	subsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-24(%rbp), %xmm1
	movsd	.LC38(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	returnYearDiv19, .-returnYearDiv19
	.globl	returnTableD
	.type	returnTableD, @function
returnTableD:
.LFB16:
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
	ja	.L57
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L59(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L59(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L59:
	.long	.L58-.L59
	.long	.L60-.L59
	.long	.L61-.L59
	.long	.L62-.L59
	.long	.L63-.L59
	.long	.L64-.L59
	.long	.L60-.L59
	.long	.L65-.L59
	.long	.L61-.L59
	.long	.L62-.L59
	.long	.L64-.L59
	.long	.L58-.L59
	.long	.L57-.L59
	.long	.L65-.L59
	.long	.L57-.L59
	.long	.L63-.L59
	.text
.L64:
	movl	$0, -4(%rbp)
	jmp	.L57
.L58:
	movl	$1, -4(%rbp)
	jmp	.L57
.L60:
	movl	$2, -4(%rbp)
	jmp	.L57
.L65:
	movl	$3, -4(%rbp)
	jmp	.L57
.L61:
	movl	$4, -4(%rbp)
	jmp	.L57
.L62:
	movl	$5, -4(%rbp)
	jmp	.L57
.L63:
	movl	$6, -4(%rbp)
	nop
.L57:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	returnTableD, .-returnTableD
	.globl	returnTableE
	.type	returnTableE, @function
returnTableE:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	cmpl	$18, -20(%rbp)
	ja	.L68
	movl	-20(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L70(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L70(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L70:
	.long	.L69-.L70
	.long	.L71-.L70
	.long	.L72-.L70
	.long	.L73-.L70
	.long	.L74-.L70
	.long	.L75-.L70
	.long	.L76-.L70
	.long	.L69-.L70
	.long	.L71-.L70
	.long	.L72-.L70
	.long	.L73-.L70
	.long	.L74-.L70
	.long	.L75-.L70
	.long	.L76-.L70
	.long	.L69-.L70
	.long	.L71-.L70
	.long	.L72-.L70
	.long	.L73-.L70
	.long	.L74-.L70
	.text
.L69:
	movl	$7, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L68
.L71:
	movl	$6, -4(%rbp)
	movl	$1, -8(%rbp)
	jmp	.L68
.L72:
	movl	$5, -4(%rbp)
	movl	$2, -8(%rbp)
	jmp	.L68
.L73:
	movl	$4, -4(%rbp)
	movl	$3, -8(%rbp)
	jmp	.L68
.L74:
	movl	$3, -4(%rbp)
	movl	$4, -8(%rbp)
	jmp	.L68
.L75:
	movl	$2, -4(%rbp)
	movl	$5, -8(%rbp)
	jmp	.L68
.L76:
	movl	$1, -4(%rbp)
	movl	$6, -8(%rbp)
	nop
.L68:
	movl	-4(%rbp), %eax
	movl	%eax, returnArray.4092(%rip)
	movl	-8(%rbp), %eax
	movl	%eax, 4+returnArray.4092(%rip)
	leaq	returnArray.4092(%rip), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	returnTableE, .-returnTableE
	.globl	findIndex
	.type	findIndex, @function
findIndex:
.LFB18:
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
	jmp	.L79
.L82:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	-32(%rbp), %eax
	jne	.L80
	movl	-4(%rbp), %eax
	jmp	.L81
.L80:
	addl	$1, -4(%rbp)
.L79:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L82
	movl	$-1, %eax
.L81:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	findIndex, .-findIndex
	.section	.rodata
.LC39:
	.string	"Sunday"
.LC40:
	.string	"Monday"
.LC41:
	.string	"Tuesday"
.LC42:
	.string	"Wednesday"
.LC43:
	.string	"Thursday"
.LC44:
	.string	"Friday"
.LC45:
	.string	"Saturday"
.LC46:
	.string	"April"
	.text
	.globl	pfm_algorithm
	.type	pfm_algorithm, @function
pfm_algorithm:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$192, %rsp
	movq	%rdi, -184(%rbp)
	movl	%esi, -188(%rbp)
	leaq	.LC39(%rip), %rax
	movq	%rax, -176(%rbp)
	leaq	.LC40(%rip), %rax
	movq	%rax, -168(%rbp)
	leaq	.LC41(%rip), %rax
	movq	%rax, -160(%rbp)
	leaq	.LC42(%rip), %rax
	movq	%rax, -152(%rbp)
	leaq	.LC43(%rip), %rax
	movq	%rax, -144(%rbp)
	leaq	.LC44(%rip), %rax
	movq	%rax, -136(%rbp)
	leaq	.LC45(%rip), %rax
	movq	%rax, -128(%rbp)
	movl	-188(%rbp), %eax
	movl	%eax, %edi
	call	returnTableAB
	movl	%eax, -12(%rbp)
	movl	-188(%rbp), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	imull	$-100, %eax, %edx
	movl	-188(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -20(%rbp)
	movl	$0, -24(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	returnTableD
	movl	%eax, -28(%rbp)
	movl	-12(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	returnTableE
	movq	%rax, -40(%rbp)
	movl	$1, -44(%rbp)
	movl	-44(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -48(%rbp)
	movl	-188(%rbp), %eax
	movl	%eax, %edi
	call	returnTableA
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -57(%rbp)
	cmpb	$77, -57(%rbp)
	jne	.L84
	leaq	.LC25(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L85
.L84:
	leaq	.LC46(%rip), %rax
	movq	%rax, -8(%rbp)
.L85:
	movq	-56(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -76(%rbp)
	movl	-48(%rbp), %eax
	cltq
	movq	-176(%rbp,%rax,8), %rax
	movq	%rax, -112(%rbp)
	movl	-76(%rbp), %eax
	movl	%eax, -96(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -104(%rbp)
	movl	-188(%rbp), %eax
	movl	%eax, -92(%rbp)
	movq	-184(%rbp), %rax
	movq	-112(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-104(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-96(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-184(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	pfm_algorithm, .-pfm_algorithm
	.globl	gauss_Easter_algorithm
	.type	gauss_Easter_algorithm, @function
gauss_Easter_algorithm:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movq	%rdi, -120(%rbp)
	movl	%esi, -124(%rbp)
	movl	-124(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %ecx
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
	movl	%eax, -24(%rbp)
	movl	-20(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -28(%rbp)
	movl	-20(%rbp), %ecx
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
	movl	%eax, -32(%rbp)
	movl	-20(%rbp), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
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
	pxor	%xmm0, %xmm0
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -136(%rbp)
	movsd	-136(%rbp), %xmm0
	call	floor@PLT
	cvttsd2si	%xmm0, %eax
	movl	%eax, -52(%rbp)
	movl	-36(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	pxor	%xmm0, %xmm0
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -136(%rbp)
	movsd	-136(%rbp), %xmm0
	call	floor@PLT
	cvttsd2si	%xmm0, %eax
	movl	%eax, -68(%rbp)
	movl	$15, %eax
	subl	-52(%rbp), %eax
	movl	%eax, %edx
	movl	-36(%rbp), %eax
	addl	%edx, %eax
	subl	-68(%rbp), %eax
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
	movl	-36(%rbp), %eax
	addl	$4, %eax
	subl	-68(%rbp), %eax
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
	movl	%eax, -76(%rbp)
	movl	-76(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -76(%rbp)
	movl	-24(%rbp), %edx
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
	movl	%eax, -80(%rbp)
	movl	-80(%rbp), %eax
	imull	$30, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -80(%rbp)
	movl	-32(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-28(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-80(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	%ecx, %eax
	leal	(%rax,%rax), %edx
	movl	-76(%rbp), %eax
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
	movl	%eax, -84(%rbp)
	movl	-84(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -84(%rbp)
	cmpl	$6, -84(%rbp)
	jne	.L88
	cmpl	$29, -80(%rbp)
	jne	.L89
	movl	$19, -4(%rbp)
	jmp	.L88
.L89:
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
	jg	.L88
	movl	$18, -4(%rbp)
.L88:
	movl	-80(%rbp), %eax
	leal	22(%rax), %edx
	movl	-84(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	cmpl	$31, -4(%rbp)
	jle	.L90
	leaq	.LC46(%rip), %rax
	movq	%rax, -16(%rbp)
	subl	$31, -4(%rbp)
	jmp	.L91
.L90:
	leaq	.LC25(%rip), %rax
	movq	%rax, -16(%rbp)
.L91:
	leaq	.LC39(%rip), %rax
	movq	%rax, -112(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -96(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -104(%rbp)
	movl	-124(%rbp), %eax
	movl	%eax, -92(%rbp)
	movq	-120(%rbp), %rax
	movq	-112(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-104(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-96(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-120(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	gauss_Easter_algorithm, .-gauss_Easter_algorithm
	.globl	anonymous_Gregorian_algorithm
	.type	anonymous_Gregorian_algorithm, @function
anonymous_Gregorian_algorithm:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -104(%rbp)
	movl	%esi, -108(%rbp)
	movl	-108(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %ecx
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
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %ecx
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
	movl	%eax, -24(%rbp)
	movl	-20(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -28(%rbp)
	movl	-20(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -32(%rbp)
	movl	-20(%rbp), %eax
	leal	8(%rax), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$3, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -36(%rbp)
	movl	-20(%rbp), %eax
	subl	-36(%rbp), %eax
	leal	1(%rax), %ecx
	movl	$1431655766, %edx
	movl	%ecx, %eax
	imull	%edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -40(%rbp)
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	subl	-28(%rbp), %eax
	subl	-40(%rbp), %eax
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
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	imull	$30, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -44(%rbp)
	movl	-24(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -48(%rbp)
	movl	-24(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -52(%rbp)
	movl	-32(%rbp), %eax
	leal	16(%rax), %edx
	movl	-48(%rbp), %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	-44(%rbp), %eax
	subl	-52(%rbp), %eax
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
	movl	-44(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%eax, %edx
	movl	-16(%rbp), %eax
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
	movl	%eax, -60(%rbp)
	movl	-44(%rbp), %edx
	movl	-56(%rbp), %eax
	addl	%eax, %edx
	movl	-60(%rbp), %eax
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
	movl	%eax, -64(%rbp)
	movl	-44(%rbp), %edx
	movl	-56(%rbp), %eax
	addl	%eax, %edx
	movl	-60(%rbp), %eax
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
	movl	%eax, -68(%rbp)
	cmpl	$3, -64(%rbp)
	jne	.L94
	leaq	.LC25(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L95
.L94:
	leaq	.LC46(%rip), %rax
	movq	%rax, -8(%rbp)
.L95:
	leaq	.LC39(%rip), %rax
	movq	%rax, -96(%rbp)
	movl	-68(%rbp), %eax
	movl	%eax, -80(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -88(%rbp)
	movl	-108(%rbp), %eax
	movl	%eax, -76(%rbp)
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-88(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-80(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-104(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	anonymous_Gregorian_algorithm, .-anonymous_Gregorian_algorithm
	.section	.rodata
.LC47:
	.string	""
	.text
	.globl	meeus_Julian_algorithm
	.type	meeus_Julian_algorithm, @function
meeus_Julian_algorithm:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -72(%rbp)
	movl	%esi, -76(%rbp)
	movl	-76(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %ecx
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
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %ecx
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
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %edx
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
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	imull	$30, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -28(%rbp)
	movl	-20(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-16(%rbp), %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	-28(%rbp), %eax
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
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -32(%rbp)
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
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
	movl	%eax, -36(%rbp)
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
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
	movl	%eax, -40(%rbp)
	cmpl	$3, -36(%rbp)
	jne	.L98
	leaq	.LC25(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L99
.L98:
	leaq	.LC46(%rip), %rax
	movq	%rax, -8(%rbp)
.L99:
	leaq	.LC47(%rip), %rax
	movq	%rax, -64(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -48(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -56(%rbp)
	movl	-76(%rbp), %eax
	movl	%eax, -44(%rbp)
	movq	-72(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-56(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-48(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-72(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	meeus_Julian_algorithm, .-meeus_Julian_algorithm
	.section	.rodata
	.align 8
.LC48:
	.string	"----------------------------------------\nEaster %d Dates:\n----------------------------------------\n"
	.align 8
.LC49:
	.string	"\nGauss Output:\n\t%s %d, %s %d -- Gregorian Calendar, mixed var array\n"
	.align 8
.LC50:
	.string	"\nAnonymous Output:\n\t%s %d, %s %d -- Gregorian Calendar, mixed var array\n"
	.align 8
.LC51:
	.string	"\nMeeus Output:\n\t%s %d, %s %d -- Julian Calendar, mixed var array\n"
	.align 8
.LC52:
	.string	"\nPaschal Full Moon (PFM) Output:\n\t%s %d, %s %d -- Gregorian Calendar, mixed var array\n\n"
	.align 8
.LC53:
	.string	"PFM output as a single char array value:\n\tString array: %s\n"
	.align 8
.LC54:
	.string	"\n------------------------\nThis following 'last line' line will be used as a string to input into Bash for any further POSIX formatted date calculations."
.LC55:
	.string	"\n%s"
	.text
	.globl	verboseDisplay
	.type	verboseDisplay, @function
verboseDisplay:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -36(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC48(%rip), %rdi
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
	leaq	.LC49(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-80(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	anonymous_Gregorian_algorithm
	movq	-80(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -24(%rbp)
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
	leaq	-80(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	meeus_Julian_algorithm
	movq	-80(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC51(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-80(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	pfm_algorithm
	movq	-80(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC52(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	subq	$8, %rsp
	pushq	-16(%rbp)
	pushq	-24(%rbp)
	pushq	-32(%rbp)
	call	outputDate2OutputString
	addq	$32, %rsp
	movq	%rax, outputString.4212(%rip)
	movq	outputString.4212(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC53(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	outputString.4212(%rip), %rax
	movq	%rax, %rdi
	call	dispDemoArray
	leaq	.LC54(%rip), %rdi
	call	puts@PLT
	movq	outputString.4212(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC55(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	verboseDisplay, .-verboseDisplay
	.section	.rodata
.LC56:
	.string	"%s"
	.text
	.globl	simpleDisplay
	.type	simpleDisplay, @function
simpleDisplay:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
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
	movq	%rax, outputString.4217(%rip)
	movq	outputString.4217(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC56(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	simpleDisplay, .-simpleDisplay
	.section	.rodata
	.align 8
.LC58:
	.string	"\nThe next Paschal Full Moon:\n\tThis year\n\tIn %f days\n\tOn %s %d %s %d"
	.text
	.globl	daysUntillPFM
	.type	daysUntillPFM, @function
daysUntillPFM:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$256, %rsp
	movl	%edi, -164(%rbp)
	leaq	-144(%rbp), %rax
	movl	-164(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	pfm_algorithm
	movl	-124(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-128(%rbp), %eax
	movl	%eax, -12(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	leaq	.LC25(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	je	.L104
	movl	$3, -4(%rbp)
	jmp	.L105
.L104:
	movl	$4, -4(%rbp)
.L105:
	leaq	-240(%rbp), %rax
	movl	-12(%rbp), %ecx
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %esi
	movq	%rax, %rdi
	call	defineTMstruct
	movq	-240(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-224(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -64(%rbp)
	leaq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	time@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	mktime@PLT
	movl	%eax, -32(%rbp)
	movq	-152(%rbp), %rdx
	movl	-32(%rbp), %eax
	cltq
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	difftime@PLT
	movq	%xmm0, %rax
	movq	%rax, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	movsd	.LC57(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -48(%rbp)
	movl	-124(%rbp), %edi
	movq	-136(%rbp), %rcx
	movl	-128(%rbp), %edx
	movq	-144(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	%edi, %r8d
	movq	%rax, -248(%rbp)
	movsd	-248(%rbp), %xmm0
	leaq	.LC58(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movsd	-48(%rbp), %xmm0
	cvttsd2si	%xmm0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	daysUntillPFM, .-daysUntillPFM
	.section	.rodata
	.align 8
.LC59:
	.string	"\nThe next Paschal Ful Moon:\n\t NEXT year \n\tOn %s %d %s %d"
	.text
	.globl	nextPFM
	.type	nextPFM, @function
nextPFM:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$2019, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	daysUntillPFM
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jns	.L109
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
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
	leaq	.LC59(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L109:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	nextPFM, .-nextPFM
	.section	.rodata
.LC60:
	.string	"-v"
	.text
	.type	inspectMainInputs, @function
inspectMainInputs:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$1, -20(%rbp)
	jne	.L111
	movl	$1, isGoodInput.4247(%rip)
	jmp	.L112
.L111:
	cmpl	$1, -20(%rbp)
	jle	.L113
	cmpl	$3, -20(%rbp)
	jg	.L113
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	noOfChars
	movl	%eax, inputLength.4244(%rip)
	leaq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$10, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strtol@PLT
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L114
	movl	inputLength.4244(%rip), %eax
	cmpl	$4, %eax
	jne	.L114
	movl	$1, isNumber.4245(%rip)
.L114:
	movl	isNumber.4245(%rip), %eax
	testl	%eax, %eax
	jne	.L115
	cmpl	$2, -20(%rbp)
	jle	.L115
	movq	-8(%rbp), %rax
	leaq	.LC60(%rip), %rsi
	movq	%rax, %rdi
	call	compareStrings
	movl	%eax, isVerbose.4246(%rip)
	movl	isVerbose.4246(%rip), %eax
	testl	%eax, %eax
	je	.L115
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	noOfChars
	movl	%eax, inputLength.4244(%rip)
	leaq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$10, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strtol@PLT
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L115
	movl	inputLength.4244(%rip), %eax
	cmpl	$4, %eax
	jne	.L115
	movl	$1, isNumber.4245(%rip)
.L115:
	movl	isNumber.4245(%rip), %eax
	testl	%eax, %eax
	jne	.L116
	movl	$0, isGoodInput.4247(%rip)
	jmp	.L112
.L116:
	movl	$1, isGoodInput.4247(%rip)
	jmp	.L112
.L113:
	movl	$0, isGoodInput.4247(%rip)
.L112:
	movl	isGoodInput.4247(%rip), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	inspectMainInputs, .-inspectMainInputs
	.section	.rodata
	.align 8
.LC61:
	.string	"------------------------\nBasic PMF Output Render:\n------------------------"
	.align 8
.LC62:
	.string	"\n\n\nVerbose PMF and Easter Output Render:"
	.align 8
.LC63:
	.string	"\n!!! Execution interupted !!!\nProvide valid inputs and try again :)\n\nExample:\n\n  ./main\n or\n  ./main 1985\n or\n  ./main -v 1985\n\n0000000"
	.text
	.globl	main
	.type	main, @function
main:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rdx
	movl	-20(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	inspectMainInputs
	movl	%eax, isInputValid.4252(%rip)
	movl	isInputValid.4252(%rip), %eax
	testl	%eax, %eax
	je	.L120
	movl	-20(%rbp), %eax
	cmpl	$2, %eax
	je	.L122
	cmpl	$3, %eax
	je	.L123
	cmpl	$1, %eax
	jne	.L121
	movl	$0, %eax
	call	returnYear
	movl	%eax, yearInt.4253(%rip)
	movl	yearInt.4253(%rip), %eax
	movl	%eax, %edi
	call	simpleDisplay
	jmp	.L121
.L122:
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, yearInt.4253(%rip)
	movl	yearInt.4253(%rip), %eax
	movl	%eax, %edi
	call	simpleDisplay
	jmp	.L121
.L123:
	leaq	.LC61(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	nextPFM
	leaq	.LC62(%rip), %rdi
	call	puts@PLT
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, yearInt.4253(%rip)
	movl	yearInt.4253(%rip), %eax
	movl	%eax, %edi
	call	verboseDisplay
	nop
.L121:
	movl	$10, %edi
	call	putchar@PLT
	movl	$0, %eax
	jmp	.L126
.L120:
	leaq	.LC63(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %edi
	call	exit@PLT
.L126:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	main, .-main
	.local	str1Len.3943
	.comm	str1Len.3943,4,4
	.local	str2Len.3944
	.comm	str2Len.3944,4,4
	.local	combinedLen.3945
	.comm	combinedLen.3945,4,4
	.local	outputString.3940
	.comm	outputString.3940,8,8
	.local	count2.3942
	.comm	count2.3942,4,4
	.local	count1.3941
	.comm	count1.3941,4,4
	.local	returnArray.4092
	.comm	returnArray.4092,8,8
	.local	outputString.4212
	.comm	outputString.4212,8,8
	.local	outputString.4217
	.comm	outputString.4217,8,8
	.local	isGoodInput.4247
	.comm	isGoodInput.4247,4,4
	.local	inputLength.4244
	.comm	inputLength.4244,4,4
	.local	isNumber.4245
	.comm	isNumber.4245,4,4
	.local	isVerbose.4246
	.comm	isVerbose.4246,4,4
	.local	isInputValid.4252
	.comm	isInputValid.4252,4,4
	.local	yearInt.4253
	.comm	yearInt.4253,4,4
	.section	.rodata
	.align 8
.LC22:
	.long	0
	.long	1072693248
	.align 8
.LC37:
	.long	0
	.long	1077084160
	.align 8
.LC38:
	.long	0
	.long	1083129856
	.align 8
.LC57:
	.long	0
	.long	1089804288
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
