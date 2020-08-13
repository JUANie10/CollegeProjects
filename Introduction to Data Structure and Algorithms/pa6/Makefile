#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 6
#
# Name:       Juan Lee
# CruzID:      jlee543
# Course:       CSE 101 Spring 2020 PA6
# File name:     Makefile
# File Description: Compiles the files together
#
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                  makes Order
#  make WordFrequency    makes WordFrequency
#  make clean            removes all binaries
#  make check1           checks WordFrequency for memory leaks on Big.txt
#  make check2           checks Order for memory leaks on English.txt
#------------------------------------------------------------------------------

TOP              = Order
TOP_OBJ          = $(TOP).o
TOP_SRC          = $(TOP).c
ADT              = Dictionary
TEST             = WordFrequency
TEST_OBJ         = $(TEST).o
TEST_SRC         = $(TEST).c
ADT_OBJ          = $(ADT).o
ADT_SRC          = $(ADT).c
ADT_HDR          = $(ADT).h
COMPILE          = gcc -std=c11 -Wall -c
LINK             = gcc -std=c11 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full  --track-origins=yes


$(TOP) : $(TOP_OBJ) $(ADT_OBJ)
	$(LINK) $(TOP) $(TOP_OBJ) $(ADT_OBJ)

$(TEST) : $(TEST_OBJ) $(ADT_OBJ)
	$(LINK) $(TEST) $(TEST_OBJ) $(ADT_OBJ)

$(TOP_OBJ) : $(TOP_SRC) $(ADT_HDR)
	$(COMPILE) $(TOP_SRC)

$(TEST_OBJ) : $(TEST_SRC) $(ADT_HDR)
	$(COMPILE) $(TEST_SRC)

$(ADT_OBJ) : $(ADT_SRC) $(ADT_HDR)
	$(COMPILE) $(ADT_SRC)

clean :
	$(REMOVE) $(TOP) $(TOP_OBJ) $(TEST) $(TEST_OBJ) $(ADT_OBJ) junk

check1 : $(TEST)
	$(MEMCHECK) $(TEST) infile5.txt junk

check2 : $(TOP)
	$(MEMCHECK) $(TOP) infile5.txt junk
