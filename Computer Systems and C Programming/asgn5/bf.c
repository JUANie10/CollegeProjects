#include "bf.h"
#include <stdlib.h>
#include <stdio.h>


//
// Constructor for a Bloomfilter.
//
// size: The number of entries in the Bloomfilter.
//
// Code by DDEL
BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter)+1);
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7; // U.S. Constitution
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3; // Il nome della rosa
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0; // The Cremation of Sam McGee
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    return bf;
  }
  return (BloomFilter *)NIL;
}

//
// Destructor for a BloomFilter.
//
// bf: The BloomFilter.
//
void bf_delete(BloomFilter *bf) {
  
  bv_delete(bf->filter);
  free(bf);
}

//
// Inserts a new key into the BloomFilter.
// Indices to set bits are given by the hash function.
//
// bf: The BloomFilter.
// key: The key to insert into the BloomFilter.
//
void bf_insert(BloomFilter *bf, char *key) {
  uint32_t index1 = hash(bf->primary, key) % bf->filter->length;
  uint32_t index2 = hash(bf->secondary, key) % bf->filter->length;
  uint32_t index3 = hash(bf->tertiary, key) % bf->filter->length;
  bv_set_bit(bf->filter, index1);
  bv_set_bit(bf->filter, index2);
  bv_set_bit(bf->filter, index3);
}

//
// Probes a BloomFilter to check if a key has been inserted.
// Returns true if the key has already been inserted.
//
// bf: The BloomFilter.
// key: The key in which to check membership.
//
bool bf_probe(BloomFilter *bf, char *key) {
  uint32_t index1 = hash(bf->primary, key) % bf->filter->length;
  uint32_t index2 = hash(bf->secondary, key) % bf->filter->length;
  uint32_t index3 = hash(bf->tertiary, key) % bf->filter->length;
  uint8_t bit1 = bv_get_bit(bf->filter, index1);
  uint8_t bit2 = bv_get_bit(bf->filter, index2);
  uint8_t bit3 = bv_get_bit(bf->filter, index3);
  if (bit1 && bit2 && bit3) {
    return true;
  }
  else {
    return false;
  }
}
