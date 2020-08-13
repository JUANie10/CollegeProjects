/*********************************************************************************
* Name: 			Juan Lee
* CruzID:			jlee543
* Course: 			CSE 101 Spring 2020 PA1
* File name: 		List.c
* File Description: Function prototypes for List ADT
*********************************************************************************/
// Header files
#include "List.h"




// Constructors-Destructors ---------------------------------------------------

 
// Creates and returns a new Node.
Node newNode(int data) {
  Node newNode = malloc(sizeof(Nodeobj));
  newNode->data = data;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

// Creates and returns a new empty List.
List newList(void) {
  List newList = malloc(sizeof(Listobj));
  newList->front = NULL;
  newList->back = NULL;
  newList->cursor = NULL;
  newList->index = -1;
  newList->length = 0;
  return newList;
}

// Free the node and sets N to NULL
void freeNode(Node* N) {
  if (N != NULL && *N != NULL) {
    free(*N);
    N = NULL;
  }
  return;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
  if (pL != NULL && *pL != NULL) {
    while (length(*pL) > 0) {
      deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
  }
  return;
}


// Access functions -----------------------------------------------------------

 // Returns the number of elements in L.
int length(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return L->length;
}

 // Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
  }
  
  if (L->cursor != NULL) {
    return L->index;
  }
  else {
    return -1;
  }
}

 // Returns front element of L. Pre: length()>0
int front(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }
  if (length(L) > 0) {
    return L->front->data;
  }
  else if (length(L) == 0) {
    printf("List Error: calling front() on empty List\n");
    exit(1);
  }
  return L->front->data;
}

 // Returns back element of L. Pre: length()>0
int back(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  }
  if (length(L) > 0) {
    return L->back->data;
  }
  else if (length(L) == 0) {
    printf("List Error: calling back() on empty List\n");
    exit(1);
  }
  return L->back->data;
}

 // Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  }
  if (length(L) == 0) {
    printf("List Error: calling get() on empty List\n");
    exit(1);
  }
  if (length(L) > 0 && index(L) >= 0) {
    return L->cursor->data;
  }
  return L->cursor->data;
}

 // Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.
int equals(List A, List B) {
  // test cases
  if (A == NULL || B == NULL) {
    printf("List Error: calling equals() on NULL List reference\n");
    exit(1);
  }
  if (length(A) == 0 && length(B) == 0) {
    return 1;
  }
  else {
    if (length(A) != length(B)) {
      return 0;
    }
    else {
      Node tempnode = A->front, tempnode1 = B->front;
      while(tempnode != NULL && tempnode1 != NULL) {
        if (tempnode->data != tempnode1->data) {
          return 0;
        }
        tempnode = tempnode->next;
        tempnode1 = tempnode1->next;
      }
    }
  }
  return 1;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling clear() on NULL List reference\n");
    exit(1);
  }
  Node tempnode1, tempnode = L->front;
  while(tempnode != NULL) {
    tempnode1 = tempnode->next;
    freeNode(&tempnode);
    tempnode = tempnode1;
  }
  L->cursor = NULL;
  L->index = -1;
  L->front = NULL;
  L->back = NULL;
  L->length = 0;
  return;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(1);
  }
  if (length(L) != 0) {
    L->cursor = L->front;
    L->index = 0;
    
  }
  return;
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);
  }
  if (L->length != 0) {
    L->cursor = L->back;
    L->index = length(L) - 1;
  }
  return;
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(1);
  }
  if (L->cursor != NULL && L->cursor != L->front) {
    L->cursor = L->cursor->prev;
    L->index--;
  }
  else if (L->cursor != NULL && L->cursor == L->front) {
    L->cursor = NULL;
    L->index = -1;
  }
  return;
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(1);
  }
  if (L->cursor != NULL && L->cursor != L->back) {
    L->cursor = L->cursor->next;
    L->index++;
  }
  else if (L->cursor != NULL && L->cursor == L->back) {
    L->cursor = NULL;
    L->index = -1;
  }
  return;
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(1);
  }
  Node frontnode = newNode(data);
  if (L->length == 0) {
    L->front = frontnode;
    L->back = frontnode;
  }
  else {
    L->front->prev = frontnode;
    frontnode->next = L->front;
    L->front = frontnode;
  }
  if (index(L) != -1) {
    L->index++;
  }
  L->length++;
  return;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling append() on NULL List reference\n");
    exit(1);
  }
  Node backnode = newNode(data);
  if (L->length == 0) {
    L->front = backnode;
    L->back = backnode;
  }
  else {
    L->back->next = backnode;
    backnode->prev = L->back;
    L->back = backnode;
  }
  L->length++;
  return;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling insertbefore() on NULL List reference\n");
    exit(1);
  }
  if (index(L) == -1) {
    printf("List Error: calling insertbefore() when the cursor is not set\n");
    exit(1);
  }
  Node newnode = newNode(data);
  Node tempnode;
  if (length(L) > 0 && index(L) >= 0) {
    if (index(L) == 0) {
      prepend(L, data);
      freeNode(&newnode);
    }
    else {
      tempnode = L->cursor->prev;
      tempnode->next = newnode;
      L->cursor->prev = newnode;
      newnode->prev = tempnode;
      newnode->next = L->cursor;
      L->length++;
      L->index++;
    }
  }
  return;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
  }
  if (index(L) == -1) {
    printf("List Error: calling insertAfter() when the cursor is not set\n");
    exit(1);
  }
  
  Node newnode = newNode(data);
  Node tempnode;
  if (length(L) > 0 && index(L) >= 0) {
    if (index(L) == length(L) - 1) {
      append(L, data);
      freeNode(&newnode);
    }
    else {
      tempnode = L->cursor->next;
      tempnode->prev = newnode;
      L->cursor->next = newnode;
      newnode->next = tempnode;
      newnode->prev = L->cursor;
      L->length++;
    }
  }
  return;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }
  if (length(L) == 0) {
    printf("List Error: calling deleteFront() on empty List\n");
    exit(1);
  }
  if (L->cursor == L->front) {
    L->cursor = NULL;
    L->index = -1;
  }
  else if (L->cursor != L->front && L->cursor != NULL) {
    L->index--;
  }
  if (length(L) > 0) {
    if (length(L) != 1) {
      Node tempnode = L->front->next;
      tempnode->prev = NULL;
      freeNode(&L->front);
      L->front = tempnode;
    }
    else {
      freeNode(&L->front);
      L->front = NULL;
      L->back = NULL;
    }
    L->length--;
  }
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(1);
  }
  if (length(L) == 0) {
    printf("List Error: calling deleteBack() on empty List\n");
    exit(1);
  }
  if (L->cursor == L->back) {
    L->cursor = NULL;
    L->index = -1;
  }
  if (length(L) > 0) {
    if (length(L) != 1) {
      Node tempnode = L->back->prev;
      tempnode->next = NULL;
      freeNode(&L->back);
      L->back = tempnode;
    }
    else {
      freeNode(&L->back);
      L->front = NULL;
      L->back = NULL;
    }
    L->length--;
  }
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling delete() on NULL List reference\n");
    exit(1);
  }
  if (length(L) == 0) {
    printf("List Error: calling delete() on empty List\n");
    exit(1);
  }
  if (index(L) == -1) {
    printf("List Error: calling delete() when cursor is undefined\n");
    exit(1);
  }
  if (length(L) > 0 && index(L) >= 0) {
    if (L->cursor == L->front) {
      deleteFront(L);
    }
    else if (L->cursor == L->back) {
      deleteBack(L);
    }
    else {
      Node tempnode = L->cursor->prev;
      Node tempnode1 = L->cursor->next;
      tempnode->next = tempnode1;
      tempnode1->prev = tempnode;
      freeNode(&L->cursor);
      L->cursor = NULL;
      L->index = -1;
      L->length--;
    }
  }
  return;
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.

void printList(FILE* out, List L) {
  Node N = NULL;
  // test cases
  if (L == NULL) {
    printf("List Error: calling printList() on NULL List reference\n");
    exit(1);
  }
  for (N = L->front; N != NULL; N = N->next) {
    fprintf(out, "%d ", N->data);
  }
  return;
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
  // test cases
  if (L == NULL) {
    printf("List Error: calling copyList() on NULL List reference\n");
    exit(1);
  }
  List List1 = newList();
  Node N = NULL;
  for (N = L->front; N != NULL; N = N->next) {
    append(List1, N->data);
  }
  List1->length = length(L);
  return List1;
}

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
  List List1;
  List1 = newList();
  List1->front = A->front;
  A->back->next = B->front;
  List1->back = B->back;
  List1->length = length(A) + length(B);
  return List1;
}

