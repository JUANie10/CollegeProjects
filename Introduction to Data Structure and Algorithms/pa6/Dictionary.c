/*********************************************************************************
* Name:       Juan Lee
* CruzID:      jlee543
* Course:       CSE 101 Spring 2020 PA6
* File name:     Dictionary.c
* File Description: Function prototypes for Dictionary ADT
*********************************************************************************/

#include "Dictionary.h"


// Private Types and Functions ------------------------------------------------

// Struct for NodeObj
typedef struct NodeObj {
  KEY_TYPE key;
  VAL_TYPE val;
  int color;
  int lookup;
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
  struct NodeObj* nil;
  int uni;
  int size;
} DictionaryObj;

// private Function Declaration -----------------------------------------------
Node newNode(Dictionary D, KEY_TYPE k, VAL_TYPE value);
void freeNode(Node *pN);
Node findKey(Dictionary D, Node R, KEY_TYPE k);
void leftRotate(Dictionary D, Node x);
void rightRotate(Dictionary D, Node x);
Node TreeMinimum(Dictionary D , Node x);
Node TreeMaximum(Dictionary D ,Node x);
void insertFix(Dictionary D, Node z);
void transplant(Dictionary D, Node u, Node v);
void deleteFix(Dictionary D, Node x);
Node treeSuccessor(Dictionary D);
Node treePredecessor(Dictionary D);
void deleteAll(Dictionary D, Node r);
void inorder(Dictionary D, FILE* out, Node r);
void preorder(Dictionary D, FILE* out, Node r);
void postorder(Dictionary D, FILE* out, Node r);

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Creates and returns a new Node.
Node newNode(Dictionary D ,KEY_TYPE k, VAL_TYPE value) {
  Node newN = malloc(sizeof(NodeObj));
  newN->key = k;
  newN->val = value;
  newN->parent = D->nil;
  newN->color = 0;
  newN->lookup = 0;
  newN->left = D->nil;
  newN->right = D->nil;
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
  newDict->nil = newNode(newDict,KEY_UNDEF, VAL_UNDEF);
  newDict->nil->left = newDict->nil;
  newDict->nil->right = newDict->nil;
  newDict->nil->parent = newDict->nil;
  newDict->size = 0;
  newDict->root = newDict->nil;
  newDict->cursor = NULL;
  return newDict;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD) {
  if (pD != NULL && *pD != NULL) {
    makeEmpty(*pD);
    freeNode(&(*pD)->nil);
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
Node findKey(Dictionary D, Node R, KEY_TYPE k) {
  if (R == D->nil) {
    return D->nil;
  }
  if (KEY_CMP(k, R->key) == 0) {
    return R;
  }
  else if (KEY_CMP( R->key, k) >0) {
    return findKey(D ,R->left, k);
  }
  else {
    return findKey(D ,R->right, k);
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
  N = findKey(D ,D->root, k);
  
  return (N==D->nil ? VAL_UNDEF : N->val);
}


// Manipulation procedures ----------------------------------------------------

// leftRoatate();
// set y
// turn y's left subtree into x's right subtree
// link x's parents to y
// puts x on y's left
void leftRotate(Dictionary D, Node x) {
  // set y
  if (x->right != D->nil) {
    Node y = x->right;
    // turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left != D->nil) {
      y->left->parent = x;
    }
    // link x's parents to y
    y->parent = x->parent;
    if (x->parent == D->nil) {
      D->root = y;
    }
    else if (x == x->parent->left) {
      x->parent->left = y;
    }
    else {
      x->parent->right = y;
    }
    // puts x on y's left
    y->left = x;
    x->parent = y;
    return;
  }
  
}

// rightRotate();
// set y
// turn y's right subtree into x's left subtree
// link x's parents to y
// puts x on y's right
void rightRotate(Dictionary D, Node x) {
  if (x->left != D->nil) {
    // set y
    Node y = x->left;
    // turn y's right subtree into x's left subtree
    x->left = y->right;
    if (y->right != D->nil) {
      y->right->parent = x;
    }
    // link x's parents to y
    y->parent = x->parent;
    if (x->parent == D->nil) {
      D->root = y;
    }
    else if (x == x->parent->right) {
      x->parent->right = y;
    }
    else {
      x->parent->left = y;
    }
    // puts x on y's right
    y->right = x;
    x->parent = y;
  }
  return;
}

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
  if (D==NULL ) {
     printf("Dictionary Error: calling insert() on NULL Dictionary reference\n");
     exit(1);
  }
  if (getUnique(D) == 1) {
    if (lookup(D, k) != VAL_UNDEF) {
      return;
    }
  }
  Node y = NULL, x = NULL, z = NULL;
  y = D->nil;
  x = D->root;
  z = newNode(D, k, v);
  while (x != D->nil) {
    y = x;
    if (KEY_CMP(x->key, z->key) > 0) {
      x = x->left;
    }
    else {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == D->nil) {
    D->root = z;
  }
  else if (KEY_CMP(y->key, z->key) > 0) {
    y->left = z;
  }
  else if (KEY_CMP(y->key, z->key) < 0) {
    y->right = z;
  }
  else {
    y->right = z;
  }
  z->left = D->nil;
  z->right = D->nil;
  
  z->color = 1;
  
  insertFix(D, z);
  D->size += 1;
  return;
}

// insertFix()
// Takes care of insert's edge cases and puts them in correct order
void insertFix(Dictionary D, Node z) {
  while (z->parent->color == 1) {
    if (z->parent == z->parent->parent->left) {
      Node y = z->parent->parent->right;
      // case 1
      if (y->color == 1) {
        z->parent->color = 0;
        y->color = 0;
        z->parent->parent->color = 1;
        z = z->parent->parent;
      }
      else {
        // case 2
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(D, z);
        }
        // case 3
        z->parent->color = 0;
        z->parent->parent->color = 1;
        rightRotate(D, z->parent->parent);
        
      }
    }
    else {
      Node y = z->parent->parent->left;
      // case 4
      if (y->color == 1) {
        z->parent->color = 0;
        y->color = 0;
        z->parent->parent->color = 1;
        z = z->parent->parent;
      }
      else {
        // case 4
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(D, z);
        }
        // case 5
        z->parent->color = 0;
        z->parent->parent->color = 1;
        leftRotate(D, z->parent->parent);
      }
    }
  }
  D->root->color = 0;
}

// TreeMinimum()
// Returns the left most node of the input node
Node TreeMinimum(Dictionary D, Node x) {
  while (x->left != D->nil) {
    x = x->left;
  }
  return x;
}

// TreeMaximum()
// Return the right most node of the input node
Node TreeMaximum(Dictionary D, Node x) {
  while (x->right != D->nil) {
    x = x->right;
  }
  if (x->right == D->nil) {
    
  }
  return x;
}

//Transplant()
// places a node in the right place and sets it's values
void transplant(Dictionary D, Node u, Node v) {
  if (u->parent == D->nil) {
    D->root = v;
  }
  else if (u == u->parent->left) {
    u->parent->left = v;
  }
  else {
    u->parent->right = v;
  }
  v->parent = u->parent;
  return;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k) {
  Node x = NULL;
  Node z = findKey(D ,D->root, k);
  if (z == D->cursor) {
    D->cursor = NULL;
  }
  Node y = z;
  int ogcolor = y->color;
  if (z->left == D->nil) {
    x = z->right;
    transplant(D, z, z->right);
  }
  else if (z->right == D->nil) {
    x = z->left;
    transplant(D, z, z->left);
  }
  else {
    y = TreeMinimum(D, z->right);
    ogcolor = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    }
    else {
      transplant(D, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(D, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (ogcolor == 0) {
    deleteFix(D, x);
  }
  freeNode(&z);
  D->size -= 1;
  return;
}

// deleteFix()
// Takes care of deelete's edge cases and puts them in correct order
void deleteFix(Dictionary D, Node x) {
  Node w = NULL;
  while (x != D->root && x->color == 0) {
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == 1) {
        w->color = 0;                         // case 1
        x->parent->color = 1;                 // case 1
        leftRotate(D, x->parent);              // case 1
        w = x->parent->right;                 // case 1
      }
      if (w->left->color == 0 && w->right->color == 0) {
        w->color = 1;                         // case 2
        x = x->parent;
      }
      else {
        if (w->right->color == 0) {
          w->left->color = 0;                // case 3
          w->color = 1;                       // case 3
          rightRotate(D, w);                  // case 3
          w = x->parent->right;                  // case 3
        }
        w->color = x->parent->color;               // case 4
        x->parent->color = 0;                 // case 4
        w->right->color = 0;                  // case 4
        leftRotate(D, x->parent);                // case 4
        x = D->root;
      }
    }
    else {
      w = x->parent->left;
      if (w->color == 1) {
        w->color = 0;                        // case 5
        x->parent->color = 1;                   // case 5
        rightRotate(D, x->parent);               // case 5
        w = x->parent->left;                      // case 5
      }
      if (w->right->color == 0 && w->left->color == 0) {
        w->color = 1;                         // case 6
        x = x->parent;                           // case 6
      }
      else {
        if (w->left->color == 0) {
          w->right->color = 0;               // case 7
          w->color = 1;                       // case 7
          leftRotate(D, w);                    // case 7
          w = x->parent->left;                   // case 7
        }
              
        w->color = x->parent->color;               // case 8
        x->parent->color = 0;                 // case 8
        w->left->color = 0;                   // case 8
        rightRotate(D, x->parent);               // case 8
        x = D->root;
      }
    }
  }
  x->color = 0;
  return;
  
}

// deleteAll()
// deletes all the Nodes in the subtree rooted at r
void deleteAll(Dictionary D ,Node r) {
  if (r != D->nil) {
    deleteAll(D ,r->left);
    deleteAll(D ,r->right);
    freeNode(&r);
  }
  return;
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D) {
  if (D==NULL ) {
     printf("Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
     exit(1);
  }
  if (D->root != NULL) {
    deleteAll(D, D->root);
  }
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
  D->cursor = TreeMinimum(D ,D->root);
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
  D->cursor = TreeMaximum(D ,D->root);
  return D->cursor->val;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D) {
  if (D->cursor == NULL || D->cursor == D->nil) {
    return KEY_UNDEF;
  }
  return D->cursor->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D) {
  if ( D->cursor == NULL || D->cursor == D->nil) {
    return VAL_UNDEF;
  }
  return D->cursor->val;
}

// treeSuccessor()
// returns the next node in D to be processed in an in-order tree walk
Node treeSuccessor(Dictionary D) {
  Node x = D->cursor, y = D->nil;
  if (x == D->nil) {
    return D->nil;
  }
  if (x->right != D->nil) {
    return TreeMinimum(D ,x->right);
  }
  
  y = x->parent;
  while (y != D->nil && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

// treePredecessor()
// return the prev node in D to be processed in an in-order tree walk.
Node treePredecessor(Dictionary D) {
  Node x = D->cursor, y = D->nil;
  if (x == D->nil) {
    return D->nil;
  }
  if (x->left != D->nil) {
    return TreeMaximum(D ,x->left);
  }
  y = x->parent;
  while (y != D->nil && x == y->left) {
    x = y;
    y = y->parent;
  }
  D->cursor = y;
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
  
  if (D->cursor == D->nil) {
    return VAL_UNDEF;
  }
  /*
  if (D->cursor->key == KEY_UNDEF && D->cursor->val == VAL_UNDEF) {
    freeNode(&D->cursor);
    D->cursor = D->nil;
  }
  */
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
  if (D->cursor == D->nil) {
    return VAL_UNDEF;
  }
  return currentVal(D);
}


// Other operations -----------------------------------------------------------

// printDictionary()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printDictionary(FILE* out, Dictionary D, const char* ord) {
  if (KEY_CMP(ord, "in") == 0) {
    fprintf(out,"******************************************************\n");
    fprintf(out, "IN-ORDER:\n");
    fprintf(out, "******************************************************\n");
    inorder(D, out, D->root);
  }
  else if (KEY_CMP(ord, "pre") == 0) {
    fprintf(out,"******************************************************\n");
    fprintf(out, "PRE-ORDER:\n");
    fprintf(out, "******************************************************\n");
    preorder(D, out, D->root);
  }
  else if (KEY_CMP(ord, "post") == 0) {
    fprintf(out,"******************************************************\n");
    fprintf(out, "POST-ORDER:\n");
    fprintf(out, "******************************************************\n");
    postorder(D, out, D->root);
  }
  return;
}

// inorder()
// prints the dictionary in order of KEY_CMP() using in-order tree traversal
void inorder(Dictionary D, FILE* out, Node r) {
  if (r != D->nil) {
    inorder(D,out, r->left);
    fprintf(out, "%s\n", r->key);
    inorder(D,out, r->right);
  }
  return;
}

// preorder()
// prints the dictionary in order of KEY_CMP() using in-order tree traversal
void preorder(Dictionary D, FILE* out, Node r) {
  if (r != D->nil) {
    fprintf(out, "%s\n", r->key);
    preorder(D,out, r->left);
    preorder(D,out, r->right);
  }
  return;
}

// postorder()
// prints the dictionary in order of KEY_CMP() using in-order tree traversal
void postorder(Dictionary D, FILE* out, Node r) {
  if (r != D->nil) {
    postorder(D,out, r->left);
    postorder(D,out, r->right);
    fprintf(out, "%s\n", r->key);
  }
  return;
}
