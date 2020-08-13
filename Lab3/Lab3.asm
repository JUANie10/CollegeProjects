
##########################################################################
# Created by:  Lee, Juan
#              Jlee543
#              12 May 2019
#
# Assignment:  Lab 3: MIPS!
#              CMPE 012, Computer Systems and Assembly Language
#              UC Santa Cruz, Spring 2019
# 
# Description: This program prints the factorial of a inputed integer between 0 and 10 
# 
# Notes:       This program is intended to be run from the MARS IDE.
##########################################################################
.data
	prompt: .asciiz "Enter an integer between 0 and 10: "
	#This is the intial prompt that the user will recieve
	
	wrong: .asciiz "\nInvalid entry! \n\n"
	#In case the user inputs a invalid integer, they will recieve this message.
.text
	loop: 
	#getting the prompt to print
	li $v0, 4
	la $a0, prompt
	syscall
	
	#getting the user's input
	li $v0, 5
	syscall 
	
	#moving the user's input to register $t0 
	move $t0, $v0
	
	#Checkers if the inputed integer is betweeen 0 adn 10
	sge  $t1, $t0, $zero
	sle  $t2, $t0, 10
	and $t1, $t1, $t2
	beqz $t1, else
	
	#adds a space for spacing
	li $v0, 11
	la $a0, '\n'
	syscall
	
	#prints out the inputed integer
	li $v0, 1
	move $a0, $t0
	syscall 
	
	#prints out "! = " after the integer
	li $v0, 11
	la $a0, '!'
	syscall
	li $v0, 11
	la $a0, ' '
	syscall
	li $v0, 11
	la $a0, '='
	syscall 
	li $v0, 11
	la $a0, ' '
	syscall
	
	#skips the else part and brings it to pass
	j pass
	
	else: 
	#prints out the wrong statement if the integer is not between 0 and 10.
		li $v0, 4
		la $a0, wrong
		syscall
		
	#loops it back to the loop statement above.
		j loop
		
	pass:
	#sets the $t4 register to 1.
		li $t4, 1
	pass2:
	#checks if register $t0 is zero 
		beqz $t0, end_if
		
	#loops til the factorial calculation is complete
		mul $t4, $t0, $t4
		subi $t0, $t0, 1 
		b pass2
		
		
	end_if:
	#prints the answer of the factorial
		li $v0, 1
		move $a0, $t4
		syscall
		
	#prints out a space
		li $v0, 11
		la $a0, '\n'
		syscall
		
	#Closes the program.
		li $v0, 10
		syscall
		
		
	
		
		
		
		
