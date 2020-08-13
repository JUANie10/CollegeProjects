#ifndef __BF_H__
#define __BF_H__

#include "bv.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>

typedef struct BloomFilter {
  uint64_t primary [2];
  uint64_t secondary [2];
  uint64_t tertiary [2];
  struct BitVector *filter;
} BloomFilter;

BloomFilter *bf_create(uint32_t size);

void bf_delete(BloomFilter *b);

uint32_t bf_length(BloomFilter *b);

void bf_insert(BloomFilter *b, char *key);

bool bf_probe(BloomFilter *b, char *key);

uint32_t bf_count(BloomFilter *b);

#endif
