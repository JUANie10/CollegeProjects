/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA5
* File name:     Dictionary.c
* File Description: Function prototypes for Dictionary ADT
*********************************************************************************/

#include "Dictionary.h"


// Private Types and Functions ------------------------------------------------

// Struct for NodeObj
typedef struct NodeObj {
  KEY_TYPE key;
  VAL_TYPE val;
  struct NodeObj* parent;
  struct NodeObj* left;
  struct NodeObj* right;
} NodeObj;

// Private Node type
typedef NodeObj* Node;

// Struct for DictionaryObj
typedef struct DictionaryObj {
  struct NodeObj* cursor;
  struct NodeObj* root;
  int uni;
  int size;
} DictionaryObj;

// private Function Declaration -----------------------------------------------
Node newNode(KEY_TYPE k, VAL_TYPE value);
Node findKey(Node R, KEY_TYPE k);
Node TreeMinimum(Node x);
Node TreeMaximum(Node x);
Node treeSuccessor(Dictionary D);
Node treePredecessor(Dictionary D);
void deleteAll(Node r);
void inorder(FILE* out, Node r);

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Creates and returns a new Node.
Node newNode(KEY_TYPE k, VAL_TYPE value) {
  Node newN = malloc(sizeof(NodeObj));
  newN->key = k;
  newN->val = value;
  newN->parent = NULL;
  newN->left = NULL;
  newN->right = NULL;
  return newN;
}

// freeNode()
// frees heap memory associated with *pN, sets *pN to NULL.
void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary
// will accept duplicate keys, i.e. distinct pairs with identical keys. If
// unique==true (1 or any non-zero value), then duplicate keys will not be
// accepted. In this case, the operation insert(D, k) will enforce the
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique) {
  Dictionary newDict = malloc(sizeof(DictionaryObj));
  newDict->uni = unique;
  newDict->size = 0;
  newDict->root = NULL;
  newDict->cursor = NULL;
  return newDict;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD) {
  if (pD != NULL && *pD != NULL) {
    makeEmpty(*pD);
    free(*pD);
    *pD = NULL;
  }
}


// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D) {
  if (D == NULL) {
    printf("Dictionary Error: calling size() on a NULL Dictionary reference");
    exit(1);
  }
  return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D) {
  if (D == NULL) {
    printf("Dictionary Error: calling unique() on a NULL Dictionary reference");
    exit(1);
  }
  return D->uni;
}

// findKey()
// Returns the Node containing key k in the subtree at Node R, or returns NULL
// if no such Node exists.
Node findKey(Node R, KEY_TYPE k) {
  if (R == NULL || KEY_CMP(k, R->key) == 0) {
    return R;
  }
  else if (KEY_CMP(k, R->key)<0) {
    return findKey(R->left, k);
  }
  else {
    return findKey(R->right, k);
  }
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {
  Node N;
  if (D == NULL) {
    printf("Dictionary Error: calling lookup() on a NULL Dictionary reference");
    exit(1);
  }
  N = findKey(D->root, k);
  return (N==NULL ? VAL_UNDEF : N->val);
}


// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
  Node N, A, B;
  if (D==NULL ) {
     printf("Dictionary Error: calling insert() on NULL Dictionary reference\n");
     exit(1);
  }
  N = newNode(k, v);
  B = NULL;
  A = D->root;
  while (A != NULL) {
     B = A;
     if (KEY_CMP(k, A->key) < 0) {
        A = A->left;
     }
     else {
        A = A->right;
     }
  }
  N->parent = B;
  if ( B==NULL ) {
     D->root = N;
  }
  else if (KEY_CMP(k, B->key) < 0) {
     B->left = N;
  }
  else {
     B->right = N;
  }
  D->size += 1;
}

// TreeMinimum()
// Returns the left most node of the input node
Node TreeMinimum(Node x) {
  while (x->left != NULL) {
    x = x->left;
  }
  return x;
}

// TreeMaximum()
// Return the right most node of the input node
Node TreeMaximum(Node x) {
  while (x->right != NULL) {
    x = x->right;
  }
  return x;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k) {
  if (lookup(D, k) == VAL_UNDEF) {
    printf("Dictionary Error: calling delete() on key that does not exist\n");
    exit(1);
  }
  Node N, P, S;
  N = findKey(D->root, k);
  if (N == D->cursor) {
    D->cursor = NULL;
  }
  if (N->left==NULL && N->right==NULL ) {
    // case 1 (no children)
     if( N == D->root ){
        D->root = NULL;
        freeNode(&N);
     }
     else{
        P = N->parent;
        if( P->right==N ) {
           P->right = NULL;
        }
        else{
           P->left = NULL;
        }
        freeNode(&N);
     }
  }
  else if( N->right==NULL ) {
    // case 2 (left but no right child)
     if( N==D->root ) {
        D->root = N->left;
        freeNode(&N);
     }
     else {
       P = N->parent;
        if( P->right==N ) {
           P->right = N->left;
        }
        else{
           P->left = N->left;
        }
        freeNode(&N);
     }
  }
  else if (N->left==NULL ) {
    // case 2 (right but no left child)
     if( N==D->root ) {
        D->root = N->right;
        freeNode(&N);
     }
     else {
        P = N->parent;
        if( P->right==N ) {
           P->right = N->right;
        }
        else {
           P->left = N->right;
        }
        freeNode(&N);
     }
  }
  else {
    // case3: (two children: N->left!=NULL && N->right!=NULL)
     S = TreeMinimum(N->right);
     N->key = S->key;
     N->val = S->val;
     P = S->parent;
     if( P->right==S ) {
        P->right = S->right;
     }
     else {
        P->left = S->right;
     }
     freeNode(&S);
  }
  D->size -= 1;
}

// deleteAll()
// deletes all the Nodes in the subtree rooted at r
void deleteAll(Node r) {
  if (r != NULL) {
    deleteAll(r->left);
    deleteAll(r->right);
    freeNode(&r);
  }
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D) {
  if (D==NULL ) {
     printf("Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
     exit(1);
  }
  deleteAll(D->root);
  D->root = NULL;
  D->cursor = NULL;
  D->size = 0;
  return;
}



// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D) {
  if (D->size == 0) {
    return VAL_UNDEF;
  }
  D->cursor = TreeMinimum(D->root);
  return currentVal(D);
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D) {
  if (D->size == 0) {
    return VAL_UNDEF;
  }
  D->cursor = TreeMaximum(D->root);
  return currentVal(D);
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D) {
  if (D->cursor == NULL) {
    return KEY_UNDEF;
  }
  return D->cursor->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D) {
  if (D->cursor == NULL) {
    return VAL_UNDEF;
  }
  return D->cursor->val;
}

// treeSuccessor()
// returns the next node in D to be processed in an in-order tree walk
Node treeSuccessor(Dictionary D) {
  Node x = NULL, y = NULL;
  if (D->cursor->right != NULL) {
    return TreeMinimum(D->cursor->right);
  }
  y = D->cursor->parent;
  while (y != NULL && x == D->cursor->right) {
    x = y;
    if (y->parent == NULL) {
      y = NULL;
    }
  }
  if (D->cursor->right == NULL) {
    y = newNode(KEY_UNDEF, VAL_UNDEF);
  }
  return y;
}

// treePredecessor()
// return the prev node in D to be processed in an in-order tree walk.
Node treePredecessor(Dictionary D) {
  Node x = NULL, y = NULL;
  if (D->cursor->left != NULL) {
    return TreeMaximum(D->cursor->left);
  }
  y = D->cursor->parent;
  while (y != NULL && x == D->cursor->left) {
    x = y;
    if (y->parent == NULL) {
      y = NULL;
    }
  }
  if (y == NULL) {
    y = newNode(KEY_UNDEF, VAL_UNDEF);
  }
  return y;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D) {
  if (D->cursor == NULL) {
    return VAL_UNDEF;
  }
  D->cursor = treeSuccessor(D);
  if (D->cursor->key == KEY_UNDEF && D->cursor->val == VAL_UNDEF) {
    freeNode(&D->cursor);
    D->cursor = NULL;
  }
  return currentVal(D);
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D) {
  if (D->cursor == NULL) {
    return VAL_UNDEF;
  }
  D->cursor = treePredecessor(D);
  if (D->cursor->key == KEY_UNDEF && D->cursor->val == VAL_UNDEF) {
    freeNode(&D->cursor);
    D->cursor = NULL;
  }
  return currentVal(D);
}


// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D) {
  inorder(out, D->root);
  return;
}

// inorder()
// prints the dictionary in order of KEY_CMP() using in-order tree traversal
void inorder(FILE* out, Node r) {
  if (r != NULL) {
    inorder(out, r->left);
    fprintf(out, "%s\n", r->key);
    inorder(out, r->right);
  }
  return;
}
