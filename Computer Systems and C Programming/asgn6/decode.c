#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include "io.h"
#include "trie.h"
#include "word.h"
#include "code.h"

uint8_t bit_length(uint16_t code);
void Decompress(int infile, int outfile);

int main(int argc, char **argv) {
  bool stats = false, input = false, output = false;
  struct stat buf, buf1;
  char *inputfile, *outputfile;
  int infile, outfile, errno;
  int c = 0;
  while ((c = getopt(argc , argv , "vi:o:")) !=  -1) {
    //switch statement to read flags
    switch(c) {
      //reading flags
      case 'v':
        stats = true;
        break;
      case 'i':
        input = true;
        inputfile = optarg;
        break;
      case 'o':
        output = true;
        outputfile = optarg;
      default:
        break;
    }
  }
  // Creating the fileheader
  FileHeader *headfile = malloc(sizeof(FileHeader));
  
  // Opening the file and reading the fileheader
  if (input == true) {
    infile = open(inputfile, O_RDONLY);
    fstat(infile, &buf1);
    if (infile == -1) {
      printf("Please enter a valid input file\n");
      perror("Error status");
      exit(1);
    }
    read_header(infile, headfile);
  }
  else {
    infile = STDIN_FILENO;
  }
  
  // opening the outfile.
  if (output == true) {
    outfile = open(outputfile, O_WRONLY);
    if (outfile == -1) {
      printf("\nPlease enter a valid output file\n");
      perror("Error status");
      exit(1);
    }

    fstat(outfile, &buf);
    if (headfile->protection != buf.st_mode) {
      printf("Protection code does not match. Exiting");
      exit(1);
    }
  }
  else {
    outfile = STDOUT_FILENO;
  }
  // Where the magic happens where it decompresses
  Decompress(infile, outfile);
  
  fstat(outfile, &buf);
  if (stats == true) {
    printf("\nCompressed file size: %lld bytes", buf1.st_size);
    printf("\nUncompressed file size: %lld bytes", buf.st_size);
    printf("\nCompression ratio: %lld", 100 * (1 - (buf1.st_size / buf.st_size)));
  }
  
  // Closing the file descriptors
  if (input == true) {
    close(infile);
  }
  if (output == true) {
    close(outfile);
  }
  
  
  free(headfile);
  return 0;
}

// Returns the length of the codes
uint8_t bit_length(uint16_t code) {
  uint8_t length = 0;
  if (code >= 1) {
    length = floor(log10(code) / log10(2)) + 1;
  }
  else if (code == 0) {
    length = 1;
  }
  return length;
}

// Decompresses the infile and returns it into outfile
void Decompress(int infile, int outfile) {
  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;
  while (read_pair(infile, &curr_code, &curr_sym, bit_length(next_code))) {
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    next_code = next_code + 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);
}
