#ifndef __TRIE_H__
#define __TRIE_H__

#include <inttypes.h>
#include <stdlib.h>
#include "code.h"

#define ALPHABET 256

typedef struct TrieNode TrieNode;

//
// Struct definition of a TrieNode.
//
// children: Each TrieNode has ALPHABET number of children.
// code:     Uinque code for a TrieNode.
struct TrieNode {
  TrieNode *children[ALPHABET];
  uint16_t code;
};

//
// Constructor for a TrieNode.
//
// code:    Code of the constructed TrieNode.
// returns: Pointer to a TrieNode that has been allocated memory.
//
TrieNode *trie_node_create(uint16_t code);

//
// Destructor for a TrieNode
//
// n:       TrieNode to free allocated memory for.
// returns: Void.
//
void trie_node_delete(TrieNode *n);

//
// Initializes a Trie: a root TrieNode with the code EMPTY_CODE.
//
// returns: Pointer to the root of a Trie.
//
TrieNode *trie_create(void);

//
// Resets a Trie to just the root TrieNode.
//
// root: Root for the Trie to reset.
// returns: Void.
//
void trie_reset(TrieNode *root);

//
// Deletes a sub-Trie starting from the sub-Trie's root.
//
// n:       Root of the sub-Trie to delete.
// returns: Void.
//
void trie_delete(TrieNode *n);

//
// Returns a pointer to the child TrieNode representing the symbol sym.
// If the symbol doesn't exist, NULL is returned.
//
// n:       TrieNode to step from.
// sym:     Symbol to check for.
// returns: Pointer to the TrieNode representing the symbol.
TrieNode *trie_step(TrieNode *n, uint8_t sym);

#endif
