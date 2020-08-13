/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA1
* File name:     Lex.c
* File Description: Sorts the Inserted file in alphabetical order and writes it into the outfile.
*********************************************************************************/
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
  
  int count = 0, i = 0;
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
  char array[count][160];
  char buffer[160];
  
  // Inserts each line into the array.
  while (fgets(buffer, sizeof(buffer), in)) {
    strcpy(array[i], buffer);
    i++;
  }
  
  // Storing the array in alphabetical order to a doubly linked list.
  List sortedList = newList();
  bool found;
  
  for (int c = 0; c < count; c++) {
    // first item in the list
    if (c == 0) {
      append(sortedList, c);
    }
    else {
      moveFront(sortedList);
      found = false;
      while(found == false) {
        int d = get(sortedList);
        // Sorts using comparisons of the strings through ascii values
        if (strcmp(array[c], array[d]) > 0) {
          if (sortedList->cursor->next != NULL) {
            moveNext(sortedList);
          }
          else {
            insertAfter(sortedList, c);
            found = true;
          }
        }
        else {
          insertBefore(sortedList, c);
          found = true;
        }
      }
    }
  }
  
  // Writing the contents of the array to a file in alphabetical order.
  moveFront(sortedList);
  while(sortedList->cursor != NULL) {
    int arrayindex = get(sortedList);
    fprintf(out,"%s\n", array[arrayindex] );
    moveNext(sortedList);
  }
  
  // freeing all the heap memory allocated.
  freeList(&sortedList);
  fclose(in);
  fclose(out);
}
