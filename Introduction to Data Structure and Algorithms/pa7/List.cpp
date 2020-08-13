/*********************************************************************************
* Name: 			Juan Lee
* CruzID:			jlee543
* Course: 			CSE 101 Spring 2020  PA7
* File name: 		List.cpp
* File Description: Function prototypes for List ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

using namespace std;


// Private Constructor --------------------------------------------------------
List::Node::Node(int x){
  data = x;
  next = nullptr;
  prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------
   
  
  
// Creates new List in the empty state.
List::List(){
  frontDummy = new Node(-1);
  backDummy = new Node(-1);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = backDummy;
  afterCursor = frontDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
  frontDummy = new Node(-1);
  backDummy = new Node(-1);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = backDummy;
  afterCursor = frontDummy;
  pos_cursor = 0;
  num_elements = 0;
  Node *N = L.frontDummy->next;
  while (N->data != -1) {
    insertAfter(N->data);
    moveNext();
    N = N->next;
  }
}

// Destructor
List::~List(){
  this->clear();
  if (frontDummy != NULL) {
    delete frontDummy;
  }
  if (backDummy != NULL) {
    delete backDummy;
  }
}


// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
  return (num_elements == 0);
}

// size()
// Returns the size of this List.
int List::size(){
  return (num_elements);
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position(){
  return (pos_cursor);
}

// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
  if ((frontDummy->next->data == -1) && (size() != 0)) {
    beforeCursor = frontDummy->next;
    afterCursor = frontDummy->next->next;
    pos_cursor = 0;
  }
  else {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
  }
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack() {
  if ((backDummy->prev->data == -1) && (size() != 0)) {
    beforeCursor = backDummy->prev->prev;
    afterCursor = backDummy->prev;
    pos_cursor = size();
  }
  else {
    
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = size();
  }
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext(){
  if (position() < size()) {
    return (afterCursor->data);
  }
  else {
    return (-1);
  }
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev(){
  if (position() > 0) {
    return (beforeCursor->data);
  }
  else {
    return (-1);
  }
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<size()
int List::moveNext(){
  if (position() < size()) {
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return (beforeCursor->data);
  }
  else {
    return (-1);
  }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
int List::movePrev(){
  if (position() > 0) {
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return (afterCursor->data);
  }
  else {
    return (-1);
  }
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x){
  Node* N = new Node(x);
  
  beforeCursor->next = N;
  afterCursor->prev = N;
  N->next = afterCursor;
  N->prev = beforeCursor;
  afterCursor = N;
  num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x){
  Node* N = new Node(x);
  beforeCursor->next = N;
  afterCursor->prev = N;
  N->prev = beforeCursor;
  N->next = afterCursor;
  beforeCursor = N;
  num_elements++;
  pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){
  if (position() < size()) {
    Node* N = afterCursor->next;
    Node* Na = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    if (Na != NULL) {
      delete Na;
    }
    
    afterCursor = N;
    num_elements--;
  }
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
  if (position() > 0) {
    Node* Na = beforeCursor;
    Node* N = beforeCursor->prev;
    N->next = afterCursor;
    if (Na != NULL) {
      delete Na;
    }
    afterCursor->prev = N;
    
    beforeCursor = N;
    num_elements--;
    pos_cursor--;
  }
}

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(int x){
  int i;
  while (1) {
    i = moveNext();
    if (i == -1) {
      break;
    }
    if (i == x) {
      return (pos_cursor);
    }
  }
  moveBack();
  return (-1);
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(int x) {
  int i;
  while (1) {
    i = movePrev();
    if (i == -1) {
      break;
    }
    if (i == x) {
      return (pos_cursor);
    }
  }
  moveFront();
  return (-1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup(){
  int ogpos = pos_cursor;
  int temp = 0, counter = 0;
  moveFront();
  Node *N = afterCursor;
  while (N != backDummy) {
    moveFront();
    findNext(N->data);
    while (1) {
      if (N->next == backDummy) {
        break;
      }
      temp = findNext(N->data);
      if (temp == -1) {
        break;
      }
      if (pos_cursor <= ogpos) {
        ogpos--;
      }
      eraseBefore();
    }
    N = frontDummy->next;
    counter++;
    for (int i = 0; i < counter; i++) {
      N = N->next;
    }
  }
  moveFront();
  for (int i = 0; i < ogpos; i++) {
    moveNext();
  }
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
  if (size() != 0) {
    moveFront();
    Node *N = frontDummy->next;
    if (N->data == -1) {
      N = N->next;
    }
    Node *temp = NULL;
    while (N->data != -1) {
      temp = N;
      N = N->next;
      if (temp != NULL) {
        delete temp;
      }
      if (N->next == NULL) {
        break;
      }
    }
    num_elements = 0;
    pos_cursor = 0;
    if (frontDummy == NULL) {
      beforeCursor = new Node(-1);
    }
    else {
      beforeCursor = frontDummy;
    }
    if (backDummy == NULL) {
      afterCursor = new Node(-1);
    }
    else {
      afterCursor = backDummy;
    }
  }
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
  
  List A;
  Node *N = L.frontDummy;
  N = N->next;
  if (N->data == -1 && L.num_elements != 0) {
    N = N->next;
  }
  Node *N1 = frontDummy->next;
  if (N1->data == -1 && size() != 0) {
    N1 = N1->next;
  }
  
  while (N1->data != -1) {
    A.insertBefore(N1->data);
    N1 = N1->next;
  }
  
  while (N->data != -1) {
    A.insertBefore(N->data);
    N = N->next;
  }
  A.moveFront();
  return A;
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
string List::to_string(){
  int cur = pos_cursor;
  if (pos_cursor != 0) {
    moveFront();
  }
  Node *N = afterCursor;
  
  string s = "(";
  while (N->data != -1) {
    s+= std::to_string(N->data);
    N = N->next;
    if (N->data != -1) {
      s += ",";
    }
  }
  s += ")";
  for (int i = 0; i<cur; i++) {
    moveNext();
  }
  return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R){
  if (R.num_elements == num_elements) {
    Node *N = frontDummy->next->next;
    Node *M = R.frontDummy->next;
    while (N->data != -1 && M->data != -1) {
      if (N->data != M->data) {
        return (0);
      }
      N = N->next;
      M = M->next;
    }
    return (1);
  }
  return 0;
}


// Overriden Operators --------------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
ostream& operator<<( ostream& stream, List& L ){
  return stream << L.to_string();
}

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The
   // cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ) {
  return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
  if (this != &L) {
    clear();
    List temp = L;
    frontDummy = L.frontDummy;
    backDummy = L.backDummy;
    beforeCursor = L.beforeCursor;
    afterCursor = L.afterCursor;
    num_elements = L.num_elements;
    pos_cursor = L.pos_cursor;
  }
  return *this;
}

