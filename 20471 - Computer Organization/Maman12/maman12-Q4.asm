


# Reggisters in use:
# $a0, $a1 used by char_occurrences to calculate char appearances
# $s1, $s2 are used by main to show the letter with the most occurrences
# $s6, $S5 holds the most frequest character with the number of occorences

################# Data segment #####################
.data
	CharStr: .asciiz  "AEZKLBXWZXYALKFKWZRYLAKWLQLEK"
	newLine: .asciiz  "\n"
	mostFrequentCharText: .asciiz  "\nThe most frequesnt character is: "
	numOfOccurencesText: .asciiz  " ,with number of occurences:  "
	messageToUser: .asciiz "\nWould you like to remove the next most frequent character? y / n \n"
	buffer:	.space 8
	ResultsArray: .space 26	
.globl main
################# Code segment #####################	
.text
main:
	# Question 1	
	la $a0, CharStr				# load string adress
startAgain:
	jal initResultsArray			# initialize with 0 in every cell
		
	la $a1, ResultsArray			# load results 
	#jal printString

	jal char_occurrences
	
	# Question 2: print
	move $s6, $v0 				# copy the char ascii to avoid override
	move $s5, $v1				# save the max number of occorences
	la $a0, mostFrequentCharText
	li $v0, 4
	syscall
	
	move $a0, $s6 		
	jal printChar
	
	la $a0, numOfOccurencesText
	li $v0, 4
	syscall
	
	move $a0, $v1
	jal printInt
	
	# Question 3 - print each char x occurences
	jal print_char_by_occurences
	la $a0, newLine
	li $v0, 4
	syscall
	
	# Question 4 - delete
	la $a0, CharStr
	move $a1, $s6				# ascii for the most frequent character
	jal delete
	li $v0, 4
	syscall	
	
	# Question 5 - user interaction
	lb $t0, 0($a0)				# t0 = a0[0]
	beqz, $t0, exit				# if string is empty, end the program
	
	move $s7, $a0				# store the string address
	la $a0, messageToUser
	jal printString
	
	# read user input
	la $a0, buffer
	li $a1, 8
	li $v0 8
	syscall
	
	lb $t0, buffer
	bne $t0, 'y', exit
	move $a0, $s7
	j startAgain
			
	# end the program
	j exit

# load the first str charater to a temp register
# do the char ascii - a ascii to get the index inside ResultsArray
# add 1 to the index in the results array
# advance the loop index
# end the loop, if the char == 0 
	
# To count  how many times each char exists, we loop over the string and each time we load 1 character.
# then, we calculate the index by the distance from the ascii value from the ascii value of A (65)
# to store the result:
# load the address of the ResultsArray to a temp registry
# advance the pointer by adding the index
# load the byte from the array, add 1 to the value and store it back
# $t0 - temp register for advancing the pointer on the srting
# $t1 - temp register that store a character from the string
# $t2 - temp register that stores the index of the letter
# $t3 - temp register that stores the address of ResultsArray
# $t4 - temp register that stores the value from ResultsArray
# $t5 - temp register that stores the maxValue
# $t6 - temp register that stores the maxValue's ascii
# $t7 - temp register that stores a comparison result
# $a0, $a0 = params that hold the string and the address of the result array
# v0 = used by syscall to know which value to print
	
char_occurrences:
	move $t0, $a0			# copy the str adrress to a temporary register
	li $t5, 0			# maxValue = 0
	li $t6, 'A'
loop:
	lb $t1, 0($t0)			# load the first byte of the string
	beqz $t1, endLoop		# check for the end of the string
	subi $t2, $t1, 65		# calculate the index in the result array
	
	# update the resultArray
	move $t3, $a1			# load the address of the ResultsArray to t3
	add $t3, $t3, $t2		# offset the address by the distance, to get to the correct index
	lb $t4, 0($t3)			# load the currently stored value
	addi $t4, $t4, 1		# advance by 1
	sb $t4, 0($t3)			# put it back
	
	# check if it's the the max value
	beq $t4, $t5, compareAscii	# if t4 = max
	slt $t7, $t4, $t5		# is t4 < t5 (max value)
	beq $t7, 1, continue		# t4 < max
	beq $t7, 0, setMax 		# t4 > max

setMax:
	move $t5, $t4
	move $t6, $t1			# store the new ascii
	j continue
			
compareAscii:
	slt $t7, $t1, $t6		# compare current byte to max byte
	beq $t7, 1, continue		# t1 < t6 current < max
	beq $t7, 0, setMaxAscii		# t1 > t6
	beq $t1, $t6, continue

setMaxAscii:
	move $t6, $t1
	j continue	
	
continue:		
	addi $t0, $t0, 1		# move pointer to the next byte in the string
	j loop
endLoop:
	move $v1, $t5			# return max value
	move $v0, $t6
	jr $ra 				# go back to the procedure that called it

# to print each letter, i keep track of the current index (by advancing the ResultsArray address) and current alphabet letter starting from A.
# First I get the number of occurences. if it's 0, I skip to the next letter by advancing the address and letter ascii 
# otherwise I print a new line, print the letter x times and decrease the counter accordingly
# Registers used:
# $s0 - keeps track of the letter to be printed. Initialised with A
# $s1 - holds a pointer to the address of the ResultsArray
# $t1 - holds the amount of times that the letter needs to be printed. also acts as a counter
# $a0 - param
# $v0 - used by syscall to know which value to print
 
 
print_char_by_occurences:	
	li $s0, 'A'			# load A
	move $s1, $a1			# load the Results array 

alphabetLoop:	
	bgt $s0, 122, endAlphabetLoop	# check if the whole abc was scanned - 122 is Z
	lb $t1, 0($s1)			# load number of occurences
	beqz $t1, endPrintingLoop	# if the number of occurences = 0, advance pointer to the next cell
	la $a0, newLine			# otherwisem print a new line
	li $v0, 4
	syscall	
printingLoop:
	beqz $t1, endPrintingLoop	# if the t1 = 0 zero, we finished printing the letter
	move $a0, $s0			# print the letter
	li $v0, 11
	syscall
	
	subi $t1, $t1, 1		# t1 --
	j printingLoop	
endPrintingLoop:
	addi $s1, $s1, 1		# advance the address pointer
	addi $s0, $s0, 1		# advance to the next char in the abc
	j alphabetLoop
endAlphabetLoop:
	jr $ra # go back to the procedure that called it

# Removes from the string each occurence of the character that was passed in $a1
# registers used:
# $a0 - CharStr address
# $a1 - Ascii
# $a2 - stores the address to the letter to be deleted
# $s0 - stores the original address of the string to be returned to main
# $t1 - stored that bit that is being examined

delete:
	addi $sp, $sp, -4		# save return address to the stack	
	sw $ra, 0($sp)	
	
	move $s0, $a0			# save the str address for later
			
deleteLoop:
	lb $t1, 0($a0)			# load the first byte of the string
	beqz $t1, endDeleteLoop		# t1 = 0 -> empty string
	beq $t1, $a1 deleteChar		# compare current bit to the max ascii 
	j endIf
deleteChar:
	jal reduction
endIf:
	addi $a0, $a0, 1		# advance address pointer
	j deleteLoop
endDeleteLoop:
	# recover ther return address
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $a0, $s0
	jr $ra  
	
# removes the first character from a given address and shifts all of the other character to the left.	
# registers used:
# $a0 - CharStr address
# $t4 - stores the original address to be restored when done deleting
# $t2 - stores the address of the next character in the string
# $t3 - stores the ascii of the next character in the string
reduction:
	move $t4, $a0			# save the pointer
			
reduce:
	add $t2, $a0, 1 		# next string location		
	lb $t3, 0($t2)			# load next bit
	
	beqz $t3, endReduce		# if there are no chars to shift left, return. 
	sb $t3, 0($a0)
	addi $a0, $a0, 1		# shift address 1 byte location to the right
	
	j reduce

endReduce:
	# copy the null value
	add $t2, $a0, 1 				
	lb $t3, 0($t2)			
	sb $t3, 0($a0)
	move $a0, $t4
	jr $ra				 # go back to the procedure that called it





################# Helpers #####################	
initResultsArray:
	la $t0, ResultsArray
	li $t1, 0			# i = 0
storeZero:
	bge $t1, 26, finish
	sb $zero, 0($t0)
	addi $t0, $t0, 1		# advance poiner
	addi $t1, $t1, 1		# i++
	j storeZero
finish:
	jr $ra # go back to the procedure that called it
	
printString:
	li $v0, 4
	syscall
	
	move $t0, $a0
	la $a0, newLine
	syscall
	move $a0, $t0	
	jr $ra # go back to the procedure that called it
	
printChar:
	li $v0, 11
	syscall
	jr $ra # go back to the procedure that called it
printInt:
	li $v0, 1
	syscall
	jr $ra # go back to the procedure that called it
	
exit:
	li $v0, 10
	syscall
