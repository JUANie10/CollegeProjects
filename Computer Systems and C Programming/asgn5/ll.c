#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"
#include "gs.h"

//
// Stuct definition of a ListNode
//
// gs: GoodSpeak struct containing oldspeak and its newspeak translation .
//



//
// Constructor for a ListNode.
//
// gs: GoodSpeak struct containing oldspeak and its newspeak translation.
//
ListNode *ll_node_create(GoodSpeak *gs) {
  ListNode *newlistnode = (ListNode*) malloc(sizeof(ListNode)+1);
 
  newlistnode->gs = gs_create(gs_oldspeak(gs), gs_newspeak(gs));
  
  newlistnode->next = NIL;
  return newlistnode;
}

//
// Destructor for a ListNode.
//
// n: The ListNode to free
//
void ll_node_delete(ListNode *n) {
  
  gs_delete(n->gs);
  free(n);
  return;
}

//
// Destructor for a linked list of ListNodes.
//
// head: The head of the linked list.
//
void ll_delete(ListNode *head) {
  while(head != NULL) {
    ListNode *temp = head->next;
    ll_node_delete(head);
    head = temp;
  }
}

//
// Creates and inserts a ListNode into a linked list.
//
// head: The head of the linked list to insert in.
// gs: GoodSpeak struct.
//
ListNode *ll_insert(ListNode **head, GoodSpeak *gs) {
  
  ListNode *new_head = ll_node_create(gs);
  new_head->next = *(head);
  *(head) = new_head;
  
  return *head;
}

//
// Searches for a specific key in a linked list.
// Returns the ListNode if found and NULL otherwise.
//
// head: The head of the linked list to search in.
// key: The key to search for.
//
ListNode *ll_lookup(ListNode **head, char *key) {
  seek++;
  if (*head != NULL) {
    ListNode *temp = *head;
    ListNode *tempprev = *head;
    while (temp != NULL && strcmp(gs_oldspeak(temp->gs), key)) {
      if (move_to_front) {
        tempprev = temp;
        temp = temp->next;
        traverse++;
      }
      else {
        temp = temp->next;
        traverse++;
      }
    }
    if (move_to_front) {
      tempprev->next = temp->next;
      ll_insert(head, temp->gs);
      
    }
    return temp;
  }
  return (ListNode *) NIL;
}

//
// Prints the listnode n.
//
// n: the listnode you want to print out.
//
void ll_node_print(ListNode *n) {
  
  if (gs_newspeak(n->gs) != NULL) {
    printf("%s -> %s\n", gs_oldspeak(n->gs), gs_newspeak(n->gs));
  }
  else {
    printf("%s\n", gs_oldspeak(n->gs));
  }
  return;
}

//
// Prints the linked list of list nodes.
//
// head: The pointer where the head of the linked lists is stored
//
void ll_print(ListNode *head) {
  
  while (head != NULL) {
    ll_node_print(head);
    head = head->next;
  }
  return;
}

//
// Returns the goodspeak struct of the node
//
// n: The ListNode
GoodSpeak *ll_node_gs(ListNode *gs) {
  return gs->gs;
}
