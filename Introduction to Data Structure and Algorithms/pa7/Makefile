#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 7
#
# Name:       Juan Lee
# CruzID:      jlee543
# Course:       CSE 101 Spring 2020 PA7
# File name:     Makefile
# File Description: Compiles the files together
#
#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListTest       make ListTest
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

Shuffle : Shuffle.o List.o
	g++ -std=c++11 -Wall -o Shuffle Shuffle.o List.o

Shuffle.o : List.h Shuffle.cpp
	g++ -std=c++11 -Wall -c Shuffle.cpp

ListTest : ListTest.o List.o
	g++ -std=c++11 -Wall -o ListTest ListTest.o List.o

ListTest.o : List.h ListTest.cpp
	g++ -std=c++11 -Wall -c ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++11 -Wall -c List.cpp

clean :
	rm -f Shuffle Shuffle.o ListTest ListTest.o List.o

check1 : ListClient
	valgrind --leak-check=full ListClient

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35
