/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA3
* File name:     Graph.h
* File Description: Header File for Graph ADT
*********************************************************************************/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#define NIL -1
#define INF -2

#include <stdio.h>
#include "List.h"

typedef struct GraphObj{
  struct Listobj** path;
  int* color;
  int* parent;
  int* distance;
  int size;
  int order;
  int source;
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

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

// Manipulation procedures
void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

// Other operations
void printGraph(FILE* out, Graph G);

#endif
