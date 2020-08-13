#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 5
#
# Name:       Juan Lee
# CruzID:      jlee543
# Course:       CSE 101 Spring 2020 PA5
# File name:     Makefile
# File Description: Compiles the files together
#
#  Makefile for CSE 101 Programming Assignment 5
#
#  make                     makes Lex
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make check1              checks DictionaryTest for memory leaks
#  make check2              checks Lex for memory leaks on in4
#------------------------------------------------------------------------------

TOP              = Lex
TOP_OBJ          = $(TOP).o
TOP_SRC          = $(TOP).c
ADT              = Dictionary
TEST             = $(ADT)Test
TEST_OBJ         = $(TEST).o
TEST_SRC         = $(TEST).c
ADT_OBJ          = $(ADT).o
ADT_SRC          = $(ADT).c
ADT_HDR          = $(ADT).h
COMPILE          = gcc -std=c11 -Wall -c
LINK             = gcc -std=c11 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full --track-origins=yes

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
	$(REMOVE) $(TOP) $(TOP_OBJ) $(TEST) $(TEST_OBJ) $(ADT_OBJ)

check1 : $(TEST)
	$(MEMCHECK) $(TEST)

check2 : $(TOP)
	$(MEMCHECK) $(TOP) in4 junk4
