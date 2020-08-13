/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA4
* File name:     Graph.h
* File Description: Header File for Graph ADT
*********************************************************************************/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "List.h"

#define NIL -1
#define UNDEF -2


typedef struct GraphObj {
  List* path;
  int* color;
  int* parent;
  int* dtime;
  int* ftime;
  int size;
  int order;
} GraphObj;

typedef GraphObj* Graph;

// Constructors-Destructors
Graph newGraph(int n);

void freeGraph(Graph* pG);

// Access functions
int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

// Manipulation procedures
void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);

void Visit(Graph G, int x, int* time);

// Other operations
Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif
