/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA2
* File name:     Arithmetic.c
* File Description: Handles Big Integer computations
*********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "List.h"
#include "BigInteger.h"

#define MAXLINE 1000

void printBIG(BigInteger N);

int main(int argc, char* argv[]) {
  int count = 0;
  FILE *in, *out;

  // check command line for correct number of arguments
  if (argc != 3) {
    printf("Input the following: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  // open files for reading and writing
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  // Printing out error for the in and out files if either are NULL
  if (in == NULL) {
    printf("Unable to open file %s in reading mode\n", argv[1]);
    exit(1);
  }
  if (out == NULL) {
    printf("Unable to open file %s in writing mode\n", argv[2]);
    exit(1);
  }
  // Counting the number of lines within the input file
  
  // Creating an array of the number of lines
  char buffer[MAXLINE+1];
  char buffer2[MAXLINE+1];
  char buffer3
  [MAXLINE+1];
  BigInteger A;
  BigInteger B;
  
  // Getting the lines from the inputfile
  while (fscanf(in, "%s", buffer) != EOF) {
    count++;
    if (count == 2) {
      strcpy(buffer2, buffer);
      A = stringToBigInteger(buffer);
    }
    if (count == 4) {
      strcpy(buffer3, buffer);
      B = stringToBigInteger(buffer3);
    }
  }
  
  BigInteger C = newBigInteger();
  
  // A
  printBigInteger(out, A);
  printBIG(A);
  
  // B
  printBigInteger(out, B);
  printBIG(B);
  
  // A+B
  add(C, A, B);
  printBigInteger(out, C);
  makeZero(C);
  
  // A-B
  subtract(C, A, B);
  printBigInteger(out, C);
  makeZero(C);
  
  // A-A
  subtract(C, A, A);
  printBigInteger(out, C);
  makeZero(C);
  
  // 3A-2B
  BigInteger Ab = stringToBigInteger("+3");
  BigInteger Bc = stringToBigInteger("+2");
  BigInteger Atemp = newBigInteger();
  BigInteger Btemp = newBigInteger();
  multiply(Atemp, Ab, A);
  multiply(Btemp, Bc, B);
  subtract(C, Atemp, Btemp);
  printBigInteger(out, C);
  makeZero(C);
  makeZero(Atemp);
  makeZero(Btemp);
  makeZero(Ab);
  makeZero(Bc);
  
  // A*B
  multiply(C, A, B);
  printBigInteger(out, C);
  makeZero(C);
  
  // A*A
  multiply(C, A, A);
  printBigInteger(out, C);
  makeZero(C);
  
  // B*B
  multiply(C, B, B);
  printBigInteger(out, C);
  makeZero(C);
  
  // 9A^4 + 16B^5
  Ab = stringToBigInteger("+9");
  Bc = stringToBigInteger("+16");
  BigInteger Atemp1 = copy(A);
  BigInteger Btemp1 = copy(B);
  for (long i = 0; i < 4; i++) {
    multiply(Atemp, Atemp, A);
  }
  for (long i = 0; i < 5; i++) {
    multiply(Btemp, Btemp, B);
  }
  multiply(Atemp, Atemp, Ab);
  multiply(Btemp, Btemp, Bc);
  add(C, Atemp, Btemp);
  printBigInteger(out, C);
  
  // Freeing the BigIntegers
  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&Ab);
  freeBigInteger(&Bc);
  freeBigInteger(&Atemp);
  freeBigInteger(&Btemp);
  freeBigInteger(&Atemp1);
  freeBigInteger(&Btemp1);
  
  fclose(in);
  fclose(out);
  
  return 0;

}

void printBIG(BigInteger N) {
  moveFront(N->digits);
  if (sign(N) == -1) {
    printf("-");
  }
  while(index(N->digits) != -1) {
    printf("%ld", get(N->digits));
    moveNext(N->digits);
  }
  printf("\n\n");
}
