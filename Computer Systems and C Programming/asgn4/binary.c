#include "binary.h"

//Sorts the array using Binary Insertion Sort
void Binary_Insertion_Sort(uint32_t* arr) {
  uint32_t n = 0;
  uint32_t swap = 0;
  uint32_t compare = 0;
  //counting the sizee of the array
  while(arr[n] != (uint32_t) NULL) {
    n++;
  }
  n++;
  //for loop for going through the array
  for(uint32_t i=0; i<n; i++) {
    uint32_t value = arr[i];
    uint32_t left = 0;
    uint32_t right = i;
    compare++;
    //compares the value with the right side of the array and the left
    while(left < right) {
      uint32_t mid = left + ((right - left)/2);
      compare++;
      if (value >= arr[mid]) {
        left = mid+1;
      }
      else {
        right = mid;
      }
    }
    //moves a array value one index up and swaps the ccontents in it
    for(uint32_t j=i; j>left; j--) {
      compare++;
      swap++;
      uint32_t temp = arr[j-1];
      arr[j-1] = arr[j];
      arr[j] = temp;
    }
  }
  //printing statements
  printf("Binary Insertion Sort\n");
  printf("%d elements, %d moves, %d compares\n", n-1, swap, compare);
  
  return;
}
