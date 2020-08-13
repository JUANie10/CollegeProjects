#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
# Name:       Juan Lee
# CruzID:      jlee543
# Course:       CSE 101 Spring 2020 PA2
# File name:     Makefile
# File Description: Compiles the files together
#
# make                   makes Arithmetic
# make ListTest          makes ListTest
# make ModelListTest     makes ModelListTest
# make BigIntegerTest    makes BigIntegerTest
# make ModelBigIntegerTest   makes ModelBigIntegerTest
# make clean             removes all binaries
# make checkBigModel     checks ModelBigIntegerTest for memory errors
# make checkArithmetic   checks Arithmetic for memory errors
# make checkModel        checks ModelListFile for memory errors
#------------------------------------------------------------------------------


Arithmetic : Arithmetic.o List.o BigInteger.o
	gcc -std=c11 -Wall -o Arithmetic Arithmetic.o List.o BigInteger.o

Arithmetic.o : Arithmetic.c List.h BigInteger.h
	gcc -std=c11 -Wall -c Arithmetic.c

ModelListTest	: ModelListTest.o List.o
	gcc -std=c11 -Wall -o ModelListTest ModelListTest.o List.o

ModelListTest.o : ModelListTest.c List.h
	gcc -std=c11 -Wall -c ModelListTest.c
	
ListTest	: ListTest.o List.o
	gcc -std=c11 -Wall -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -std=c11 -Wall -c ListTest.c
	
ModelBigIntegerTest	: ModelBigIntegerTest.o BigInteger.o List.o
	gcc -std=c11 -Wall -o ModelBigIntegerTest ModelBigIntegerTest.o BigInteger.o List.o

ModelBigIntegerTest.o	:	ModelBigIntegerTest.c	BigInteger.h List.h
	gcc -std=c11 -Wall -c ModelBigIntegerTest.c
	
BigIntegerTest : BigIntegerTest.o List.o BigInteger.o
	gcc -std=c11 -Wall -o BigIntegerTest BigIntegerTest.o List.o BigInteger.o

BigIntegerTest.o : BigIntegerTest.c List.h BigInteger.h
	gcc -std=c11 -Wall -c BigIntegerTest.c
	
List.o : List.c List.h
	gcc -std=c11 -Wall -c List.c
	
BigInteger.o : BigInteger.c BigInteger.h
	gcc -std=c11 -Wall -c BigInteger.c

clean :
	rm -f Arithmetic Arithmetic.o ModelListTest ListTest.o ListTest BigInteger.o List.o ModelListTest.o ModelBigIntegerTest ModelBigIntegerTest.o BigIntegerTest BigIntegerTest.o

checkArithmetic :
	valgrind --leak-check=full Arithmetic
 
checkModel :
	valgrind --leak-check=full ModelListTest

checkBigModel :
	valgrind --leak-check=full ModelBigIntegerTest
