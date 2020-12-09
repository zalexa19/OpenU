# Ask the user for a number
# verify that the number is in the following range: -9999 < n < 9999
# if not, display and error and prompt for a number again
# if number if valid, print every bit by isolating it and checking the value, starting with the left most bit
# to reverse it, init s1 with 0 and isolate the rightmost bit. shift the result 1 bit to the left and perform OR with the isolated bit. shift the mask 1 bit to the left as well.
# eventually, check the left most bit of the result. if it's 1 print a minus. then, print the number using syscall

# Registers being use:
# $s0 = stores user's input and afterwards the reversed number
# $s1 stores the result while changing the order of the bits
# $t0 used for looping
# $t1 used for calculation inside the loop
# $t2 holds the masking value, which allows to isolate bits
# $t3 temporarily stores an isolated bit that is being examined
# $a0 holds the values which syscall is going to print

.data
	promptMessage: .asciiz "Please enter a number:\n"
	invalidNumberError: .asciiz "Entered number is invalid\n"
	newLine: .asciiz "\n"
	minus: .asciiz "-"	
.text 
main:
	# Q1 Ask user for a number
	# promp the user for a number
	la $a0, promptMessage
	jal printString
	
	# read the number and store it in s0
	li $v0, 5
	syscall 
	
	move $s0, $v0
	
	# check if the number is valid. if the number is invalid, ask for input again
	 blt $s0, -9999, startAgain			# if t0 < -9999
	 bgt $s0, 9999, startAgain			# if t0 > 9999
	
	
	# Q2: Prints every bit. more in detail documentation follows
	jal printInBinary
	la $a0, newLine
	jal printString
	
	# Q3: changes the order of the bits by using the AND operation, and shifting bits.0
	li $t2, 1					# t2 = 1. This is our mask and the loop exist condition
	li $s1, 0					# initialize s1 = 0
flippingLoop:
	beq $t2, 65536, exitFlippingLoop		# if t2 = 65536, it means that the masking char is in bit 17 and therefore we can stop looping
	and $t3, $s0, $t2 				# isolate the bit which is under inspection
	sll $s1, $s1, 1					# s1 is the result -> shift 1 bit to the left before doing OR
	
	beq $t3, $t2, bitIsOne				# if t3 = t2 it means that the isolated bit = 1. otherwise, add 0 as the rightmost bit
	ori $s1, $s1, 0					# performing 'OR' will add the newly isolated bit to the result while keeping the previously calculated bits
	j shiftMaskBit					

bitIsOne:
	ori $s1, $s1, 1					# add 1 to as rightmost bit
	
shiftMaskBit:
	sll $t2, $t2, 1
	j flippingLoop

exitFlippingLoop:
	move $s0, $s1					# move s1 to s0 because printInBinary reads from s0
	jal printInBinary
	
	# Q4 print using syscall 1
	li $t2, 32768					
	and $t3, $s1, $t2 				# get the leftmost bit
	beq $t3, $t2 printMinus				# if the leftmost bit is 1, this is a negative number
	j printDecimalNumber
printMinus:	
	la $a0, minus
	jal printString
printDecimalNumber: 
	move $a0, $s1
	jal printInt
	
	# exit the program
	jal exit
	
	
startAgain: 						# prints an error and runs main again
	la $a0, invalidNumberError
	jal printString
	jal main
		

printInBinary:
	# This algorith checks every bit and prints 1 or 0 accordingly
	# The leftmost bit is being checked first. if the result of inputNumber AND mask = mask number - the bit in that location is 1
	# otherwise the bit is 0.
	# after isolating the bit, print it, shift the masked bit to the right once and do the same again
	# save return address in the stack so it's possible to go back
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
			
	li $t0, 1					# t0 = 1	
	sll $t0, $t0, 15				# t0 acts as the mask for bitwise and as the loop exit condition. starting with the leftmost bit	
loop:
	beq $t0, 0, exitLoop				# if t0 = 0, it means we checked all of the bits and can exit the loop
	and $t1, $s0, $t0 				# isolate the bit according to what is in $t0
	
	beq $t1, $t0, setBit				# if the result equals our masking value, it means that the bit = 1, 
	li $a0, 0 		
	j print
		
setBit:
	li $a0, 1
	
print:
	li $v0, 1
	syscall

	srl $t0, $t0, 1					# shift the mask 1 bit to the right
	j loop
	
exitLoop:
	la $a0, newLine
	jal printString
		
	# recover ther return address
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra   
				
				
# helper functions
printString:
	li $v0, 4
	syscall
	jr $ra # go back to the address from where this function was called 
	
printInt:
	li $v0, 1
	syscall
	jr $ra  
 

exit:
	li $v0, 10
	syscall
	
