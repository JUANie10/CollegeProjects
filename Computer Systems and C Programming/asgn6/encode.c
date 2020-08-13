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
void Compress(int infile, int outfile);

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
  
  if (input == true) {
    infile = open(inputfile, O_RDONLY);
    fstat(infile, &buf);
    if (infile == -1) {
      printf("Please enter a valid file\n");
      perror("Error status");
    }
  }
  else {
    infile = STDIN_FILENO;
  }
  // Creates a headfile to write to the outfile
  FileHeader *headfile = malloc(sizeof(FileHeader));
  
  // Openign the outfile
  if (output == true) {
    headfile->magic = MAGIC;
    
    outfile = open(outputfile, O_WRONLY);
    

    fstat(outfile, &buf);
    
    headfile->magic = 0x8badbeef;
    
    headfile->protection = buf.st_mode;
    printf("%d", headfile->protection);
    
    write_header(outfile, headfile);
  }
  else {
    outfile = STDOUT_FILENO;
  }
  
  
  // Where the magic happens where it compresses
  Compress(infile, outfile);
  
  fstat(outfile, &buf);
  
  if (stats == true) {
    printf("\nCompressed file size: %lld bytes", buf.st_size);
    printf("\nUncompressed file size: %lld bytes", buf1.st_size);
    printf("\nCompression ratio: %lld", 100 * (1 - (buf1.st_size / buf.st_size)));
  }
  
  // Closing the file descriptors
  if (input == true) {
    close(infile);
  }
  if (output == true) {
    close(outfile);
  }
  
  // Freeing allocated memory
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

// Compresses the infile and returns it into outfile
void Compress(int infile, int outfile) {
  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;
  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;
  
  while (read_sym(infile, &curr_sym) == true) {
    
    TrieNode *next_node = trie_step(curr_node, curr_sym);
    
    if (next_node != NULL) {
      prev_node = curr_node;
      curr_node = next_node;
    }
    else {
      buffer_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
      
      curr_node->children[curr_sym] = trie_node_create(next_code);
      curr_node = root;
      next_code = next_code + 1;
    }
    
    if (next_code == MAX_CODE) {
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
    prev_sym = curr_sym;
    
  }
  
  if (curr_node != root) {
    buffer_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }
  buffer_pair(outfile, STOP_CODE, 0, bit_length(next_code));
  flush_pairs(outfile);
}
