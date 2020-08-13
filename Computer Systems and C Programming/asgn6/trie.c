#include "trie.h"

// Creates a trie node
TrieNode *trie_node_create(uint16_t code) {
  TrieNode *newtrienode = (TrieNode *) malloc(sizeof(TrieNode));
  newtrienode->code = code;
  for (int i = 0; i < 256; i++) {
    newtrienode->children[i] = NULL;
  }
  return newtrienode;
}

// deletes a trie node
void trie_node_delete(TrieNode *n) {
  for (int i = 0; i < 256; i++) {
    n->children[i] = NULL;
  }
  if (n != NULL) {
    free(n);
    n = NULL;
  }
}

// Creates a trie
TrieNode *trie_create(void) {
  TrieNode *roottrienode = trie_node_create(EMPTY_CODE);
  return roottrienode;
}

// Resets a trie to just the root trie node
void trie_reset(TrieNode *root) {
  uint8_t childindex[256];
  uint8_t count = 0;
  TrieNode *current = root;
  
  for (int i = 0; i < 256; i++) {
    if (current->children[i] != NULL) {
      childindex[count] = i;
      count++;
    }
  }
  for (int j = 0; j <= count; j++) {
    trie_delete(current->children[childindex[j]]);
  }
}

// Deletes the trie entirely
void trie_delete(TrieNode *n) {
  uint8_t childindex[256];
  uint8_t count = 0;
  TrieNode *current = n;
  // Counts the amount of children nodes
  for (int i = 0; i < 256; i++) {
    if (current->children[i] != NULL) {
      childindex[count] = i;
      count++;
    }
  }
  // Deletes all the children nodes
  for (int j = 0; j <= count; j++) {
    trie_delete(current->children[childindex[j]]);
  }
  trie_node_delete(current);
}

// Returns the trie node that represents the symbol sym.
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  if (n->children[sym] != NULL) {
    return n->children[sym];
  }
  else {
    return NULL;
  }
  return NULL;
}
