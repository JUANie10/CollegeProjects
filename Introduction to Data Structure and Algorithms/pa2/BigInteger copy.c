/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020  PA2
* File name:     BigInteger.c
* File Description: Function prototypes for BIgInteger ADT
*********************************************************************************/

#include "BigInteger.h"

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(void) {
  BigInteger BI = malloc(sizeof(BigIntegerObj));
  BI->sign = 0;
  BI->digits = newList();
  return BI;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN) {
  if (*pN != NULL && pN != NULL) {
    freeList(&(*pN)->digits);
    free(*pN);
    pN = NULL;
  }
}


// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N) {
  if (N == NULL) {
    printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
    exit(1);
  }
  if (N->sign == 0) {
    return 0;
  }
  else if (N->sign == -1) {
    return -1;
  }
  return 1;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B) {
  if (A == NULL || B == NULL) {
    printf("BigInteger Error: calling compare() on NULL BigInteger reference\n");
    exit(1);
  }
  if (length(A->digits) > length(B->digits)) {
    if (sign(A) == sign(B)) {
      if (sign(A) == 1) {
        return 1;
      }
      else if (sign(A) == -1) {
        return -1;
      }
    }
    else if (sign(A) == 1 && sign(B) == -1) {
      return 1;
    }
    else if (sign(A) == -1 && sign(B) == 1) {
      return -1;
    }
    else if (sign(A) == 0) {
      if (sign(B) == 1) {
        return 1;
      }
      else {
        return -1;
      }
    }
    else if (sign(B) == 0) {
      if (sign(A) == 1) {
        return 1;
      }
      else {
        return -1;
      }
    }
  }
  else if (length(A->digits) < length(B->digits)) {
    if (sign(A) == sign(B)) {
      if (sign(A) == 1) {
        return -1;
      }
      else if (sign(A) == -1) {
        return 1;
      }
    }
    else if (sign(A) == 1 && sign(B) == -1) {
      return 1;
    }
    else if (sign(A) == -1 && sign(B) == 1) {
      return -1;
    }
    else if (sign(A) == 0) {
      if (sign(B) == 1) {
        return -1;
      }
      else {
        return 1;
      }
    }
    else if (sign(B) == 0) {
      if (sign(A) == 1) {
        return -1;
      }
      else {
        return 1;
      }
    }
  }
  else {
    if (length(A->digits) == 0) {
      return 0;
    }
    moveFront(A->digits);
    moveFront(B->digits);
    while (index(A->digits) != -1) {
      if (get(A->digits) > get(B->digits)) {
        return 1;
      }
      else if (get(A->digits) < get(B->digits)) {
        return -1;
      }
      else {
        moveNext(A->digits);
        moveNext(B->digits);
      }
    }
    if (sign(A) == sign(B)) {
      return 0;
    }
    else {
      if (sign(A) == 1) {
        return 1;
      }
      else {
        return -1;
      }
    }
  }
  return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B) {
  if (compare(A, B) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N) {
  if (N == NULL) {
    printf("BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
    exit(1);
  }
  if (N->digits != NULL) {
    freeList(&N->digits);
  }
  N->digits = newList();
  N->sign = 0;
  return;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {
  if (sign(N) == -1) {
    N->sign = 1;
  }
  else if (sign(N) == 1) {
    N->sign = -1;
  }
  return;
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s) {
  long tempnum = 0;
  BigInteger newBI = newBigInteger();
  char neg = '-', pos = '+';
  char sign = s[0];
  if (pos == sign) {
    newBI->sign = 1;
    tempnum = atol(s);
    append(newBI->digits, tempnum);
    normalize(newBI);
  }
  else if (neg == sign) {
    newBI->sign = -1;
    tempnum = atol(s)*-1;
    append(newBI->digits, tempnum);
    normalize(newBI);
  }
  else {
    newBI->sign = 1;
    tempnum = atol(s);
    append(newBI->digits, tempnum);
    normalize(newBI);
  }
  return newBI;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {
  if (N == NULL) {
    printf("BigInteger Error: calling copy() on NULL BigInteger reference\n");
    exit(1);
  }
  else if (N->sign == 0) {
    BigInteger newN2 = newBigInteger();
    return newN2;
  }
  BigInteger newN = newBigInteger();
  freeList(&newN->digits);
  newN->digits = copyList(N->digits);
  newN->sign = sign(N);
  return newN;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B) {
  if (A == NULL || B == NULL || S == NULL) {
    printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
    exit(1);
  }
  if (sign(A) == 0 && sign(B) == 0) {
    S->sign = 0;
    freeList(&S->digits);
    S->digits = newList();
    
  }
  else if (sign(A) == 0 && sign(B) != 0) {
    S->sign = sign(B);
    List templist = copyList(B->digits);
    freeList(&S->digits);
    S->digits = templist;
    
  }
  else if (sign(A) != 0 && sign(B) == 0) {
    S->sign = sign(A);
    List templist = copyList(A->digits);
    freeList(&S->digits);
    S->digits = templist;
    
  }
  else {
    long tempnum = 0;
    if (sign(A) == -1 && sign(B) == 1) {
      
      negate(A);
      if (equals(A, B)) {
        makeZero(S);
      }
      else {
        subtract(S, B, A);
      }
      negate(A);
      
    }
    else if (sign(A) == 1 && sign(B) == -1) {
      negate(B);
      if (equals(A, B)) {
        makeZero(S);
      }
      else {
        subtract(S, A, B);
      }
      negate(B);
    }
    else {
      moveBack(A->digits);
      moveBack(B->digits);
      moveBack(S->digits);
      BigInteger tempBigInt = newBigInteger();
      if (length(A->digits) > length(B->digits)) {
        moveBack(A->digits);
        moveBack(B->digits);
        while (index(A->digits) != -1) {
          tempnum += get(A->digits);
          if (index(B->digits) != -1) {
            tempnum += get(B->digits);
            movePrev(B->digits);
          }
          prepend(tempBigInt->digits, tempnum);
          movePrev(A->digits);
          tempnum = 0;
        }
      }
      else if (length(A->digits) < length(B->digits)) {
        moveBack(A->digits);
        moveBack(B->digits);
        while (index(B->digits) != -1) {
          tempnum += get(B->digits);
          if (index(A->digits) != -1) {
            tempnum += get(A->digits);
            movePrev(A->digits);
          }
          prepend(tempBigInt->digits, tempnum);
          movePrev(B->digits);
          tempnum = 0;
        }
      }
      else {
        moveBack(A->digits);
        moveBack(B->digits);
        while (index(B->digits) != -1) {
          tempnum += get(B->digits);
          if (index(A->digits) != -1) {
            tempnum += get(A->digits);
            movePrev(A->digits);
          }
          prepend(tempBigInt->digits, tempnum);
          movePrev(B->digits);
          tempnum = 0;
        }
      }
      normalize(tempBigInt);
      if (S->digits != NULL) {
        freeList(&S->digits);
      }
      S->digits = copyList(tempBigInt->digits);
      S->sign = sign(A);
      freeBigInteger(&tempBigInt);
    }
  }
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B) {
  BigInteger S = newBigInteger();
  add(S, A, B);
  return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B) {
  if (A == NULL || B == NULL || D == NULL) {
    printf("BigInteger Error: calling subtract() on NULL BigInteger reference\n");
    exit(1);
  }
  if (sign(A) == 0 && sign(B) == 0) {
    D->sign = 0;
    freeList(&D->digits);
    D->digits = newList();
    
  }
  else if (sign(A) == 0 && sign(B) != 0) {
    negate(B);
    List templist = copyList(B->digits);
    freeList(&D->digits);
    D->digits = templist;
    D->sign = sign(B);
    negate(B);
    
  }
  else if (sign(A) != 0 && sign(B) == 0) {
    List templist = copyList(A->digits);
    freeList(&D->digits);
    D->digits = templist;
    D->sign = sign(A);
  }
  else if (sign(A) == 1 && sign(B) == -1) {
    negate(B);
    add(D, A, B);
    negate(B);
    
  }
  else if (sign(A) == -1 && sign(B) == 1) {
    negate(B);
    add(D, A, B);
    negate(B);
  }
  else if (sign(A) == -1 && sign(B) == -1) {
    if (equals(A, B)) {
      makeZero(D);
    }
    else {
      negate(B);
      negate(A);
      subtract(D, A, B);
      negate(B);
      negate(A);
      negate(D);
    }
  }
  else {
    if (equals(A, B)) {
      makeZero(D);
    }
    else if (compare(A, B) == 1) {
      moveBack(A->digits);
      moveBack(B->digits);
     
      long tempnum = 0;
      BigInteger tempBigInt = newBigInteger();
      while(index(A->digits) != -1) {
        tempnum += get(A->digits);
        if (index(B->digits) != -1) {
          tempnum -= get(B->digits);
          movePrev(B->digits);
        }
        prepend(tempBigInt->digits, tempnum);
        movePrev(A->digits);
        tempnum = 0;
      }
      normalize(tempBigInt);
      freeList(&D->digits);
      D->digits = copyList(tempBigInt->digits);
      D->sign = 1;
      freeBigInteger(&tempBigInt);
    }
    else if (compare(A, B) == -1) {
      subtract(D, B, A);
      negate(D);
    }
  }
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B) {
  BigInteger D = newBigInteger();
  subtract(D, A, B);
  return D;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B) {
  if (A == NULL || B == NULL || P == NULL) {
    printf("BigInteger Error: calling multiply() on NULL BigInteger reference\n");
    exit(1);
  }
  if (sign(B) == 0 || sign(A) == 0) {
    makeZero(P);
  }
  else {
    BigInteger addsum = newBigInteger();
    BigInteger tempInt = newBigInteger();
    BigInteger buffer = newBigInteger();
    BigInteger pB;
    bool pBbool = false;
    if (equals(A, B) == 1) {
      pBbool = true;
      pB = copy(B);
    }
    else {
      pB = B;
    }
    moveBack(A->digits);
    moveBack(pB->digits);
    long tempnum = 0, counterA = 0, counterB = 0;
    while(index(pB->digits) != -1) {
      counterA = 0;
      makeZero(tempInt);
      moveBack(A->digits);
      while(index(A->digits) != -1) {
        makeZero(buffer);
        
        tempnum = get(A->digits) * get(pB->digits);
        append(buffer->digits, tempnum);
        
        for (long i = 0; i < (length(pB->digits)-index(pB->digits)-1); i++) {
          append(buffer->digits, 0);
        }
        for (long i = 0; i < (length(A->digits)-index(A->digits)-1); i++) {
          append(buffer->digits, 0);
        }
        normalize(buffer);
        
        buffer->sign = 1;
        if (length(tempInt->digits) == 0) {
          tempInt->sign = 0;
        }
        else {
          tempInt->sign = 1;
        }
        
        add(tempInt, buffer, tempInt);
        normalize(tempInt);
        makeZero(buffer);
        
        counterA++;
        movePrev(A->digits);
        counterB++;
      }
      
      if (length(tempInt->digits) == 0) {
        tempInt->sign = 0;
      }
      else {
        tempInt->sign = 1;
      }
      addsum->sign = 1;
      add(addsum, tempInt, addsum);
      normalize(addsum);
      movePrev(pB->digits);
    }
    if (pBbool == true) {
      freeBigInteger(&pB);
    }
    
    normalize(addsum);
    
    freeList(&P->digits);
    P->digits = copyList(addsum->digits);
    P->sign = sign(addsum);
    
    if (sign(A) == -1 && sign(B) == -1) {
      P->sign = sign(addsum);
    }
    else if (sign(A) == -1 || sign(B) == -1) {
      negate(P);
    }
    freeBigInteger(&buffer);
    freeBigInteger(&addsum);
    freeBigInteger(&tempInt);
  }
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B) {
  BigInteger P = newBigInteger();
  multiply(P, A, B);
  return P;
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N) {
  if (N == NULL) {
    printf("BigInteger Error: calling printBigInteger() on NULL BigInteger reference\n");
    exit(1);
  }
  if (N->sign == 1) {
    printList(out, N->digits);
  }
  else if (N->sign == -1) {
    fprintf(out, "-");
    printList(out, N->digits);
  }
  else {
    fprintf(out, "0");
  }
  fprintf(out, "\n\n");
  return;
}

// normalize()
// normalizes the given BigInteger values
void normalize(BigInteger N) {
  long carry = 0, normal = 0;
  moveBack(N->digits);
  while (N->digits->cursor != NULL) {
    if (get(N->digits) >= BASE) {
      carry = get(N->digits) + carry;
      normal = carry;
      carry /= BASE;
      carry *= BASE;
      normal -= carry;
      carry /= BASE;
      set(N->digits, normal);
      movePrev(N->digits);
      if (index(N->digits) != -1) {
        set(N->digits, get(N->digits) + carry);
      }
      else {
        prepend(N->digits, carry);
      }
      movePrev(N->digits);
    }
    movePrev(N->digits);
  }
  if (N->digits != NULL) {
    if (length(N->digits) != 0) {
      moveFront(N->digits);
      while(get(N->digits) == 0) {
        deleteFront(N->digits);
        moveFront(N->digits);
      }
    }
  }
}
