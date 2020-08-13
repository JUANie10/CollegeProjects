#include "shell.h"

//returns a array of gaps
uint32_t* gap(uint32_t n) {
  //Since we don't know the size of the array initially, I created a test
  //array
  uint32_t* testarray = calloc(100, sizeof(uint32_t));
  int p = 0;
  int index = 0;
  //inserting gaps into the testarray
  while (n > 1) {
    if (n <= 2) {
      n = 1;
      testarray[p] = n;
    }
    else {
      n = (5*n)/11;
      testarray[p] = n;
      p++;
    }
  }
  //find the size of the test array
  while (testarray[index] != (uint32_t) NULL) {
    index++;
  }
  //creates a new array to store the values of gaps with the right size
  uint32_t* array = calloc(index+1, sizeof(uint32_t));
  for (int i=0; i<index; i++) {
    array[i] = testarray[i];
  }
  //frees the test array
  if (testarray != NULL) {
    free(testarray);
    testarray = NULL;
  }
  return array;
}

//sorts the array using shell sort
void Shell_Sort(uint32_t* arr) {
  uint32_t n = 0;
  uint32_t swap = 0;
  uint32_t compare = 0;
  //finding the size of the array
  while(arr[n] != (uint32_t) NULL) {
    n++;
  }
  uint32_t* v = gap(n);
  uint32_t u = 0;
  //finding the size of the gap array
  while(v[u] != (uint32_t) NULL) {
    u++;
  }
  //sorting the array by placing the elements in the right places using the
  // gap array to know which index to place into
  for (uint32_t i = 0; i < u; i++) {
    for (uint32_t k = v[i]; k < n; k++) {
      for (uint32_t j = k; j > v[i]-1; j--) {
        compare++;
        if (arr[j] < arr[j - v[i]]) {
          swap++;
          uint32_t temp = arr[j];
          arr[j] = arr[j - v[i]];
          arr[j - v[i]] = temp;
        }
      }
    }
  }
  //print statements
  printf("Shell Sort\n");
  printf("%d elements, %d moves, %d compares\n", n, swap, compare);
  //freeing the gap array
  if (v != NULL) {
    free(v);
    v = NULL;
  }
  return;
}
