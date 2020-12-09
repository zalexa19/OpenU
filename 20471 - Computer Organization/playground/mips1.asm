.data 
	message: .asciiz "Hello Assembly \n"
	character: .byte 'm'
	age: .word 23			# this is declaring intigers (a word is 4 bytes)
	double: .double 7.202		# 
	zeroDouble: .double 0.0 
	
.text
	# print a double
	ldc1 $f2, double
	ldc1 $f0, zeroDouble
	
	
	# print integer
	li $v0, 1
	lw $a0, age
	syscall 
	
	
	# la $a0, message 		# loads into reserved reg 
	# li $v0, 4			# for syscall
	# syscall			# prints the ascii text value in this case
	
	#print character
	la $a0, character 		# loads into reserved reg 
	li $v0, 11			# for syscall
	syscall				# prints the ascii text value in this case
	