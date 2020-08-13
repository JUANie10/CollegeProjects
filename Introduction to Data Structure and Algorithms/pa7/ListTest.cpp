
/*********************************************************************************
* Name: 			Juan Lee
* CruzID:			jlee543
* Course: 			CSE 101 Spring 2020  PA7
* File name: 		ListClient.cpp
* File Description: Function Tests for List ADT
*********************************************************************************/
//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main(){

  List A;
  A.insertBefore(3);
  A.insertBefore(2);
  A.insertBefore(1);
  A.insertBefore(0);
  
  A.clear();
  
   List  B, C, D, E;

  A.insertBefore(1);
        A.insertAfter(3);
        A.insertAfter(2);
        B.insertBefore(3);
        B.insertBefore(2);
        B.insertBefore(1);
        C.insertAfter(1);
        C.insertAfter(2);
        C.insertAfter(3);
        C.insertAfter(3);
        C.insertAfter(2);
  C.insertAfter(1);
  
  A.moveFront();
  while (A.position() != A.size()) {
    cout << A.moveNext() << " ";
  }
  cout << "\n";
  B.moveFront();
  while (B.position() != B.size()) {
    cout << B.moveNext() << " ";
  }
  cout << "\n";
  
  C.moveFront();
  while (C.position() != C.size()) {
    cout << C.moveNext() << " ";
  }
  cout << "\n";
  B.moveFront();
  D = A.concat(B);
  
  D.moveFront();
  while (D.position() != D.size()) {
    cout << D.moveNext() << " ";
  }
  cout << "\n";
  
  
  cout << !C.equals(A.concat(B)) << "\n";
  
  
  A.insertBefore(1);
  A.insertBefore(5);
  A.insertBefore(22);
  A.insertBefore(176);
  A.insertBefore(3215);
  A.movePrev();
  A.movePrev();
  
  A.eraseAfter();
        A.eraseAfter();
        A.movePrev();
        A.movePrev();
  
  A.movePrev();
  A.moveBack();
  cout << A.movePrev() << "\n";
  
  
  A.insertAfter(3215);
  A.insertAfter(176);
  A.insertAfter(22);
  A.insertAfter(5);
  A.insertAfter(1);
  A.moveNext();
  A.moveNext();
  A.eraseBefore();
        A.eraseBefore();
        A.moveNext();
        A.moveNext();
  A.moveNext();
  
  while (A.position() > 0) {
    cout << A.movePrev() << " " << A.position() << "\n";
    
  }
  
  A.moveFront();
  while (A.position() < A.size()) {
    cout << A.moveNext() << " " << A.position() << "\n";
    
  }
  
  A.insertAfter(2);
  A.insertAfter(1);
  B = A;
  
  cout << !A.equals(B) << " should be 0" << endl;
  
  
  A.insertAfter(16);
        A.insertAfter(200);
        A.insertAfter(176);
        A.insertAfter(16);
        A.insertAfter(5);
        A.insertAfter(1);
        A.findNext(16);
  
  A.movePrev();
        A.insertBefore(225);
   A.moveNext();
        A.findNext(16);
   A.moveFront();
  cout << A.peekNext() << " " << A.peekPrev() << "\n";
  A.moveNext();
  cout << A.peekNext() << " " << A.peekPrev() << "\n";
        A.findNext(16);
  cout << A.position() << " = 4\n";
  
  A.insertAfter(1);
  cout << A.peekNext() << " next" << A.peekPrev() << " prev\n";
  
  A.insertAfter(2);
  cout << A.peekNext() << " next" << A.peekPrev() << " prev\n";
  
  A.insertAfter(3);
  cout << A.peekNext() << " next" << A.peekPrev() << " prev\n";
  
  A.insertAfter(1);
  cout << A.peekNext() << " next" << A.peekPrev() << " prev\n";
  
  A.insertAfter(2);
  cout << A.peekNext() << " next" << A.peekPrev() << " prev\n";

  A.insertAfter(1);
  cout << A.peekNext() << " next" << A.peekPrev() << " prev\n";
  
  A.cleanup();
  
  
  cout << A.size() << " == 10\n";
  
  A.insertBefore(1);
  A.insertBefore(5);
  A.insertBefore(16);
  A.insertBefore(176);
  A.insertBefore(200);
  A.insertBefore(16);
  A.findPrev(16);
  cout << A.position() << "== 14\n";
  
  A.moveNext();
  A.insertAfter(225);
  cout << A.position() << "== 15\n";
  
  A.movePrev();
  A.findPrev(16);
  cout << A.position() << "== 11\n";
  
  A.moveBack();
  cout << A.size() << "\n";
  
  A.findPrev(16);
  cout << A.position() << "== 14\n";
  
  
  A.insertAfter(1);
  A.insertAfter(2);
  A.insertAfter(3);
  B.insertAfter(4);
  B.insertAfter(5);
  B.insertAfter(6);
  C = A.concat(B);
  
  
  cout << A.size() << "  should be 20\n";

  A.insertAfter(1);
  A.insertAfter(2);
  A.insertAfter(3);
  A.insertAfter(5);
  A.insertAfter(12);
  
  
  A.moveNext();
  A.eraseBefore();
  cout << A.size() << "  should be 24\n";

  A.findNext(2);
  A.eraseBefore();
  cout << A.size() << "  should be 23\n";
  
  A.clear();
  B.clear();
  C.clear();
  D.clear();
  

   return(0);
}
