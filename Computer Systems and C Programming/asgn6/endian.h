// Code by DDEL
#ifndef __ENDIAN_H__
#define __ENDIAN_H__

#include <inttypes.h>
#include <stdbool.h>

//
// Checks if the order of bytes on the system is big endian.
//
static inline bool is_big(void) {
  union {
    uint8_t bytes[2];
    uint16_t word;
  } test;
  test.word = 0xFF00;
  return test.bytes[0];
}

//
// Checks if the order of bytes on the system is little endian.
//
static inline bool is_little(void) {
  return !is_big();
}

//
// Swaps the endianness of a uint16_t.
//
// x: The uint16_t.
//
static inline uint16_t swap16(uint16_t x) {
  uint16_t result = 0;
  result |= (x & 0x00FF) << 8;
  result |= (x & 0xFF00) >> 8;
  return result;
}

//
// Swaps the endianness of a uint32_t.
//
// x: The uint32_t.
//
static inline uint32_t swap32(uint32_t x) {
  uint32_t result = 0;
  result |= (x & 0x000000FF) << 24;
  result |= (x & 0x0000FF00) << 8;
  result |= (x & 0x00FF0000) >> 8;
  result |= (x & 0xFF000000) >> 24;
  return result;
}

//
// Swaps the endianness of a uint64_t.
//
// x: the uint64_t.
//
static inline uint64_t swap64(uint64_t x) {
  uint64_t result = 0;
  result |= (x & 0x00000000000000FF) << 56;
  result |= (x & 0x000000000000FF00) << 40;
  result |= (x & 0x0000000000FF0000) << 24;
  result |= (x & 0x00000000FF000000) << 8;
  result |= (x & 0x000000FF00000000) >> 8;
  result |= (x & 0x0000FF0000000000) >> 24;
  result |= (x & 0x00FF000000000000) >> 40;
  result |= (x & 0xFF00000000000000) >> 56;
  return result;
}

#endif
