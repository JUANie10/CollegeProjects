#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "hash.h"


//
// Constructor for a HashTable.
//
// length: Length of the HashTable.
// sale: Salt for the HashTable.
//
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable)+1);
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3; // Il nome della rosa
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *)+1);
    return ht;
  }
  return (HashTable *) NIL;
}

//
// Destructor for a HashTable.
//
// ht: The HashTable.
//
void ht_delete(HashTable *ht) {
  for (uint32_t i = 0; i < ht->length; i++) {
    if (ht->heads[i] != NULL) {
      ll_delete(ht->heads[i]);
    }
  }
  free(ht);
  return;
}

//
// Searches a HashTable for a key.
// Returns the ListNode if found and return NULL otherwise.
// This should call thee ll_loopup() function.
//
// ht: The HashTable.
// key: The key to search for.
//
ListNode *ht_lookup(HashTable *ht, char *key) {
  
  uint32_t hashindex = hash(ht->salt, key) % ht->length;
  if (ht->heads[hashindex] != NULL) {
    if (ll_lookup(&ht->heads[hashindex], key) != NULL) {
      
      return ll_lookup(&ht->heads[hashindex], key);
    }
    
  }
  
  return NULL;
  
}

//
// First creates a new ListNode from GoodSpeak.
// The created ListNode is then inserted into a HashTable.
// This should call the ll_insert() function.
//
// ht: The HashTable.
// gs: The GoodSpeak to add to the Hashtable.
//
void ht_insert(HashTable *ht, GoodSpeak *gs) {
  ListNode *insertnode = ll_node_create(gs);
  uint32_t hashindex = hash(ht->salt, gs_oldspeak(gs));
  uint32_t index = hashindex % ht->length;
  
  if (ht->heads[index] == NULL) {
    
    ht->heads[index] = insertnode;
    
  }
  else {
    ll_insert(&ht->heads[index], insertnode->gs);
  }
  return;
}

//
// Counts the number of heads within the HashTable
//
// ht: The HashTable.
//
uint32_t ht_count(HashTable *h) {
  uint32_t count = 0;
  for (uint32_t i = 0; i < h->length; i++) {
    if (h->heads[i] != (ListNode*) NIL) {
      count++;
    }
  }
  return count;
}

//
// Prints the Values within the HashTable.
//
// ht: The HashTable.
//
void ht_print(HashTable *h) {

  for (uint32_t i = 0; i < h->length; i++) {
    if (h->heads[i] != (ListNode *) NIL) {
      ll_print(h->heads[i]);
    }
  }
}
