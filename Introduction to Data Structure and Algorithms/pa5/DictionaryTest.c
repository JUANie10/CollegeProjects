/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA5
* File name:     DictionaryTest.c
* File Description: Dictionary ADT Tests
*********************************************************************************/
#include "Dictionary.h"
#include <stdio.h>


int main(void) {
  Dictionary A = newDictionary(1);
  
  // Tests for Next
  insert(A, "a", 2);
  insert(A, "b", 7);
  insert(A, "c", 17);
  insert(A, "d", 154);
  insert(A, "e", 3114);
  beginForward(A);
  next(A);
  next(A);
  printf("%s %d\n", currentKey(A), currentVal(A));
  next(A);
  next(A);
  next(A);
  printf("%s %d\n", currentKey(A), currentVal(A));
  
  // Tests for BeginFowards
  insert(A, "d", 2);
  insert(A, "b", 7);
  insert(A, "c", 12);
  insert(A, "f", 166);
  insert(A, "e", 3214);
  beginForward(A);
  printf("%d %d\n", beginForward(A), currentVal(A));
  delete(A, "b");
  next(A);
  next(A);
  next(A);
  printf("%d %d\n", beginForward(A), currentVal(A));
  
  // testing Insert
  insert(A, "c", 3);
  insert(A, "b", 2);
  insert(A, "a", 1);
  beginForward(A);
  printf("currentKey(A) == %s, currentVal(A) = %d, size(A) = %d\n", currentKey(A), currentVal(A), size(A));
  makeEmpty(A);
  printf("currentKey(A) == %s, currentVal(A) = %d, size(A) = %d\n", currentKey(A), currentVal(A), size(A));
  
  // Testing insert size
  insert(A, "a", 1);
   printf("size(A) == %d\n", size(A));
  insert(A, "b", 3);
   printf("size(A) == %d\n", size(A));
  insert(A, "c", 4);
   printf("size(A) == %d\n", size(A));
  insert(A, "e", 5);
  printf("size(A) == %d\n", size(A));
  
  return 0;
}
