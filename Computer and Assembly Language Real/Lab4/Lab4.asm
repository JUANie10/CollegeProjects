
##########################################################################
# Created by:  Lee, Juan
#              Jlee543
#              25 May 2019
#
# Assignment:  Lab 4: Roman Numeral Conversion 
#              CMPE 012, Computer Systems and Assembly Language
#              UC Santa Cruz, Spring 2019
# 
# Description: This program converts an inputed Roman Numeral input to Binary.
# 
# Notes:       This program is intended to be run from the MARS IDE.
#
#Register Usage:
#		$v0 is used for syscall
#		$a0 is used for loading address of arrays or strings
#		$t0 stores the current value
#		$t1 stores the address of the program agrument
#		$t2 stores the next value 
#		$t3 sotre the next next value
#		$t4 stores a bte of the hex values of the binary 
#		$t5 stores the remainder of the division 
#		$t6 stores the value of the loaded byte of the bianry
#		$t7 stores the hex values of binary
#		$s0 storees the decimal value of the roman numeral 
#		hi stores the remainder of the division
##########################################################################
#       This program converts an inputed Roman Numeral to Binary
# .data
#	bin is a space of 30 to input the binary value from the modulo operation
#	uenter is the string where I am going to put my statement asking for a Roman Numeral input
#	Error is the string where I put my errror message
#	binrep is the string before the binary is printed
#.text
# 	Prints out the uenter string
#
#	Adds a space
#
#	Loads the $a0 with the inputed string of Roman Numerals 
#	
#	Prints out the inputed string
#
#	Checks if the Roman Numeral is Valid by checking the current and the next input 
#	
#	Converts the Roman Numeral to Decimal by checking what hex values are loaded
#	
#	Prints out the binary string, binrep
#	
#	Converts the Decimal to Binary by using modulos
#
#	Prints the Binary
#
#	End program
##########################################################################

.data						
	bin: .space 30
	uenter: .asciiz "You entered the Roman numerals:"
	error: .asciiz "\nError: Invalid program argument."
	binrep: .asciiz "\nThe binary representation is:"
   
.text
	li $v0, 4			#Prints out the initial prompt
	la $a0, uenter
	syscall
	
	li $v0, 11			#adds a space
	la $a0, '\n'
	syscall
	
	
	lw $a0 ($a1)			#Prints the program agrument
	li $v0, 4
	syscall
	
	lw $t1, ($a1)			#Loads the program agrument into a $t1 register from the address of $a1
	
	
	store1: 
		lb $t0, ($t1)		#loads a byte from $t1 register
		addi $t1, $t1, 1
		lb $t2, ($t1)		#Loads the next byte into $t2 register
		
		
		j checker
	
			
	
	checker:
		

		beq $t0, 0x49, valid1	#Checks which hex value the current byte holds
		
		beq $t0, 0x56, valid2
		
		beq $t0, 0x58, valid3
	
		beq $t0, 0x4C, valid4
		
		beq $t0, 0x43, valid5
		
		j invalid
		
		
	invalid:
		li $v0, 11		#adds a space
		la $a0, '\n'
		syscall
		
		li $v0, 4		#prints out the error messagee
		la $a0, error
		syscall
		j end
		
		
	valid1: 
		beq $t2, 0x4C, invalid	#Checks the validity for roman numeral "I"
		beq $t2, 0x43, invalid
		beq $t2, 0x56, case1
		beq $t2, 0x58, case1
	back:	
		beq $t2, 0x58, sub1 	#either sends to subtract or add depending on the next byte
		beq $t2, 0x56, sub1
		beq $t2, 0x49, add1
		beq $t2, 0x00, add1
	case1:
		subi $t1, $t1, 2	
		lb $t3, ($t1)		#loads the next next byte
		beq $t3, 0x49, invalid	#checks for another case
		addi $t1, $t1, 2
		j back
	add1:	
		addi $s0, $s0, 1	#add 1 to the integer register #s0
		j next
	sub1: 
		subi $s0, $s0, 1	#subtracts 1 to the integer register #s0
		j next
		
		
	valid2:
		beq $t2, 0x58, invalid	#checks for valid cases invovling the roman numeral "V"
		beq $t2, 0x4C, invalid
		beq $t2, 0x43, invalid
		beq $t0, $t2, invalid
		bge $t0, $t2, add2 
		blt $t0, $t2, sub2
	add2:	
		addi $s0, $s0, 5	#add 5 to the integer register #s0
		j next
	sub2:
		subi $s0, $s0, 5	#subtracts 5 to the integer register #s0
		j next
	valid3:
		beq $t2, 0x49, add3	#checks for valid cases invovling the roman numeral "X"
		beq $t2, 0x56, add3
		beq $t2, 0x58, add3 
		beq $t2, 0x4C, sub3
		beq $t2, 0x43, sub3
	add3:	
		addi $s0, $s0, 10	#add 10 to the integer register #s0
		j next
	sub3: 
		subi $s0, $s0, 10	#subtracts 10 to the integer register #s0
		j next
	valid4:
		beq $t2, 0x43, invalid	#checks for valid cases invovling the roman numeral "L"
		beq $t0, $t2, invalid
		beq $t2, 0x58 add4 
		beq $t2, 0x56 add4 
		beq $t2, 0x49 add4 
		blt $t0, $t2, sub4
	add4:	
		addi $s0, $s0, 50	#add 50 to the integer register #s0
		j next
	sub4: 
		subi $s0, $s0, 50	#subtracts 50 to the integer register #s0
		j next
	valid5:
		
		beq $t2, 0x49 add5	#checks for valid cases invovling the roman numeral "C"
		beq $t2, 0x56 add5 
		beq $t2, 0x58 add5 
		beq $t2, 0x4C add5 
		beq $t2, 0x43 add5 
		
	add5:	
		addi $s0, $s0, 100	#add 100 to the integer register #s0
		j next
	
	next:
		beqz $t2, binary	#Checks for if the next value is null.
		j store1
		
	
	binary:
		li $v0, 11		#adds a space
		la $a0, '\n'
		syscall
		
		li $v0, 4		#Prints out the binary prompt
		la $a0, binrep
		syscall
		
		li $v0, 11		#adds a space
		la $a0, '\n'
		syscall
		
		li $v0, 11		#Prints out the character "0"
		la $a0, '0'
		syscall
		
		li $v0, 11		#Prints out the character "b"
		la $a0, 'b'
		syscall
		
	      	move $t3, $s0		#moves the stored integer value into the $t3 register
	      	
	      	la $a0, bin		#loads the address of bin into the $a0
	      	move $t7, $a0		#moves the contents of $a0 to $t7
	modulo:
		blt $t3, 2, store2	#if the value being divided in less than 2, go to store2
		divu $t3, $t3, 2	#Takes davision of $t3 register by two
		mfhi $t5		#Stores the remainder into the $t5 register
		addi $t4, $t5, 48	#adds 48 to $t5 reigster to get the asscii value of 1 or 0 and stores it into $t4 register
		sb $t4, ($t7)		#store it and changes the place
		addi $t7, $t7,1
		j modulo
		
	store2:
		addi $t3, $t3, 48	#converts the stored integer to asscii value 
		sb $t3, ($t7)		#stores it and goes to print
		j print
	print: 	
		
		lb $t6, ($t7)		#Loads a byte of the binary asscii value into $t6
		beqz $t6, end		#If #t6 is zero go to end
		subi $t7, $t7, 1	#increments $t7
		
		
		li $v0, 11		#Prints out the binary value
		move $a0, $t6
		syscall
		j print
	end:	
		li $v0, 11		#adds a space
		la $a0, '\n'
		syscall
	
		li $v0, 10		#End Program
		syscall
	
	
	
