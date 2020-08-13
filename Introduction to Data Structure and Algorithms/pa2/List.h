/*********************************************************************************
* Name: 			Juan Lee
* CruzID:			jlee543
* Course: 			CSE 101 Spring 2020  PA2
* File name: 		List.h
* File Description: Function headers for List ADT
*********************************************************************************/

#ifndef __LIST_H__
#define __LIST_H__

// Header files
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Struct Definitions ----------------------------------------------------------

// Struct for Node
typedef struct Nodeobj {
  struct Nodeobj* prev;
  struct Nodeobj* next;
  long data;
} Nodeobj;

// Private Node type
typedef Nodeobj* Node;


// Struct for List
typedef struct Listobj {
  Node front;
  Node back;
  Node cursor;
  long index;
  long length;
} Listobj;


// Private List type
typedef Listobj* List;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new Node.
Node newNode(long data);

void freeNode(Node* N);

// Creates and returns a new empty List.
List newList(void);

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
long length(List L);

// Returns index of cursor element if defined, -1 otherwise.
long index(List L);

// Returns front element of L. Pre: length()>0
long front(List L);

// Returns back element of L. Pre: length()>0
long back(List L);

// Returns cursor element of L. Pre: length()>0, index()>=0
long get(List L);

// Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.
long equalss(List A, List B);

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L);

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L);

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L);

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L);

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L);

// Insert new element longo L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, long data);

// Insert new element longo L. If L is non-empty,
// insertion takes place after back element.
void append(List L, long data);

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, long data);

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, long data);

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, long x);

// Delete the front element. Pre: length()>0
void deleteFront(List L);

// Delete the back element. Pre: length()>0
void deleteBack(List L);

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L);

// Other operations -----------------------------------------------------------

// Prints to the file polonged to by out, a
// string representation of L consisting
// of a space separated sequence of longegers,
// with front on left.
void printList(FILE* out, List L);

// Returns a new List representing the same longeger
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L); 

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B); 

#endif
