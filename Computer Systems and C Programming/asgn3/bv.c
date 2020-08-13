#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "bv.h"

//
// Creates a new BitVector of specified length.
//
// bit_len : The length in bits of the BitVector.
//
BitVector *bv_create(uint32_t bit_len) {
  //allocating space for for the newbitvector and the vector
  BitVector *newBitVector = (BitVector*) malloc(sizeof(BitVector));
  newBitVector->vector = (uint8_t*) malloc(8*bit_len);
  newBitVector->length = bit_len;
  return newBitVector;
}

//
// Frees memory allocated for a BitVector.
//
// v : The BitVector.
//
void bv_delete(BitVector * v) {
  //frees the data in bitvector and vector
  free(v);
  free(v->vector);
}

//
// Returns the length in bits of the BitVector.
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v) {
  // Returns the length of the bitvector in bits
  return v->length;
}

//
// Sets the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to set.
//
void bv_set_bit(BitVector *v, uint32_t i) {
  //gets the index of the vector to set
  int f = i/8;
  //stores the bit shirfting amount
  double bf = i%8;
  int bf1 = (int) bf;
  //sets the correct bit index in the vector
  v->vector[f] |= 1 << bf1;
}
//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  //gets the index of the vector to set
  int f = i/8;
  //stores the bit shirfting amount
  double bf = i%8;
  int bf1 = (int) bf;
  //clears the correct bit index in the vector
  v->vector[f] &= ~(1 << bf1);
}

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  //gets the index of the vector to set
  int f = i/8;
  //stores the bit shirfting amount
  double bf = i%8;
  int bf1 = (int) bf;
  //returns the bit in the correct index of the bit within the vector
  return v->vector[f] >> bf1 & 1;
}
//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  //for the length in bits, sets all the bits in the vector
  for (uint32_t i = 0; i < v->length; i++) {
    bv_set_bit(v, i);
  }
}

