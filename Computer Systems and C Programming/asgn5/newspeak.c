//header files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <regex.h>
#include "gs.h"
#include "ll.h"
#include "hash.h"
#include "parser.h"
#include "bf.h"
#include <strings.h>
#include <errno.h>

bool move_to_front = false;
int seek = 0;
int traverse = 0;
//main function with getopt
int main(int argc, char **argv) {
  //initializing variables
  int c = 0;
  uint32_t hashsize = 10000;
  uint32_t boomsize = 1048576;
  uint32_t movefrontback = 0;
  move_to_front = false;
  //char *inputtemp;
  bool stats = false;
  
  //using getopt
  while ((c = getopt(argc, argv, "sh:f:mb")) !=  -1) {
    //switch statement to read flags
    switch(c) {
      //Gets the file to read
      case 's':
        stats = true;
        break;
      //Sets the hashtable size
      case 'h':
        if (optarg != NULL) {
          hashsize = atoi(optarg);
        }
        else {
          printf("Please Enter a valid size for the HashTable\n");
          exit(1);
        }
        break;
      case 'f':
        //sets the bloomfilter size
        if (optarg != NULL) {
          boomsize = atoi(optarg);
        }
        else {
          printf("Please enter a valid size for the BloomFilter\n");
          exit(1);
        }
        break;
      case 'm':
        //Sets move_to_front
        move_to_front = true;
        movefrontback++;
        if (movefrontback == 2) {
          printf("The flags m and b are not supported\n");
          exit(1);
        }
        break;
      case 'b':
        //sets move_to_front to false
        move_to_front = false;
        movefrontback++;
        if (movefrontback == 2) {
          printf("The flags m and b are not supported\n");
          exit(1);
        }
        break;
      default:
        break;
    }
  }
  //creating a bloomfilter and hashtable in accordance to their sizes
  BloomFilter *bf = bf_create(boomsize);
  HashTable *ht = ht_create(hashsize);
  
  char key11[256];
  char key22[256];
  //Opens newspeak.txt to inserted into bloomfilter and Hashtable
  FILE *new = fopen ("newspeak.txt", "r");
  
  while (fscanf(new, "%s", key11) != -1) {
    fscanf(new, "%s", key22);
    //breaks when end of file has been reached
    if (feof(new)) {
      break;
    }
    
    //insert into bloomfilter
    bf_insert(bf, key11);
    //creates a new goodspeak to insert into the hashtable
    GoodSpeak *newgs = gs_create(key11, key22);
    
    ht_insert(ht, newgs);
    
    //frees the goodspeak struct
    gs_delete(newgs);
  }
  
  //closing file
  fclose(new);
  
  //Opens the Badspeak.txt to set the bloomfilter and the hashtable
  char key[256];
  char *key1 = NULL;
  FILE *baddie = fopen ("badspeak.txt", "r");
  
  //gets the next word
  while (fscanf(baddie, "%s", key) != -1) {
    //insert into the bloomfilter
    
    bf_insert(bf, key);
    //creates a goodspeak struct and inserts it into the hashtable
    GoodSpeak *badgs = gs_create(key, key1);
    ht_insert(ht, badgs);
    
    //frees the goodspeak struct
    gs_delete(badgs);
  }
  //closing file
  fclose(baddie);
  
  
  
  //Opening the inputfile
  //FILE *inputfile = fopen(inputtemp, "r");
  char *inputkey;
  //setting up regular expressions
  regex_t regex1;
  regcomp(&regex1, "[[:alnum:]]+([-'][[:alnum:]]+)?", REG_EXTENDED);

  
  //Booleans to create the start of the linked lsit
  bool firstenter = false;
  bool firstenter1 = false;
  //The Linked Lists
  ListNode *good = NULL;
  ListNode *forbidden = NULL;
  
  
  while (1) {
    //Grabs the next word from stdin
    inputkey = next_word(stdin, &regex1);
    
    if (inputkey == NULL) {
      break;
    }
    //Changes the inputkey to lowercase
    for (int i = 0; inputkey[i]; i++) {
      inputkey[i] = tolower(inputkey[i]);
    }
    //Checks if the bits have been set for that inputkey
    if (bf_probe(bf, inputkey)) {
      seek++;
      ListNode *wordhead = ht_lookup(ht, inputkey);
      
      //Inputs the inputkey into forbidden or good linked list depending on
      // what kind of word it is.
      if (wordhead != NULL) {
        
        if (gs_newspeak(wordhead->gs) == NULL) {
          //creating the linked list for forbidden words
          if (firstenter == false) {
            
            forbidden = ll_node_create(wordhead->gs);
            firstenter = true;
          }
          seek++;
          // Checking if the forbidden word has already been inputed or not
          if (ll_lookup(&forbidden, inputkey) == NULL) {
            forbidden = ll_insert(&forbidden, wordhead->gs);
          }
        }
        else {
          //creating the linked lists for words with translations
          if (firstenter1 == false) {
            
            good = ll_node_create(wordhead->gs);
            firstenter1 = true;
          }
          seek++;
          //checks if the inputkey is in the good linked list already
          if (ll_lookup(&good, inputkey) == NULL) {
            good = ll_insert(&good, wordhead->gs);
          }
        }
      }
    }
  }
  //freeing linked lists and the words
  regfree(&regex1);
  uint32_t bvcount = 0;
  // If the s flag was inputtted
  if (stats == false) {
    //Checks for which message to output
    if (good == NULL) {
      
      if (forbidden != NULL) {
        //Thoughtcrime message
        printf("Dear Comrade,\n\n"
               "You have chosen to use degenerate words that may cause hurt\n"
               "feelings or cause your comrades to think unpleasant thoughts.\n"
               "This is doubleplus bad. To correct your wrongthink and\n"
              "preserve community consensus we will be sending you to joycamp\n"
               "administered by Miniluv.\n\nYour errors:\n\n");
        //printing forbidden words
        ll_print(forbidden);
        
      }
    }
    else {
      if (forbidden == NULL) {
        //encouragement message
        printf("Dear Comrade,\n\n"
               "Submitting your text helps to preserve feelings and prevent\n"
               "badthink. Some of the words that you used are not goodspeak.\n"
               "The list shows how to turn the oldspeak words into newspeak."
               "\n\n");
        //printing words that have newspeak translation
        
        ll_print(good);
      
      }
      else {
        // thoughtcrime and encouragement message
        printf("Dear Comrade,\n\n"
               "You have chosen to use degenerate words that may cause hurt\n"
               "feelings or cause your comrades to think unpleasant thoughts.\n"
               "This is doubleplus bad. To correct your wrongthink and\n"
              "preserve community consensus we will be sending you to joycamp\n" "administered by Miniluv.\n\nYour errors:\n\n");
        //printing forbidden words and words that have newspeak translations
        ll_print(forbidden);
        printf("\nThink of these words on your vacation!\n\n");
        ll_print(good);
        
      }
    }
  }
  // Printing the stats of the computations
  else if (stats == true) {
    printf("\nSeeks: %d\n", seek);
    printf("Average seek length: %f\n", (float)traverse/seek);
    printf("Hash table load: %f\n",  100 * ((float)(
                                             ht_count(ht))/(float)hashsize));
    //Counting the bits that are occupied
    for (uint32_t i = 0; i < boomsize; i++) {
      if (bv_get_bit(bf->filter, i)) {
        bvcount++;
      }
    }
    printf("Bloom filter load: %f\n",  100
           *((float)bvcount/(float)boomsize));
    
  }
  
  //freeing the bloomfilters and listnodes
  if (good != NULL) {
    ll_delete(good);
  }
  if (forbidden != NULL) {
    ll_delete(forbidden);
  }
  
  bf_delete(bf);
  ht_delete(ht);
  return 0;
}
