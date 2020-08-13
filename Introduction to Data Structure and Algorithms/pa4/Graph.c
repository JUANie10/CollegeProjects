/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA4
* File name:     Graph.c
* File Description: Function prototypes for Graph ADT
*********************************************************************************/

#include "Graph.h"

// Constructors-Destructors
// Creates and returns a new empty Graph
Graph newGraph(int n) {
  Graph newG = malloc(sizeof(GraphObj));
  newG->path = malloc((n+1) *sizeof(List));
  newG->dtime = malloc((n+1)*sizeof(int));
  newG->ftime = malloc((n+1)*sizeof(int));
  newG->parent = malloc((n+1)*sizeof(int));
  for (int i = 1; i <= n; i++) {
    newG->path[i] = newList();
    newG->dtime[i] = UNDEF;
    newG->ftime[i] = UNDEF;
    newG->parent[i] = NIL;
  }
  newG->color = malloc((n+1)*sizeof(int));
  newG->order = n;
  newG->size = 0;
  return newG;
}

//frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG) {
  if (*pG != NULL) {
    for (int i = 1; i <= getOrder(*pG); i++) {
      freeList(&(*pG)->path[i]);
    }
    free((*pG)->path);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->dtime);
    free((*pG)->ftime);
    free(*pG);
    *pG = NULL;
  }
  return;
}

// Access functions

// Returns the number of vertexes
int getOrder(Graph G) {
  if (G == NULL) {
    printf("Graph Error: calling getOrder() on NULL Graph reference\n");
    exit(1);
  }
  return G->order;
}

// Returns the number of edges
int getSize(Graph G) {
  if (G == NULL) {
    printf("Graph Error: calling getSize() on NULL Graph reference\n");
    exit(1);
  }
  return G->size;
}


// Gets the parent of the vertex u if BFS has been called or NIL otherwise
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u) {
  if (G == NULL) {
    printf("Graph Error: calling getParent() on NULL Graph reference\n");
    exit(1);
  }
  if (u >= 1 && u <= getOrder(G)) {
    return G->parent[u];
  }
  else {
    printf("Graph Error: calling getParent() on Parent index that does not exist\n");
    exit(1);
  }
}

// Returns the discover time of variable u. Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u) {
  if (G == NULL) {
    printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
    exit(1);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling getDiscover() on Parent index that does not exist\n");
    exit(1);
  }
  return G->dtime[u];
}

// Returns the Finish time of variable u.  Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u) {
  if (G == NULL) {
    printf("Graph Error: calling getFinish() on NULL Graph reference\n");
    exit(1);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling getFinish() on Parent index that does not exist\n");
    exit(1);
  }
  return G->ftime[u];
}

// Manipulation procedures

// inserts a new edge joining u to v and v to u
// pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling addEdge() on vertex index that does not exist\n");
    exit(1);
  }
  else if (v < 1 || v > getOrder(G)) {
    printf("Graph Error: calling addEdge() on vertex index that does not exist\n");
    exit(1);
  }
  else {
    addArc(G, u, v);
    addArc(G, v, u);
    G->size -= 1;
  }
  return;
}

// inserts a new directed edge from u to v
// pre: 1 <= u <= getOrder(G)
void addArc(Graph G, int u, int v) {
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling addEdge() on vertex index that does not exist\n");
    exit(1);
  }
  else if (v < 1 || v > getOrder(G)) {
    printf("Graph Error: calling addEdge() on vertex index that does not exist\n");
    exit(1);
  }
  else {
    moveFront(G->path[u]);
    if (index(G->path[u]) == -1) {
      append(G->path[u], v);
    }
    while (index(G->path[u]) != -1) {
      if (get(G->path[u]) < v) {
        moveNext(G->path[u]);
        if (index(G->path[u]) == -1) {
          append(G->path[u], v);
        }
      }
      else if (get(G->path[u]) == v) {
        return;
      }
      else {
        insertBefore(G->path[u], v);
        break;
      }
    }
    G->size = getSize(G) + 1;
  }
  return;
}

// Runs Depth First Search in order of the verticies within List S and stores
// the verticies in topological order in List S.
void DFS(Graph G, List S) {
  if (length(S) != getOrder(G)) {
    printf("Graph Error: calling DFS() when length(S) != getOrder(G)\n");
    exit(1);
  }
  for (int i = 1; i <= getOrder(G); i++) {
    G->color[i] = 0;
    G->parent[i] = NIL;
  }
  int time = 0, x;
  List L = copyList(S);
  moveFront(L);
  clear(S);
  while (index(L) != -1) {
    x = get(L);
    //printf("get(S): %d\n", x);
    if (G->color[x] == 0) {
      Visit(G, x, &time);
    }
    moveNext(L);
  }
  for (int i = 1; i <= getOrder(G); i++) {
    if (length(S) == 0) {
      append(S, i);
    }
    else {
      moveFront(S);
      while(index(S) != -1) {
        if (getFinish(G, i) > getFinish(G, get(S))) {
          insertBefore(S, i);
          break;
        }
        else {
          moveNext(S);
          if (index(S) == -1) {
            append(S, i);
            break;
          }
        }
      }
    }
  }
  freeList(&L);
}

// Discovers the vertex x and finishes vertex that doesn't have an adjacent
// vertex that hasn't been discovered
void Visit(Graph G, int x, int* time) {
  int y;
  G->dtime[x] = ++(*time);
  G->color[x] = 1;
  moveFront(G->path[x]);
  while (index(G->path[x]) != -1) {
    y = get(G->path[x]);
    if (G->color[y] == 0) {
      G->parent[y] = x;
      Visit(G, y, time);
    }
    moveNext(G->path[x]);
  }
  G->color[x] = 2;
  G->ftime[x] = ++(*time);
  return;
}

// Other operations

// Transposes a Graph G. In other words, reverse all edges.
Graph transpose(Graph G) {
  Graph newG = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    moveFront(G->path[i]);
    while (index(G->path[i]) != -1) {
      addArc(newG, get(G->path[i]), i);
      moveNext(G->path[i]);
    }
  }
  return newG;
}

// Copies a Graph and returns it.
Graph copyGraph(Graph G) {
  Graph newG = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    freeList(&(G)->path[i]);
    newG->path[i] = copyList(G->path[i]);
    newG->dtime[i] = getDiscover(G, i);
    newG->ftime[i] = getFinish(G, i);
    newG->color[i] = G->color[i];
    newG->parent[i] = G->parent[i];
  }
  newG->size = getSize(G);
  newG->order = getOrder(G);
  return newG;
}

// Prints the adjancency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
  fprintf(out, "Adjacency list representation of G:\n");
  for (int i = 1; i <= getOrder(G); i++) {
    fprintf(out, "%d: ", i);
    moveFront(G->path[i]);
    while (index(G->path[i]) != -1) {
      fprintf(out, "%d ", get(G->path[i]));
      moveNext(G->path[i]);
    }
    fprintf(out, "\n");
  }
  fprintf(out, "\n");
  return;
}
