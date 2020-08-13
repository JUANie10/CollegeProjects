// bv.h - Contains the function declarations for the BitVector ADT.

#ifndef __BV_H__
#define __BV_H__

#include <inttypes.h>
#include <stdbool.h>

//
// Struct definition for a BitVector.
//
// vector : The vector of bytes to hold bits.
// length : The length in bits of the BitVector.
//
typedef struct BitVector {
  uint8_t *vector;
  uint32_t length;
} BitVector;

//
// Creates a new BitVector of specified length.
//
// bit_len : The length in bits of the BitVector.
//
BitVector *bv_create(uint32_t bit_len);

//
// Frees memory allocated for a BitVector.
//
// v : The BitVector.
//
void bv_delete(BitVector * v);

//
// Returns the length in bits of the BitVector.
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v);

//
// Sets the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to set.
//
void bv_set_bit(BitVector *v, uint32_t i);

//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i);

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i);

//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v);

#endif
