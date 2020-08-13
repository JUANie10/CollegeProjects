/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA2
* File name:     BigIntegerTest.c
* File Description: My personal test on BigInteger prototype
*********************************************************************************/


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "List.h"
#include "BigInteger.h"

int main(void) {
  
  
  
  
  
  BigInteger pA;
  
  BigInteger pB;
  BigInteger pC = newBigInteger();
  pA = stringToBigInteger("111122223333");
  pB = stringToBigInteger("-112122223333");
  //A-> -111122223333
  //*pB = stringToBigInteger("+111122223333");

  multiply(pA, pA, pB);
  
  printf("sign(pA) = %d\n", sign(pA));
  printf("sign(pB) = %d\n", sign(pB));
  printf("sign(pC) = %d\n", sign(pC));
  printf("pA: ");
  moveFront(pA->digits);
  while (index(pA->digits) != -1) {
    printf("%ld ", get(pA->digits));
    moveNext(pA->digits);
  }
  printf("\n");
  
  exit(1);
  
  pA = stringToBigInteger("-333333333333");
  
  printf("pA: ");
  moveFront(pA->digits);
  while (index(pA->digits) != -1) {
    printf("%ld ", get(pA->digits));
    moveNext(pA->digits);
  }
  printf("\n");

  printf("length: pC: %ld, pA: %ld\n", length(pC->digits), length(pA->digits));
  printf("compare(pA, pC) = %d\n", compare(pA, pC));
  exit(1);
  
  pB = stringToBigInteger("+222211110000");
  pC = newBigInteger();

  //pos + pos = pos
  //BigInteger pD = stringToBigInteger("+333333333333");
  add(pC, pA, pB);
  
  
 
  
  printf("pC: ");
  moveBack(pC->digits);
  while (index(pC->digits) != -1) {
    printf("%ld", get(pC->digits));
    movePrev(pC->digits);
  }
  printf("\n");
  /*
  printf("pD: ");
  moveBack(pD->digits);
  while (index(pD->digits) != -1) {
    printf("%ld", get(pD->digits));
    movePrev(pD->digits);
  }
  printf("\n");
  printf("%d\n", compare(pD,pC));
  exit(1);
  
  
  if (!equals(pC, pD)) {
    printf("1");
  }
  
  */
  return 0;
}
