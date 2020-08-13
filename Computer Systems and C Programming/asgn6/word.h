#ifndef __WORD_H__
#define __WORD_H__

#include <inttypes.h>
#include <stdlib.h>

//
// Struct definition of a Word.
//
// syms: A Word holds an array of symbols, stored as bytes in an array.
// len:  Length of the array storing the symbols a Word represents.
//
typedef struct Word {
  uint8_t *syms;
  uint32_t len;
} Word;

//
// Define an array of Words as a WordTable.
//
typedef Word *WordTable;

//
// Constructor for a Word.
//
// syms:    Array of symbols a Word represents.
// len:     Length of the array of symbols.
// returns: Pointer to a Word that has been allocated memory.
Word *word_create(uint8_t *syms, uint32_t len);

//
// Constructs a new Word from the specified Word appended with a symbol.
// The Word specified to append to may be empty.
// If the above is the case, the new Word should contain only the symbol.
//
// w:       Words to append to.
// sym:     Symbol to append.
// returns: New Word which represents the result of appending.
//
Word *word_append_sym(Word *w, uint8_t sym);

//
// Destructor for a Word.
//
// w:       Word to free memory for.
// returns: Void.
//
void word_delete(Word *w);

//
// Creates a new WordTable, which is an array of Words.
// A WordTable has a pre-defined size of MAX_CODE(UINT16_MAX - 1)/
// This is because codes are 16-bit integers.
// A WordTable is initialized with a single Word at index EMPTY_CODE.
// This Word represents the empty word, a string of length of zero.
//
// returns: Initialized WordTable.
WordTable *wt_create(void);

//
// Resets a WordTable to having just the empty Word.
//
// wt:      WordTable to reset.
// returns: Void.
//
void wt_reset(WordTable *wt);

//
// Deletes an entrie WordTable.
// All Words in the WordTable must be deleted as well.
//
// wt:      WordTable to free memory for.
// returns: Void.
//
void wt_delete(WordTable *wt);

#endif
