/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA6
* File name:     DictionaryTest.c
* File Description: Dictionary ADT Tests
*********************************************************************************/
#include "Dictionary.h"
#include <stdio.h>


int main(void) {
  Dictionary B = newDictionary(0);
  
  int *pI[8];
  pI[8] = (int*) 8;
  pI[2] = (int*) 2;
  pI[3] = (int*) 3;
  pI[4] = (int*) 4;
  pI[5] = (int*) 5;
  pI[6] = (int*) 6;
  pI[7] = (int*) 7;
  pI[0] =  (int*) 10;
  pI[1] = (int*) 1;
  
  insert(B, "a", pI[2]);
  insert(B, "d", pI[0]);
  insert(B, "d", pI[1]);
  beginForward(B);
  printf("node: %s, %p\n", currentKey(B), currentVal(B));
  printf("lookup results: %p == 0\n", lookup(B, "d"));
  next(B);
  printf("node: %s, %p\n", currentKey(B), currentVal(B));
  printf("lookup results: %p == 0\n", lookup(B, "d"));
  next(B);
  printf("lookup results: %p == 0\n", lookup(B, "d"));
  printf("node: %s, %p\n", currentKey(B), currentVal(B));

  
  insert(B, "d", pI[0]);
  insert(B, "e", pI[1]);
  insert(B, "f", pI[2]);
  beginForward(B);
  next(B);
  next(B);
  printf("lookup results next: %p\n", lookup(B, "d"));
  prev(B);
  prev(B);
  printf("lookup results prev: %p\n", lookup(B, "d"));
  insert(B, "d", pI[3]);
  insert(B, "d", pI[4]);
  insert(B, "d", pI[5]);
  insert(B, "d", pI[6]);
  insert(B, "d", pI[7]);
  delete(B, "d");
  delete(B, "d");
  findKey(B, B->root, "d");
  printf("lookup results: %p == 3\n", lookup(B, "d"));
  printf("B results: size(B) = %d unique(B) = %d\n", size(B), getUnique(B));
  leftRotate(B, B->root);
  rightRoatate(B, B->root);
  printf("B->root = %s %p\n", B->root->key, B->root->val);
  
  
  freeDictionary(&B);
  
  
  Dictionary A = newDictionary(1);
  pI[2] = (int*) 2;
  pI[3] = (int*) 3;
  pI[4] = (int*) 4;
  pI[5] = (int*) 5;
  pI[6] = (int*) 6;
  
  pI[0] =  (int*) 8;
  pI[1] = (int*) 1;
  
  insert(A, "m", pI[0]);
  insert(A, "n", pI[1]);
  insert(A, "o", pI[2]);
  insert(A, "p", pI[3]);
  insert(A, "q", pI[4]);
  insert(A, "f", pI[5]);
  insert(A, "e", pI[6]);
  
  VAL_TYPE i = beginForward(A);
  printf("bf = %p\n", i);
  next(A);
  printf("next node: %s, %p\n", currentKey(A), currentVal(A));
  next(A);
  printf("next node: %s, %p\n", currentKey(A), currentVal(A));
  next(A);
  printf("next node: %s, %p\n", currentKey(A), currentVal(A));
  next(A);
  printf("next node: %s, %p\n", currentKey(A), currentVal(A));
  next(A);
  printf("next node: %s, %p\n", currentKey(A), currentVal(A));
  next(A);
  printf("next node: %s, %p\n", currentKey(A), currentVal(A));
  
  insert(A, "a", VAL_UNDEF);
  insert(A, "b", VAL_UNDEF);
  insert(A, "c", VAL_UNDEF);
  insert(A, "d", VAL_UNDEF);
  insert(A, "e", VAL_UNDEF);
  printf("size(A) = %d\n", size(A));
  delete(A, "a");
  printf("size(A) = %d\n", size(A));
  insert(A, "f", VAL_UNDEF);
  delete(A, "e");
  printf("size(A) = %d\n", size(A));
  freeDictionary(&A);
  return 0;
}
