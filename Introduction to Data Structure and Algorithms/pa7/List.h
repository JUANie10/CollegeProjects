/*********************************************************************************
* Name: 			Juan Lee
* CruzID:			jlee543
* Course: 			CSE 101 Spring 2020  PA7
* File name: 		List.h
* File Description: Function headers for List ADT
*********************************************************************************/
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT. List is a double ended queue with a vertical
// cursor standing between elements. The cursor position is always defined
// to be an int in the range 0 (at front) to length of List (at back).
// An empty list consists of the vertical cursor only, with no elements.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>

#ifndef List_H_INCLUDE_
#define List_H_INCLUDE_

// Exported type --------------------------------------------------------------
class List{

private:

   // private Node struct
   struct Node{
      // Node fields
      int data;
      Node* next;
      Node* prev;
      // Node constructor
      Node(int x);
   };

   // List fields
   Node* frontDummy;
   Node* backDummy;
   Node* beforeCursor;
   Node* afterCursor;
   int pos_cursor;
   int num_elements;

public:

   // Class Constructors & Destructors ----------------------------------------
   
   // Creates new List in the empty state.
   List();

   // Copy constructor.
   List(const List& L);

   // Destructor
   ~List();


   // Access functions --------------------------------------------------------

   // isEmpty()
   // Returns true if this List is empty, false otherwise.
   bool isEmpty();

   // size()
   // Returns the size of this List.
   int size();

   // position()
   // Returns the position of the cursor in this List. The value returned
   // will be in the range 0 to size().
   int position();


   // Manipulation procedures -------------------------------------------------

   // moveFront()
   // Moves cursor to position 0 in this List.
   void moveFront();

   // moveBack()
   // Moves cursor to position size() in this List.
   void moveBack();

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<size()
   int peekNext();

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   int peekPrev();

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over.
   // pre: position()<size()
   int moveNext();

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over.
   // pre: position()>0
   int movePrev();

   // insertAfter()
   // Inserts x after cursor.
   void insertAfter(int x);

   // insertBefore()
   // Inserts x before cursor.
   void insertBefore(int x);

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<size()
   void eraseAfter();

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
   void eraseBefore();

   // findNext()
   // Starting from the current cursor position, performs a linear search (in
   // the direction front-to-back) for the first occurrence of the element x.
   // If x is found, places the cursor immediately after the found element (so
   // eraseBefore() would remove the found element), and returns the final
   // cursor position. If x is not found, places the cursor at position size(),
   // and returns -1.
   int findNext(int x);

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in
   // the direction back-to-front) for the first occurrence of the element x.
   // If x is found, places the cursor immediately before the found element (so
   // eraseAfter() would remove the found element), and returns the final
   // cursor position. If x is not found, places the cursor at position 0, and
   // returns -1.
   int findPrev(int x);

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique data
   // values. The order of the remaining elements is obtained by retaining
   // the frontmost occurrance of each element, and removing all other
   // occurances. The cursor is not moved with respect to the retained
   // elements, i.e. it lies between the same two retained elements that it
   // did before cleanup() was called.
   void cleanup();

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void clear();

   // concat()
   // Returns a new List consisting of the elements of this List, followed
   // the elements of L. The returned List's cursor will be at its front
   // (position 0).
   List concat(const List& L);


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this List consisting of a comma
   // separated sequence of elements, surrounded by parentheses.
   std::string to_string();

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool equals(const List& R);


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   friend std::ostream& operator<<( std::ostream& stream, List& L );

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The
   // cursors in both Lists are unchanged are unchanged.
   friend bool operator==( List& A, const List& B );

   // operator=()
   // Overwrites the state of this List with state of L.
   List& operator=( const List& L );

};


#endif
