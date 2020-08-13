#ifndef __LL_H__
#define __LL_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include "gs.h"
#include <stdbool.h>

// If flag is set, ListNodes that are qqueried aree moved to the front.
extern bool move_to_front;
extern int seek;
extern int traverse;

//
// Struct definition of a ListNode
//
// gs: GoodSpeak struct containing oldspeak and its newspeak translation.
//
typedef struct ListNode {
  GoodSpeak *gs;
  struct ListNode *next;
} ListNode ;

ListNode *ll_node_create(GoodSpeak *gs);

void ll_node_delete(ListNode *n);

void ll_delete(ListNode *head);

GoodSpeak *ll_node_gs(ListNode *n);

ListNode *ll_insert(ListNode **head, GoodSpeak *gs);

ListNode *ll_lookup(ListNode **head, char *oldspeak);

void ll_node_print(ListNode *n);

void ll_print(ListNode *head);



#endif
