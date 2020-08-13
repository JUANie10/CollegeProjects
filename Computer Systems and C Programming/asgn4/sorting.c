//header files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include "bubble.h"
#include "shell.h"
#include "quick.h"
#include "binary.h"

//declaration
uint32_t* array_create(uint32_t seed, uint32_t size);

//main function with getopt
int main(int argc, char **argv) {
  //initializing variables
  int c = 0;
  bool all = false;
  bool bubble = false;
  bool shell = false;
  bool quick = false;
  bool binary = false;
  uint32_t print = 100;
  uint32_t seed = 8222022;
  uint32_t size = 100;
  //using getopt
  while ((c = getopt(argc , argv , "Absqip:r:n:")) !=  -1) {
    //switch statement to read flags
    switch(c) {
      //reading which sorts to do 
      case 'A':
        all = true;
        break;
      case 'b':
        bubble = true;
        break;
      case 's':
        shell = true;
        break;
      case 'q':
        quick = true;
        break;
      case 'i':
        binary = true;
        break;
      case 'p':
        //storing the optarg into print
        if (optarg != NULL) {
          print = atoi(optarg);
        }
        break;
      case 'r':
        //storing the optarg into seed
        if (optarg != NULL) {
          seed = atoi(optarg);
        }
        break;
      case 'n':
        //storing the optarg into size
        if (optarg != NULL) {
          size = atoi(optarg);
        }
        break;
      default:
        break;
    }
  }
  
  //sets the values of the print if the print is bigger than size
  if (size < print) {
    print = size;
  }
  
  if (all == true) {
    bubble = true;
    shell = true;
    quick = true;
    binary = true;
  }
  //creating an array calling bubble sort
  if (bubble == true) {
    uint32_t* array = array_create(seed, size);
    Bubble_Sort(array);
    uint32_t count = 0;
    //printing the values
    for (uint32_t i=1; i<=print; i++) {
      printf("\t%d", array[i]);
      count++;
      if (count == 7) {
        count = 0;
        printf("\n");
      }
    }
    printf("\n");
    //freeing the array
    if (array != NULL) {
      free(array);
      array = NULL;
    }
  }
  //creating an array calling shell sort
  if (shell == true) {
    uint32_t* array2 = array_create(seed, size);
    Shell_Sort(array2);
    uint32_t count = 0;
    //printing the values
    for (uint32_t i=0; i<print; i++) {
      printf("\t%d", array2[i]);
      count++;
      if (count == 7) {
        count = 0;
        printf("\n");
      }
    }
    printf("\n");
    //freeing the array
    if (array2 != NULL) {
      free(array2);
      array2 = NULL;
    }
  }
  //creating an array calling quick sort
  if (quick == true) {
    uint32_t* array3 = array_create(seed, size);
    Quick_Sort(array3, 0, (int) size-1);
    uint32_t count = 1;
    //printing the values
    printf("\t%d", array3[0]);
    for (uint32_t i=1; i<print; i++) {
      printf("\t%d", array3[i]);
      count++;
      if (count == 7) {
        count = 0;
        printf("\n");
      }
    }
    printf("\n");
    //freeing the array
    if (array3 != NULL) {
      free(array3);
      array3 = NULL;
    }
  }
  //creating an array calling binary insertion sort
  if (binary == true) {
    uint32_t* array1 = array_create(seed, size);
    Binary_Insertion_Sort(array1);
    uint32_t count = 0;
    //printing the values
    for (uint32_t i=1; i<print+1; i++) {
      printf("\t%d", array1[i]);
      count++;
      if (count == 7) {
        count = 0;
        printf("\n");
      }
    }
    printf("\n");
    //freeing the array
    if (array1 != NULL) {
      free(array1);
      array1 = NULL;
    }
  }
  
  return 0;
}

//creates an array with the correct size and returns it
uint32_t* array_create(uint32_t seed, uint32_t size) {
  //initializing the seed
  srand(seed);
  uint32_t* array = calloc(size+1, sizeof(uint32_t));
  for (uint32_t i = 0; i<size; i++) {
    //inputing 30 bit random numbers into the array
    uint32_t u = rand();
    array[i] = u & 0x3FFFFFFF;
  }
  return array;
}
