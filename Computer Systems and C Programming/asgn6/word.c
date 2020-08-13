#include <stdio.h>
#include "word.h"
#include "code.h"

// creating a new word
Word *word_create(uint8_t *syms, uint32_t len) {
  Word *newword = (Word *) malloc(sizeof(Word));
  newword->syms = syms;
  newword->len = len;
  return newword;
}

// incrementing length and realloating the symbols
Word *word_append_sym(Word *w, uint8_t sym) {
  if (w == NULL) {
    return word_create(&sym, 1);
  }
  else if (w->len == 0) {
    uint32_t newlen = 1;
    return word_create(&sym, newlen);
  }
  else {
    uint32_t newlen = w->len + 1;
    uint8_t *syms = calloc(newlen, sizeof(uint8_t));
    for (uint32_t i = 0; i < w->len; i++) {
      syms[i] = w->syms[i];
    }
    syms[w->len] = sym;
    return word_create(syms, newlen);
  }
}

// freeing the allocated spaces for word
void word_delete(Word *w) {
  free(w->syms);
  w->syms = NULL;
  free(w);
  w = NULL;
  return;
  
}

// Creates a wordtable which is an array of words.
WordTable *wt_create(void) {
  uint8_t *emptysym = NULL;
  Word *emptyword = word_create(emptysym, 0);
  WordTable *newwordtable = (WordTable *) calloc(MAX_CODE-1, sizeof(WordTable));
  newwordtable[EMPTY_CODE] = emptyword;
  return newwordtable;
}

// Resets the wordtable up to the empty word.
void wt_reset(WordTable *wt) {
  int i = EMPTY_CODE + 1;
  while (wt[i] != NULL) {
    word_delete(wt[i]);
    i++;
  }
}

// Deletes the WordTable.
void wt_delete(WordTable *wt) {
  int i = EMPTY_CODE;
  while (wt[i] != NULL) {
    word_delete(wt[i]);
    i++;
  }
  free(wt);
}

