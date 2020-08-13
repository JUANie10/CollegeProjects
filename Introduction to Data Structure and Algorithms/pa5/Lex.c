/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA5
* File name:     Lex.c
* File Description: Sorts the Inserted file in alphabetical order and writes it into the outfile using Dictionary ADT
*********************************************************************************/
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
  
  // Initializing Variables
  int count = 0, c = 0;
  FILE *in, *out;
  char line[160];
  
  // check command line for correct number of arguments
  if (argc != 3) {
     printf("Input the following: %s <input file> <output file>\n", argv[0]);
     exit(1);
  }

  // open files for reading and writing
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  
  // Printing out error for the in and out files if either are NULL
  if (in == NULL) {
     printf("Unable to open file %s in reading mode\n", argv[1]);
     exit(1);
  }
  if (out == NULL) {
     printf("Unable to open file %s in writing mode\n", argv[2]);
     exit(1);
  }
  // Counting the number of lines within the input file
  while (fgets(line, 160, in) != NULL) {
    count++;
  }
  rewind(in);
  
  // Creating an array of the number of lines
  char *lines[count];
  
  // Dynamically allocating an array
  for (int i = 0; i < count; i++) {
    lines[i] = calloc(160, sizeof(char*));
  }
  char buffer[160];
  
  // Inserts each line into the array.
  while (fgets(buffer, sizeof(buffer), in)) {
    strcpy(lines[c], buffer);
    c++;
  }
  
  // Creating a dictionary thats
  Dictionary D = newDictionary(0);
  
  // inserting the lines from infile to the dicitonary
  for (int i = 0; i < count; i++) {
    insert(D, lines[i], VAL_UNDEF);
  }
  
  // prints the Dictionary using in-order tree traversal
  printDictionary(out, D);
  
  
  // freeing all the heap memory allocated.
  for (int i = 0; i < count; i++) {
    free(lines[i]);
  }
  freeDictionary(&D);
  fclose(in);
  fclose(out);
}
