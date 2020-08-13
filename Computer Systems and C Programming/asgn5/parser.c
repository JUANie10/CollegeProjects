#include "parser.h"
#include <regex.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Code by DDEL
#define BLOCK   4096

static char *words[BLOCK] = { NULL };  // Stores a block of words maximum.

//
// Returns the next word that matches the specified regular expression.
// Words are buffered and returned as they are read from the input file.
//
// infile:      The input file to read from.
// word_regex:  The compiled regular expression for a word.
// returns:     The next word if it exists, a null pointer otherwise.
//
char *next_word(FILE *infile, regex_t *word_regex) {
  static uint32_t index = 0;  // Track the word to return.
  static uint32_t count = 0;  // How many words have we stored?

  if (!index) {
    clear_words();

    regmatch_t match;
    uint32_t matches = 0;
    char buffer[BLOCK] = { 0 };

    while (!matches) {
      if (!fgets(buffer, BLOCK, infile)) {
        return NULL;
      }

      char *cursor = buffer;

      for (uint16_t i = 0; i < BLOCK; i += 1) {
        if (regexec(word_regex, cursor, 1, &match, 0)) {
          break;  // Couldn't find a match.
        }

        if (match.rm_so < 0) {
          break;  // No more matches.
        }

        uint32_t start  = (uint32_t)match.rm_so;
        uint32_t end    = (uint32_t)match.rm_eo;
        uint32_t length = end - start;

        words[i] = (char *)calloc(length + 1, sizeof(char));
        if (!words[i]) {
          perror("calloc");
          exit(1);
        }

        memcpy(words[i], cursor + start, length);
        cursor += end;
        matches += 1;
      }

      count = matches;  // Words stored is number of matches.
    }
  }

  char *word = words[index];
  index = (index + 1) % count;
  return word;
}

//
// Clears out the static word buffer.
//
void clear_words(void) {
  for (uint16_t i = 0; i < BLOCK; i += 1) {
    if (words[i]) {
      free(words[i]);
      words[i] = NULL;
    }
  }

  return;
}
