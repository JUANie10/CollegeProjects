/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA3
* File name:     GraphTest.c
* File Description: Edge cases and test cases for Graph ADT
*********************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Graph.h"
#include "List.h"

void printfList(List L);

int main(void) {
  List L = newList();
  Graph A = newGraph(100);
  List C = newList();
  append(C, 3);
  append(C, 42);
  append(C, 2);
  append(C, 64);
  
  addArc(A, 64, 4);
  addArc(A, 64, 3);
  addArc(A, 42, 2);
  addArc(A, 2, 64);
  addArc(A, 4, 2);
  addArc(A, 3, 42);
  BFS(A, 3);
  getPath(L, A, 64);
  printfList(L);
  printfList(C);
  printf("equals: %d\n", equals(L, C));
  
  
  addEdge(A, 64, 4);
  addEdge(A, 64, 3);
  addEdge(A, 42, 2);
  addEdge(A, 2, 64);
  addEdge(A, 4, 2);
  addEdge(A, 3, 42);
  BFS(A, 64);
  printf("Distance of 2: %d\n", getDist(A, 2));
  
  addEdge(A, 64, 4);
  addEdge(A, 64, 3);
  addEdge(A, 42, 2);
  addEdge(A, 2, 64);
  addEdge(A, 4, 2);
  addEdge(A, 3, 42);
  BFS(A, 3);
  getPath(L, A, 64);
  printfList(L);
  
  return 0;
}

void printfList(List L) {
  moveFront(L);
  while (index(L) != -1) {
    printf("%d ", get(L));
    moveNext(L);
  }
  printf("\n");
}
