#include "bubble.h"

//Sorts the array using bubble sort
void Bubble_Sort(uint32_t* arr) {
  uint32_t n = 0;
  uint32_t compare = 0;
  uint32_t swap = 0;
  //counts the size of the array
  while(arr[n] != (uint32_t) NULL) {
    n++;
  }
  n++;
  //Compares the value with the value of one index above and adjusts the array
  // accordingly. Starting from the first index compares with second index
  for (uint32_t i = 0; i < n-1; i++) {
    uint32_t j = n-1;
    while (j > i) {
      compare++;
      if (arr[j] < arr[j-1]) {
        swap++;
        uint32_t temp = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = temp;
      }
      j -= 1;
    }
  }
  //print statements
  printf("Bubble Sort\n");
  printf("%d elements, %d moves, %d compares\n", n-1, swap, compare);
  return;
}
