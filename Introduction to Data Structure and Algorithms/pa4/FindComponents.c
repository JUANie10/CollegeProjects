/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA4
* File name:     FindComponents.c
* File Description: Creates a graph from the entered edges in the infile and finds the strongly connected components
 *********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

void printfList(FILE* out, List L);

int main(int argc, char* argv[]) {
  // Initializing the variables needed
  int num1 = 0, num2 = 0, counter = 0, component = 0;
  FILE *in, *out;

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
  // Scans the amount of vertex from the infile and sets up a graph
  fscanf(in, "%d", &num1);
  Graph G = newGraph(num1);
  
  // Creates and stores the verticies in List L in increasing order
  List L = newList();
  for (int i = 1; i <= num1; i++) {
    append(L, i);
  }
  
  // Adding edges given from the infile
  while (fscanf(in, "%d %d", &num1, &num2) != EOF) {
    if (num1 == 0 && num2 == 0) {
      printGraph(out, G);
      break;
    }
    else {
      addArc(G, num1, num2);
    }
  }
  // Runs DFS on the Graph G
  DFS(G, L);
  
  // Transposes the Graph and runs DFS on it with the List from the first DFS
  Graph Gt = transpose(G);
  DFS(Gt, L);
  
  // Counts the number of strongly connected components
  moveBack(L);
  while (index(L) != -1) {
    if (getParent(Gt, get(L)) == NIL) {
      counter++;
    }
    movePrev(L);
  }
  
  // Prints the strongly connected Components one by one
  fprintf(out, "G contains %d strongly connected components:\n", counter);
  List tempList = newList();
  moveBack(L);
  while (index(L) != -1) {
    if (getParent(Gt, get(L)) == NIL) {
      prepend(tempList, get(L));
      component++;
      fprintf(out, "Component %d:", component);
      printfList(out, tempList);
      clear(tempList);
    }
    else {
      prepend(tempList, get(L));
    }
    movePrev(L);
  }
  
  // freeing all allocated memory
  freeGraph(&G);
  freeGraph(&Gt);
  freeList(&tempList);
  freeList(&L);
  fclose(in);
  fclose(out);
  return 0;
}

// prints a List to the outfile
void printfList(FILE* out, List L) {
  moveFront(L);
  while (index(L) != -1) {
    fprintf(out," %d", get(L));
    moveNext(L);
  }
  fprintf(out, "\n");
}
