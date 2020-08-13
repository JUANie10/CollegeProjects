#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 3
#
# Name:       Juan Lee
# CruzID:      jlee543
# Course:       CSE 101 Spring 2020 P3
# File name:     Makefile
# File Description: Compiles the files together
#
#  Makefile for CMPS 101 Programming Assignment 3
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on findpath
#  make checkClient         tests GraphClient for memory leaks
#  make checkTest           tests GraphTest for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c11 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)
	
GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c
	
GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindPath GraphClient GraphTest FindPath.o GraphClient.o GraphTest.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath infile1.txt outfile1.txt

checkClient : GraphClient
	$(MEMCHECK) GraphClient

checkTest : GraphTest
	$(MEMCHECK) GraphTest
