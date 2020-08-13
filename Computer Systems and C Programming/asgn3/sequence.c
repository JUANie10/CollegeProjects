//header files
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include "sieve.h"

//declarations
uint32_t nexfib(uint32_t n);
uint32_t nexluc(uint32_t n);
bool mersenne(uint32_t n);
void isinterest(BitVector *v);
bool isPalindrome(char* s);
char* tobase(uint32_t n, int base);
void pcase(BitVector* v);


int main(int argc, char **argv) {
  
  BitVector* prime = NULL;
  bool interest = false, palin = false;
  int c = 0;
  int num = 1000;
  
  while ((c = getopt(argc, argv, "psn:")) != -1) {
    switch(c) {
      case 's':
        //turns the interest boolean true to know to print the interesting
        //primes
        interest = true;
        break;
      case 'p':
        //turns the palin boolean true to know to print the palindrome primes
        palin = true;
        break;
      case 'n':
        //store the number of primes in integer num
        num = atoi(optarg);
        if (num == 0) {
          //throws an error message if nothing has been entered
          printf("Error: Please enter a valid 'n' value\n");
        }
        break;
      default:
        break;
    }
  }
  //creating the bit vector
  prime = bv_create(num);
  //setting all the prime indexes to one by calling sieve on it
  sieve(prime);
  if (interest) {
    //printing the interesting primes
    isinterest(prime);
  }
  if (palin) {
    //printing the palindrome primes
    pcase(prime);
  }
  bv_delete(prime);
  return 0;
}

//returns the next fibonacii number
uint32_t nexfib(uint32_t n) {
  //starting with 1 and 0
  uint32_t t1 = 1, t0 = 0, nextnum = 0;
  while (nextnum < n) {
    //adding the previous two integers to make the fibonacci number
    nextnum = t1 + t0;
    t0 = t1;
    t1 = nextnum;
  }
  return nextnum;
}

//returns the next lucas prime number
uint32_t nexluc(uint32_t n) {
  //starting with 1 and 2
  uint32_t t1 = 1, t0 = 2, nextnum = 0;
  while (nextnum < n) {
    //adding the previous two integers to make a lucas number
    nextnum = t1 + t0;
    t0 = t1;
    t1 = nextnum;
  }
  return nextnum;
}

//returns true if the integer n is a mersenne prime and false otherwise
bool mersenne(uint32_t n) {
  for (uint32_t i = 0; i < n; i++) {
    uint32_t v = i+1;
    uint32_t p2 = 2;
    //power of two for loop
    for (uint32_t a = 0; a < v; a++) {
      p2 *= 2;
    }
    if (p2-1 > n) {
      return false;
    }
    else if (p2-1 == n) {
      return true;
    }
  }
  return false;
}

//prints out if the digit is a mersenne, lucas or fibonacci prime
void isinterest(BitVector *v) {
  //check if for the prime numbers
  for (uint32_t i = 0; i < bv_get_len(v); i++) {
    if (bv_get_bit(v, i) == 1) {
      printf("%d: prime", i);
      //checking if its a mersenne prime
      if (mersenne(i)) {
        printf(", mersenne");
      }
      //checking if its a lucas prime
      if (nexluc(i) == i) {
        printf(", lucas");
      }
      //checking if its a fibonacci prime
      if (nexfib(i) == i) {
        printf(", fibonacci");
      }
      //print a new line
      printf("\n");
    }
  }
}

//checks if a character array is a palindrome
bool isPalindrome(char* s) {
  bool f = true;
  //for the squareroot of the string length, compares it to the negative index
  // with the regular index
  for (int i = 0; i <= (int) (strlen(s)/2); i++) {
    if (s[i] != s[strlen(s)-i-1]) {
      f = false;
    }
  }
  return f;
}

//changes a value into any base number
char* tobase(uint32_t u, int base) {
  //creating space for the character array to put the values into
  char* based = malloc(64);
  char* tempc = malloc(64);
  uint32_t remainder = 0;
  bool asci = false;
  //checks if the value should be converted to a ascii value
  if (base > 10 && u > 10) {
    asci = true;
  }
  while (u != 0) {
    //base conversion
    remainder = u%base;
    u /= base;
    //converts to ascii and puts the remainder into tempc
    if (asci == true && remainder >= 10) {
      remainder += 87;
      sprintf(tempc, "%c", remainder);
    }
    //puts the remainder into tempc
    else {
      sprintf(tempc, "%d", remainder);
    }
    //concatinates the tempc in to char* based
    strcat(based, tempc);
  }
  return based;
}

//prints out all the palindrome primes
void pcase(BitVector* v) {
  // bases of the primes to print
  int bases[] = {2, 10, 14, 24};
  //checks for palindrone primes for each base and prints if its true
  for (int p = 0; p < 4; p++) {
    //prints the header for the bases
    printf("Base %d\n", bases[p]);
    printf("---- --\n");
    for (uint32_t i = 0; i < bv_get_len(v); i++) {
      //checks for primes
      if (bv_get_bit(v, i) == 1) {
        char* palintest = tobase(i, bases[p]);
        //checks if its palindrome prime in that base
        if (isPalindrome(palintest)) {
          printf("%d = %s\n", i, tobase(i, bases[p]));
        }
      }
    }
    // prints new line after each base
    if (p < 3) {
      printf("\n");
    }
  }
}
