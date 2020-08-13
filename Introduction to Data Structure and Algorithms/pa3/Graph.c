/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA3
* File name:     Graph.c
* File Description: Function prototypes for Graph ADT
*********************************************************************************/

#include "Graph.h"


// Constructors-Destructors
// Creates and returns a new empty Graph
Graph newGraph(int n) {
  Graph newG = malloc(sizeof(GraphObj));
  newG->path = malloc((n+1) *sizeof(List));
  for (int i = 1; i <= n; i++) {
    newG->path[i] = newList();
  }
  newG->color = malloc((n+1)*sizeof(int));
  newG->parent = malloc((n+1)*sizeof(int));
  newG->distance = malloc((n+1)*sizeof(int));
  newG->order = n;
  newG->size = 0;
  newG->source = 0;
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
    free((*pG)->distance);
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

// Returns the source if source = 0, return NIL
int getSource(Graph G) {
  if (G == NULL) {
    printf("Graph Error: calling getSource() on NULL Graph reference\n");
    exit(1);
  }
  if (G->source != 0) {
    return G->source;
  }
  else {
    return NIL;
  }
}

// Gets the parent of the vertex u if BFS has been called or NIL otherwise
int getParent(Graph G, int u) {
  if (G == NULL) {
    printf("Graph Error: calling getParent() on NULL Graph reference\n");
    exit(1);
  }
  if (u >= 1 && u <= getOrder(G)) {
    if (getSource(G) == NIL) {
      return NIL;
    }
    else {
      return G->parent[u];
    }
  }
  else {
    printf("Graph Error: calling getParent() on Parent index that does not exist\n");
    exit(1);
  }
}

// Returns the distance from the most recent BFS source to vertex u or INF otherwise
int getDist(Graph G, int u) {
  if (G == NULL) {
    printf("Graph Error: calling getDist() on NULL Graph reference\n");
    exit(1);
  }
  if (u >= 1 && u <= getOrder(G)) {
    if (getSource(G) == NIL) {
      return INF;
    }
    else {
      return G->distance[u];
    }
  }
  else {
    printf("Graph Error: calling getDist() on distance index that does not exist\n");
    exit(1);
  }
}

// appends to the List L the vertices of a shortest path  in G from source to u
// or appends to L the value NIL if no such path exists
void getPath(List L, Graph G, int u) {
  int parent;
  if (getSource(G) != NIL) {
    //printf("u: %d, getOrder(G): %d\n", u, getOrder(G));
    //exit(1);
    if (u >= 1 && u <= getOrder(G)) {
      if (getSource(G) == u) {
        append(L, u);
        return;
      }
      else if (getParent(G, u) == NIL) {
        append(L, NIL);
        return;
      }
      else {
        parent = getParent(G, u);
        getPath(L, G, parent);
        append(L, u);
      }
    }
    else {
      printf("Graph Error: calling getPath() on vertex index that does not exist\n");
      exit(1);
    }
  }
  else {
    printf("Graph Error: calling getPath() before bfs() has been called\n");
    exit(1);
  }
}

// Manipulation procedures

// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {
  for (int i = 0; i < getOrder(G); i++) {
    freeList(&G->path[i]);
    G->path[i] = newList();
  }
  free(&G->color);
  free(&G->parent);
  free(&G->distance);
  int n = getOrder(G);
  G->color = calloc(n+1, sizeof(int));
  G->parent = calloc(n+1, sizeof(int));
  G->distance = calloc(n+1, sizeof(int));
  G->size = 0;
  G->source = 0;
  return;
}

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

// Runs the BFS algorithm on the Graph G with source s, setting the color, distance
// parent, and source fields of G accordingly
void BFS(Graph G, int s) {
  int x, y, dist = 0;
  for (int i = 1; i <= getOrder(G); i++) {
    if (i != s) {
      G->color[i] = 0;
      G->distance[i] = INF;
      G->parent[i] = NIL;
    }
  }
  G->color[s] = 1;
  G->distance[s] = dist;
  G->parent[s] = NIL;
  List L = newList();
  prepend(L, s);
  while (length(L) != 0) {
    moveFront(L);
    x = get(L);
    delete(L);
    moveFront(G->path[x]);
    while (index(G->path[x]) != -1) {
      y = get(G->path[x]);
      if (G->color[y] == 0) {
        G->color[y] = 1;
        G->distance[y] = G->distance[x] + 1;
        G->parent[y] = x;
        append(L, y);
      }
      moveNext(G->path[x]);
    }
    G->color[x] = 2;
  }
  freeList(&L);
  G->source = s;
  return;
}

// Other operations
// Promts tje adjancency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
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
