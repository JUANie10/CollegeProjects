/*********************************************************************************
* Name: 			Juan Lee
* CruzID:			jlee543
* Course: 			CSE 101 Spring 2020  PA7
* File name: 		Shuffle.cpp
* File Description:  Loads a list from 0 to n (entered number) and computes the amount of shuffles needed to
              return to the original list
*********************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

void shuffle(List& D, int size);

int main(int argc, char* argv[]) {
  
  if (argc != 2) {
     printf("Input the following: %s <positive integer>\n", argv[0]);
     exit(1);
  }
  // Convers the inputed number to integer
  int n = atoi(argv[1]);
  // Printing header statements
  cout << "deck size       shuffle count\n";
  cout << "------------------------------\n";
  List D, Dc;
  int i = 0, counter = 0;
  // Creates the list and Shuffles to check if the List is in the same order
  while (i < n) {
    D.insertBefore(i);
    Dc.insertBefore(i);
    i++;
    counter = 0;
    while (1) {
      shuffle(Dc, D.size());
      counter++;
      // If shuffle equals the original List print
      if (D == Dc) {
        cout << i << "               " << counter << "\n";
        break;
      }
    }
  }
  return 0;
}

// Performs a perfect shuffle operation on the List D
void shuffle(List& D, int size) {
  if (size == 1) {
    return;
  }
  int s = size/2;
  int a, b, ss;
  List A, B;
  D.moveFront();
  ss = size - s;
  for (int i = 0; i < s; i++) {
    a = D.moveNext();
    A.insertBefore(a);
  }
  for (int i = 0; i < ss; i++) {
    b = D.moveNext();
    B.insertBefore(b);
  }
  D.clear();
  A.moveFront();
  B.moveFront();
  for (int i = 0; i < size; i++) {
    if (i%2 == 0) {
      b = B.moveNext();
      D.insertBefore(b);
    }
    else {
      a = A.moveNext();
      D.insertBefore(a);
    }
  }
  A.clear();
  B.clear();
}
