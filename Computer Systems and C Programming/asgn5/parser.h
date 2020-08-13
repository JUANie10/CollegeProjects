#ifndef __PARSER_H__
#define __PARSER_H__

#include <regex.h>
#include <stdio.h>

//
// Returns the next word that matches the specified regular expression.
// Words are buffered and returned as they are read from the input file.
//
// infile:      The input file to read from.
// word_regex:  The compiled regular expression for a word.
// returns:     The next word if it exists, a null pointer otherwise.
//
char *next_word(FILE *infile, regex_t *word_regex);

//
// Clears out the static word buffer.
//
void clear_words(void);

#endif
