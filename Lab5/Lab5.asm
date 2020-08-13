#-------------------------------------------------------------------------
# Created by:  Lee, Juan
#              Jlee543
#              12th, June 2019
#
# Assignment:  Lab 5: A Gambling Game
#              CMPE 012, Computer Systems and Assembly Language
#              UC Santa Cruz, Spring 2019
# 
# Description: Interactive game where a random array will be given and depending on if the guess of max integer index, the user earns
#              points and loses points. If the max integer index is correctly guessed, the integer value gets replaced with -1. 
#              The user loses when their points hit zero. The user wins if every index contains -1. The players start with 100 points.
#
# Notes:       This program is intended to run in the MARS IDE
#-------------------------------------------------------------------------

jal end_game                       # this is to prevent the rest of
                                   # the code executing unexpectedly

#--------------------------------------------------------------------
# play_game
#
# This is the highest level subroutine.
#
# arguments:  $a0 - starting score
#             $a1 - address of array index 0 
#
# return:     n/a
#--------------------------------------------------------------------
#
# REGISTER USE
# $s0:      Storing the starting scrore 
# $s1:      Storing the address of array index 0 into resgister    
# $t0:      loading array values to check for array size
# $a0:      Storing current score and array size
# $a1:      Storing address of array index 0
# $a3:      Storing user selection from prompt_options
#--------------------------------------------------------------------

.text
play_game: nop
   
    subi   $sp, $sp, 4          #Storing the starting scrore and address of array index 0 into the stack
    move   $t0, $a0
    sw     $t0 ($sp)
    
    subi   $sp, $sp, 4
    move   $t0, $a1
    sw     $t0 ($sp)          
 
    li     $a0, 0               #setting $a0 register to 0 in order to store the array size
loop:
    lw     $t0,($a1)            #incrementing the array in order to find the array size in words that is stored in $a0
    addi   $a1, $a1, 4
    beqz   $t0, next 
    addi   $a0, $a0, 1
    jal    loop                 # use $a1 to get the number of elements in the array
next:
    subi   $a0, $a0, 1
    subi   $sp, $sp, 4
    sw     $a0 ($sp)
    addi   $a0, $a0, 1
    
    jal    welcome
    
comeback:
 
    jal    prompt_options           
    
    lw     $a1, 4($sp)              #storing $a0 - current score, $a1 - address of array index 0, $a2- array size, $a3 - user selection from prompt_options
    
    
    lw     $a0, 8($sp)
    
    
    move   $a3, $v0             
    
    jal    take_turn
    
    sw     $v0, 12($sp)            #Pushing the current score into the stack
    
    jal    comeback
    
    
    jr     $ra


#--------------------------------------------------------------------
# welcome (given)
#
# Prints welcome message indicating valid indices.
# Do not modify this subroutine.
#
# arguments:  $a0 - array size in words
#
# return:     n/a
#--------------------------------------------------------------------
#
# REGISTER USE
# $t0: array size
# $a0: syscalls
# $v0: syscalls
#--------------------------------------------------------------------


.data
welcome_msg: .ascii "------------------------------"
             .ascii "\nWELCOME"
             .ascii "\n------------------------------"
             .ascii "\n\nIn this game, you will guess the index of the maximum value in an array."
             .asciiz "\nValid indices for this array are 0 - "

end_of_msg:  .asciiz ".\n\n"
             
.text
welcome: nop

    add    $t0  $zero  $a0         # save address of array

    addiu  $v0  $zero  4           # print welcome message
    la     $a0  welcome_msg
    syscall
    
    addiu  $v0  $zero  1           # print max array index
    sub    $a0  $t0    1
    syscall

    addiu  $v0  $zero  4           # print period
    la     $a0  end_of_msg
    syscall
    
    jr     $ra
    
    
#--------------------------------------------------------------------
# prompt_options (given)
#
# Prints user options to screen.
# Do not modify this subroutine. No error handling is required.
# 
# return:     $v0 - user selection
#--------------------------------------------------------------------
#
# REGISTER USE
# $v0, $a0: syscalls
# $t0:      temporarily save user input
#--------------------------------------------------------------------

.data
turn_options: .ascii  "------------------------------" 
              .ascii  "\nWhat would you like to do? Select a number 1 - 3"
              .ascii  "\n"
              .ascii  "\n1 - Make a bet"
              .ascii  "\n2 - Cheat! Show me the array"
              .asciiz "\n3 - Quit before I lose everything\n\n"

.text
prompt_options: nop

    addiu  $v0  $zero  4           # print prompts
    la     $a0  turn_options       
    syscall

    addiu  $v0  $zero  5           # get user input
    syscall
    
    add    $t0  $zero  $v0         # temporarily saves user input to $t0
    
    addiu  $v0  $zero  11
    addiu  $a0  $zero  0xA         # print blank line
    syscall

    add    $v0  $zero  $t0         # return player selection
    jr     $ra


#--------------------------------------------------------------------
# take_turn	
#
# All actions taken in one turn are executed from take_turn.
#
# This subroutine calls one of following sub-routines based on the
# player's selection:
#
# 1. make_bet
# 2. print_array
# 3. end_game
#
# After the appropriate option is executed, this subroutine will also
# check for conditions that will lead to winning or losing the game
# with the nested subroutine win_or_lose.
# 
# arguments:  $a0 - current score
#             $a1 - address of array index 0 
#             $a2 - size of array (this argument is optional)
#             $a3 - user selection from prompt_options
#
# return:     $v0 - updated score
#--------------------------------------------------------------------
#
# REGISTER USE
# $t0:      Temporarily stores address of array index 0     
# $t1:      Hold the integer 0 if win condition has been met
# $a0:      loaded the address of the array index 0
# $a1:      Holds the staring score
# $a3:      Holds the user input 
# $s0:      Holds the current score
# $v0:      Holds the updated score
#--------------------------------------------------------------------

.text
take_turn: nop

    subi   $sp   $sp  4          # push return address to stack
    sw     $ra  ($sp)
    
    subi   $sp   $sp  4          # push address of array index 0 to stack
    move   $t0   $a1
    sw     $t0  ($sp)
    
other:
   
    bne    $a3, 1, other1        # Check if Make a Bet has been called
    
    #move   $a1, $a0              # Storing starting score into $a1
    
    lw     $a1  ($sp)            # poping address of array index 0 from stack
    
    jal    make_bet
    
    lw     $a0  32($sp)            # poping address of array index 0 from stack
    
    lw     $a1  36($sp)            #Loads the current score into $a1
    
    jal    win_or_lose
    
    beqz   $t1,  end_game          # Checks if win condition has been met
    beqz   $a1,  end_game          # Checks if lose condition has been met
    
    lw     $v0, 36($sp)
    
    addi   $sp, $sp, 28
    
    jal    return 
    
    
other1:
    bne    $a3, 2, other2          # Checks if Print Array has been called
    
    subi   $sp, $sp, 4
    sw     $a0, ($sp)
    
    lw     $a0  4($sp)             # poping address of array index 0 from stack
    
    jal    print_array
    
    lw     $v0, ($sp)              #pushing the current value into the stack
    addi   $sp, $sp, 8
    
    jal    return

other2:
    jal    end_game

return:

    
    lw     $ra  ($sp)            # pop return address from stack
    addi   $sp   $sp   4
    
        
    jr     $ra


#--------------------------------------------------------------------
# make_bet
#
# Called from take_turn.
#
# Performs the following tasks:
#
# 1. Player is prompted for their bet along with their index guess.
# 2. Max value in array and index of max value is determined.
#    (find_max subroutine is called)
# 3. Player guess is compared to correct index.
# 4. Score is modified
# 5. If player guesses correctly, max value in array is either:
#    --> no extra credit: replaced by -1
#    --> extra credit:    removed from array
#  
# arguments:  $a1 - address of first element in array
#             $a0 - current score of user
#
# return:     $v0 - updated score
#--------------------------------------------------------------------
#
# REGISTER USE
# $t0:      temporarily stores the current score and address of the array and stores the correct array index    
# $t3:      Holds the correct amount of bits the array address needs to get incremented to get to the max value 
# $t5:      Holds the integer value -1 to replace the max value
# $t6:      Stores the user input for the index and integer 4 used in multiplication
# $t7:      Holds the amount of points the user bet
# $a0:      Syscalls and address of the array 
# $a1:      Holds the current score
# $a2:      Temporarily Holds the array size
# $v0:      Syscalls, Holds the updated score
# $s0:      Holds Current score
# $s2:      Holds the array size
# $s3:      Holds the array index of the max value 
#--------------------------------------------------------------------


.data
bet_header:   .ascii  "------------------------------"
              .asciiz "\nMAKE A BET\n\n"
            
score_header: .ascii  "\n\n------------------------------"
              .asciiz "\nCURRENT SCORE\n\n"
            
cur_score1:   .asciiz "You currently have "

cur_score2:   .asciiz " points.\n"

bet_points:   .asciiz "How many points would you like to bet? "

errormsg:     .asciiz "\nSorry, your bet exceeds your current worth.\n\n"

index:        .asciiz "\nValid indices for this array are 0 - "

maxindex:     .asciiz "\nWhich index do you believe contains the maximum value? "

correct1:     .asciiz "\nScore! Index "

correct2:     .asciiz  " has the maximum value in the array.\n"

incorrect:    .asciiz "\nYour guess is incorrect! The maximum value is not in index "

lose1:        .asciiz "\n\nYou lost "

lose2:        .asciiz " points."

earn1:        .asciiz "\nYou earned "

earn2:        .asciiz  " points!\n"

removeval:    .asciiz "\nThis value has been removed from the array."

points:       .asciiz  " pts\n\n"

.text
make_bet: nop 
    
  
    
    subi   $sp   $sp  4            # push return address to stack
    sw     $ra  ($sp)

    subi   $sp   $sp  4            # push the current score
    move   $t0   $a0
    sw     $t0  ($sp)
 
    subi   $sp   $sp  4            # push the address of the first element in the array
    move   $t0   $a1
    sw     $t0  ($sp)
    
    addiu  $v0  $zero  4           # print header
    la     $a0  bet_header
    syscall

redo:
   
    li     $v0  4                  # prints the current score statement
    la     $a0  cur_score1
    syscall
    
    lw     $a1  4($sp)
    
    li     $v0  1
    move   $a0, $a1
    syscall
    
    li     $v0  4
    la     $a0  cur_score2
    syscall
     
    li     $v0  4                  # prints the bet statement
    la     $a0  bet_points
    syscall
    
    li     $v0  5                  # gets the user input on the amount of point they are willing to bet
    syscall 
    
    move   $t7, $v0
    
    blt    $a1, $t7, error1        # Checks if the bet amount exceeds the current amount of points
    bge    $a1, $t7, pass
error1: 
 
    li     $v0  4                  # prints the error message
    la     $a0  errormsg
    syscall
    
    j redo
    
pass: 
    
    li     $v0, 4                  # Prints the index prompt including the valid indicies
    la     $a0, index
    syscall               
    
    li     $v0, 1                  # prints the max array index
    move   $a0, $a2
    syscall
     
    la     $a0, '.'
    li     $v0, 11
    syscall
    
    li     $v0, 4
    la     $a0, maxindex
    syscall
    
    li     $v0, 5                  # Obtains the user input in which player thinks the max integer index is
    syscall 
    
    move   $t6, $v0                # moves the user input into $t6 register   
    
    lw     $a0, ($sp)              # pops the array address to $a0 register
    
    jal    find_max
    
    subi   $sp, $sp, 4
    sw     $s3, ($sp)
    
    lw     $s3, 8($sp)             #Loads current max index
    
    lw     $a1, 16($sp)            # loads the current score into $a1 register
    
    beq    $s3, $t6, correct       # Checks if the guess is right

    li     $v0  4                  # Prints statements stating that the guess was inncorrect
    la     $a0  incorrect 
    syscall 
    
    li     $v0  1
    move   $a0  $t6
    syscall 
    
    la     $a0, '.'
    li     $v0, 11
    syscall
    
    li     $v0, 4                  # Prints the amount of points lost
    la     $a0, lose1
    syscall 
    
    li     $v0, 1
    move   $a0, $t7
    syscall 
    
    li     $v0, 4
    la     $a0, lose2
    syscall 
    
    sub    $v1, $a1, $t7           # Subtracts the points from the current score
    
    j      result
    
correct:

    li     $v0, 4                  # Prints the statement that the guess was correct
    la     $a0, correct1
    syscall 
    
    move   $a0, $s3
    li     $v0, 1
    syscall   
    
    li     $v0, 4
    la     $a0, correct2
    syscall 
    
    li     $v0, 4                  # Prints the earned points statement 
    la     $a0, earn1
    syscall
    
    move   $a0, $t7
    li     $v0, 1
    syscall 
    
    li     $v0, 4
    la     $a0, earn2
    syscall 
    
    li     $v0, 4                  # Prints that the following array index value has been removed
    la     $a0, removeval      
    syscall
    
    li     $t6, 4                  # Loads 4 into $t6 register    
    
    move   $t0, $s3                # moves the correct array index into the $t0 register
    
    mul    $t3, $t0, $t6
    
    lw     $a0, 12($sp)             # Loads the address of the array
   
    add    $a0, $t3, $a0           # adds the correct amount of bits where the max integer is located in the array
    
    li     $t5, -1
    
    sw     $t5, ($a0)              # Stores -1 into the max array index
    
    sub    $a0, $a0, $t3
    
    sw     $a0, 32($sp)
   
    add    $v1, $a1, $t7           # stores the updated points into $s0 register
    
result:
  
    li     $v0, 4                  # Prints out the updated points that the player has
    la     $a0, score_header
    syscall
    
    li     $v0, 1 
    move   $a0, $v1 
    syscall 
    
    li     $v0, 4
    la     $a0, points
    syscall 
    
    move   $v0, $v1                # moves the updated score into the $v0 register
    
    lw     $s3  ($sp)

    lw     $ra  20($sp)              # pops the return address 
    addi   $sp, $sp, 4
    
    sw     $v0  36($sp)
    

    jr     $ra


#--------------------------------------------------------------------
# find_max
#
# Finds max element in array, returns index of the max value.
# Called from make_bet.
# 
# arguments:  $a0 - array
#
# returns:    $v0 - index of the maximum element in the array
#             $v1 - value of the maximum element in the array
#--------------------------------------------------------------------
#
# REGISTER USE
# $a0:        Holds the array address 
# $v0:        Stores the max integer
# $v1:        Stores the max integer value
# $s2:        Stores the max integer
# $s3:        Stores the max integer value
# $t0:        Holds the array address
# $t1:        Holds the current integer
# $t2:        Holds the current max integer
# $t3:        Holds the next integer
# $t4:        Holds the array size 
#--------------------------------------------------------------------

.text
find_max: nop

    subi   $sp, $sp, 4             # Pushes the return address
    sw     $ra  ($sp)
    
    li     $t2, 0                  # Loads 0 into $t2, $t4
    li     $t4, 0
    
    move   $t0, $a0                # Moves the array into $t0
    
find_max2: nop
    
    lw     $t1, ($t0)              # Loads the current integer
    
    addi   $t0, $t0, 4             # Increments the array 
    
    lw     $t3, ($t0)              # Loads the next integer
    
    addi   $t4, $t4, 1             # array size counter
    
    bgt    $t1, $t2, maxatm        # Compares the current integer with the previous max
    ble    $t1, $t2, notmax
    
maxatm: nop
    
    move   $t2, $t1                # Stores the max integer value into $v1
    move   $v1, $t2
    subi   $t4, $t4, 1
    move   $v0, $t4                # Stores the max integer index into $v0
    addi   $t4, $t4, 1
    beqz   $t3, foundmax
    jal    find_max2
    
notmax: nop

    beqz   $t3, foundmax
    jal    find_max2
    
foundmax: nop
                    
    
    subi   $t4, $t4, 1             # Stores the array index into $t4 
    
    lw     $ra, ($sp)              # Pops the return address
    addi   $sp, $sp, 4
    
    subi   $sp, $sp, 4             #Pushes the current index of the max element into the stack
    sw     $v0, ($sp)
    
    subi   $sp, $sp, 4             # Pushes the array size into stack 
    sw     $t4, ($sp)
    
    lw     $a2, ($sp)
    
    jr     $ra


#--------------------------------------------------------------------
# win_or_lose
#
# After turn is taken, checks to see if win or lose conditions
# have been met
# 
# arguments:  $a0 - address of the first element in array
#             $a1 - updated score
#
# return:     n/a
#--------------------------------------------------------------------
#
# REGISTER USE
# $a0:        Holds the address of the array, syscalls
# $a1:        Holds the current score 
# $v0:        syscall
# $s0:        Holds the current score   
# $t0:        Holds a integer of the array
# $t1:        Holds a -1 integer
# $t2:        Holds the next integer of the array
#--------------------------------------------------------------------

.data
win_msg:  .ascii   "------------------------------"
          .asciiz  "\nYOU'VE WON! HOORAY! :D\n\n"

lose_msg: .ascii   "------------------------------"
          .asciiz  "\nYOU'VE LOST! D:\n\n"

.text
win_or_lose: nop

    subi   $sp, $sp 4              # Pushes the return address to the stack
    sw     $ra ($sp)
    
    sw     $a0, 4($sp)
    
    sw     $a1, 8($sp)
    
    ble    $a1, $zero, lose3

loop1:

    li     $t1, -1                 #Checks if every single integer in the array is -1
    lw     $t0 ($a0) 
    bne    $t1, $t0, comeback
    addi   $a0, $a0, 4             # increments the array
    lw     $t2 ($a0)
    beqz   $t2, win
    beq    $t1, $t0, loop1
    
win:     

    bne    $t1, $t0, jump          # Checks if the last integer is -1
    
    addiu  $v0  $zero  4           #Prints the win message
    la     $a0  win_msg
    syscall
    
    li     $t1, 0                  # Loads 0 into $t1
    
    jal    jump
   
    
lose3: 

    addiu  $v0  $zero  4           # Prints the lose message
    la     $a0  lose_msg
    syscall

    jal    jump
     
jump:

    lw     $ra, ($sp)              # pops the return address
    addi   $sp, $sp 4
    
    jr     $ra


#--------------------------------------------------------------------
# print_array
#
# Print the array to the screen. Called from take_turn
# 
# arguments:  $a0 - address of the first element in array
#--------------------------------------------------------------------
#
# REGISTER USE
# $a0:        syscalls, address of the array
# $v0:        syscalls
# $t0:        Temporarily hold the array address and is loaded with 0 and hold the index
# $t1:        Holds the current integer value
# $t2:        Holds the next integer value 
# $t3:        Holds the array adddress       
#--------------------------------------------------------------------

.data
cheat_header: .ascii  "------------------------------"
              .asciiz "\nCHEATER!\n\n"
              
colon:        .asciiz ": "

nextline:     .asciiz "\n"

.text
print_array: nop

    subi   $sp, $sp, 4             #Push the return address
    sw     $ra ($sp) 
    
    subi   $sp, $sp, 4             # Push the Array address
    move   $t0, $a0
    sw     $t0 ($sp)
    
    addiu  $v0  $zero  4           # print header
    la     $a0  cheat_header
    syscall
    
    li     $t0, 0                  # Loads $t0 with 0
    
    lw     $t3 ($sp)               # pops the Array address into $t3 register 
    addi   $sp, $sp, 4
    
loop2: 
   
    li     $v0, 1                  # Prints the index of the array integer
    move   $a0, $t0
    syscall
    
    addi   $t0, $t0, 1             # Increments the index
    
    li     $v0, 4                  # Prints a colon and a space
    la     $a0, colon 
    syscall 
     
    lw     $t1 ($t3)               # Loads the current value into $t1 register
    
    addi   $t3, $t3, 4             # Increments the array 
    
    lw     $t2 ($t3)               # Loads the next value into $t2 register
    
    li     $v0, 1                  # Prints the current value 
    move   $a0, $t1
    syscall 
    
    li     $v0, 4                  # Prints a next line
    la     $a0, nextline
    syscall 
    
    beqz   $t2, pass2
    
    j loop2
    
pass2:

    li     $v0 4                   # Prints a next line
    la     $a0 nextline
    syscall 
    
    lw     $ra ($sp)               # Pops the return address
    addi   $sp, $sp, 4
    
    jr     $ra


#--------------------------------------------------------------------
# end_game (given)
#
# Exits the game. Invoked by user selection or if the player wins or
# loses.
#
# arguments:  $a0 - current score
#
# returns:    n/a
#--------------------------------------------------------------------
#
# REGISTER USE
# $a0: syscalls
# $v0: syscalls
#--------------------------------------------------------------------

.data
game_over_header: .ascii  "------------------------------"
                  .ascii  " GAME OVER"
                  .asciiz " ------------------------------"

.text
end_game: nop

    add    $s0  $zero  $a0         # save final score

    addiu  $v0  $zero  4           # print game over header
    la     $a0  game_over_header
    syscall
    
    addiu  $v0  $zero  11          # print new line
    addiu  $a0  $zero  0xA
    syscall
    
    addiu  $v0  $zero  10          # exit program cleanly
    syscall


#--------------------------------------------------------------------
# OPTIONAL SUBROUTINES
#--------------------------------------------------------------------
# You are permitted to delete these comments.

#--------------------------------------------------------------------
# get_array_size (optional)
# 
# Determines number of 1-word elements in array.
#
# argument:   $a0 - address of array index 0
#
# returns:    $v0 - number of 1-word elements in array
#--------------------------------------------------------------------

#--------------------------------------------------------------------
# prompt_bet (optional)
#
# Prompts user for bet amount and index guess. Called from make_bet.
# 
# arguments:  $a0 - current score
#             $a1 - address of array index 0
#             $a2 - array size in words
#
# returns:    $v0 - user bet
#             $v1 - user index guess
#--------------------------------------------------------------------

#--------------------------------------------------------------------
# compare (optional)
#
# Compares user guess with index of largest element in array. Called
# from make_bet.
#
# arguments:  $a0 - player index guess
#             $a1 - index of the maximum element in the array
#
# return:     $v0 - 1 = correct guess, 0 = incorrect guess
#--------------------------------------------------------------------

#--------------------------------------------------------------------
# mod_score (optional)
#
# Modifies score based on outcome of comparison between user guess
# correct answer. Returns score += bet for correct guess. Returns
# score -= bet for incorrect guess. Called from make_bet.
# 
# arguments:  $a0 - current score
#             $a1 - player’s bet
#             $a2 - boolean value from comparison
#
# return:     $v0 - updated score
#--------------------------------------------------------------------

#--------------------------------------------------------------------
# mod_array (optional)
#
# Replaces largest element in array with -1 if player guessed correctly.
# Called from make_bet.
#
# If extra credit implemented, the largest element in the array is
# removed and array shrinks by 1 element. Index of largest element
# is replaced by another element in the array.
# 
# arguments:  $a0 - address of array index 0
#             $a1 - index of the maximum element in the array
# 
# return:     n/a
#--------------------------------------------------------------------
