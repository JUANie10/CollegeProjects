/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA4
* File name:     GraphTest.c
* File Description: Edge cases and test cases for Graph ADT
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

void printfList(FILE* out, List L);

int main(int argc, char* argv[]) {

  int num1 = 0, num2 = 0, counter = 0, component = 0;
  FILE *in, *out;

  Graph G = newGraph(6);
  
  // Creates and stores the verticies in List L in increasing order
  List L = newList();
  for (int i = 1; i <= 6; i++) {
    append(L, i);
  }
  
  // Adding edges given from the infile
  addArc(G, 1, 2);
  addArc(G, 1, 4);
  addArc(G, 2, 3);
  addArc(G, 2, 5);
  addArc(G, 2, 6);
  addArc(G, 5, 3);
  addArc(G, 5, 4);
  addArc(G, 5, 6);
  // Runs DFS on the Graph G
  DFS(G, L);
  
  moveFront(L);
  printf("Regular:\n");
  while(index(L) != -1) {
    printf("dtime: %d, ftime: %d\n", getDiscover(G, get(L)), getFinish(G, get(L)));
    printf("%d parent: %d\n", get(L) ,getParent(G, get(L)));
    moveNext(L);
  }
  // Transposes the Graph and runs DFS on it with the List from the first DFS
  Graph Gt = transpose(G);
  DFS(Gt, L);
  
  
  printf("Tanspose:\n");
  moveFront(L);
  
  while (index(L) != -1) {
    printf("dtime: %d, ftime: %d\n", getDiscover(Gt, get(L)), getFinish(Gt, get(L)));
    printf("%d parent: %d\n", get(L) ,getParent(Gt, get(L)));
    moveNext(L);
  }
  
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
