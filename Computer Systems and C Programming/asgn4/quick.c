#include "quick.h"

//global variables
uint32_t swap = 0;
uint32_t compare = 0;
bool print = false;

//returns the pivot of the array
uint32_t Partition(uint32_t* arr, int left, int right) {
  uint32_t pivot = arr[left];
  int lo = left + 1;
  int hi = right;
  // finding the best pivot point by not choosing an extreme
  while(1) {
    while (lo <= hi && arr[hi] >= pivot) {
      hi -= 1;
    }
    while (lo <= hi && arr[lo] <= pivot) {
      lo += 1;
    }
    compare++;
    //swapings the values of the array
    if (lo <= hi) {
      swap++;
      uint32_t temp = arr[lo];
      arr[lo] = arr[hi];
      arr[hi] = temp;
    }
    else {
      break;
    }
  }
  swap++;
  uint32_t temp = arr[left];
  arr[left] = arr[hi];
  arr[hi] = temp;
  //returns the pivot
  return hi;
}

//sorts an array using quick sort
void Quick_Sort(uint32_t* arr, int left, int right) {
  int index;
  if (left < right) {
    //storing the pivot into index and recusively calling quick sort
    index = Partition(arr, left, right);
    Quick_Sort(arr, left, index-1);
    Quick_Sort(arr, index+1, right);
  }
  int n = 0;
  //counting the size of the array
  while(arr[n] != (uint32_t) NULL) {
    n++;
  }
  //print statement
  if (left == 0 && right == n-1) {
    printf("Quick Sort\n");
    printf("%d elements, %d moves, %d compares\n", n, swap, compare);
  }

  return;
}
