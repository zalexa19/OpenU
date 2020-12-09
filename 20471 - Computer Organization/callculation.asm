.data
	number1: .word 5
	number2: .word 10

.text
	# subtracting
	lw $s0, number2				# s0 = 10
	lw $s1, number1 			# s1 = 5

	sub $t0, $s0, $s1			# t0 = 10 - 5
	
	# print with a pseudo
	li $v0, 1
	move $a0, $t0				# pseudo to move the value from t0 to a0
	syscall

	# adding two integers and printing
	lw $t0, number1($zero)			# load the number into the register in the processor
	lw $t1, number2($zero)
	add $t2, $t1, $t0
	
	# print the result 
	li $v0, 1				# print integer code
	add $a0, $t2, $zero			# move the value to a0
	syscall
	
	
	