#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# Name:       Juan Lee
# CruzID:      jlee543
# Course:       CSE 101 Spring 2020 PA1
# File name:     Makefile
# File Description: Compiles the files together
#
# make                   makes Lex
# make ListClient        makes ListClient
# make ModelListTest     makes ModelListTest
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
# make checkModel        checks ModelTestFile for memory erros
#------------------------------------------------------------------------------


Lex : Lex.o List.o
	gcc -std=c11 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c11 -Wall -c Lex.c

ListClient: ListClient.o List.o
	gcc -std=c11 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -std=c11 -Wall -c ListClient.c
	
ModelListTest	: ModelListTest.o ModelListTest.o
	gcc -std=c11 -Wall -o ModelListTest ModelListTest.o List.o

ModelListTest.o : ModelListTest.c List.h
	gcc -std=c11 -Wall -c ModelListTest.c

List.o : List.c List.h
	gcc -std=c11 -Wall -c List.c

clean :
	rm -f Lex ListClient ModelListTest Lex.o ListClient.o List.o ModelListTest.o

checkClient :
	valgrind --leak-check=full ListClient

checkLex :
	valgrind --leak-check=full Lex
 
checkModel :
	valgrind --leak-check=full ModelListTest

