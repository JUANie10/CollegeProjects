/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA3
* File name:     FindPath.c
* File Description: Creates a graph and finds the distance between vertexs and the shortest paths
 *********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

void printfList(FILE* out, List L);

int main(int argc, char* argv[]) {

  int num1 = 0, num2 = 0;
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
  List L = newList();
  
  // Adding edges given from the infile
  while (fscanf(in, "%d %d", &num1, &num2) != EOF) {
    if (num1 == 0 && num2 == 0) {
      printGraph(out, G);
      break;
    }
    else {
      addEdge(G, num1, num2);
    }
  }
  // Printing the shortest distances and paths of the numbers fromt the infile
  while (fscanf(in, "%d %d", &num1, &num2) != EOF) {
    if (num1 == 0 && num2 == 0) {
      break;
    }
    else {
      clear(L);
      BFS(G, num1);
      fprintf(out, "The distance from %d to %d is ", num1, num2);
      if (getDist(G, num2) == INF) {
        fprintf(out, "infinity\nNo %d-%d path exists\n", num1, num2);
      }
      else {
        fprintf(out,"%d\nA shortest %d-%d path is: ", getDist(G, num2), num1, num2);
        getPath(L, G, num2);
        printfList(out, L);
      }
    }
  }
  // freeing all allocated memory
  freeGraph(&G);
  freeList(&L);
  fclose(in);
  fclose(out);
  return 0;
}

// prints a List to the outfile
void printfList(FILE* out, List L) {
  moveFront(L);
  while (index(L) != -1) {
    fprintf(out,"%d ", get(L));
    moveNext(L);
  }
  fprintf(out, "\n");
}
