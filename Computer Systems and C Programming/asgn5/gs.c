#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gs.h"




//
// Constructor for GoodSpeak.
//
// oldspeak: The oldspeak string.
// newspeak: The newspeak string.
//
GoodSpeak *gs_create(char *oldspeak, char *newspeak) {
  GoodSpeak *newgoodspeak = (GoodSpeak*) malloc(sizeof(GoodSpeak)+1);
  
  if (oldspeak != NULL) {
    newgoodspeak->oldspeak = (char*) malloc(strlen(oldspeak)+1);
    newgoodspeak->oldspeak = strdup(oldspeak);
  }
  
  
  if (newspeak != NULL) {
    newgoodspeak->newspeak = (char*) malloc(strlen(newspeak)+1);
    newgoodspeak->newspeak = strdup(newspeak);
  }
  else {
    newgoodspeak->newspeak = NULL;
  }
  
  return newgoodspeak;
}

//
// Deconstructor for GoodSpeak.
//
// g = GoodSpeak struct.
//
void gs_delete(GoodSpeak *g) {
  if (g->oldspeak != NULL) {
    free(g->oldspeak);
  }
  if (g->newspeak != NULL) {
    free(g->newspeak);
  }
  
  free(g);
}

//
// Returns the oldspeak char*
//
// g = GoodSpeak struct.
//
char *gs_oldspeak(GoodSpeak *g) {
  return g->oldspeak;
}

//
// Returns the newspeak char*.
//
// g = GoodSpeak struct.
//
char *gs_newspeak(GoodSpeak *g) {
  if (g->newspeak == NULL) {
    return NULL;
  }
  return g->newspeak;
}
