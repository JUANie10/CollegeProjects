#include "speck.h"
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

//Code by DDEL
// Ray Beaulieu, Stefan Treatman-Clark, Douglas Shors, Bryan Weeks, Jason
// Smith and Louis Wingers. "The SIMON and SPECK lightweight block ciphers,"
// In proceedings of the Design Automation Conference (DAC),
// 2015 52nd ACM/EDAC/IEEE, pp. 1-6. IEEE, 2015.

#define LCS(X, K)                                                              \
  (X << K) | (X >> (sizeof(uint64_t) * 8 - K)) // left circular shift
#define RCS(X, K)                                                              \
  (X >> K) | (X << (sizeof(uint64_t) * 8 - K)) // right circular shift

// Core SPECK operation
#define R(x, y, k) (x = RCS(x, 8), x += y, x ^= k, y = LCS(y, 3), y ^= x)


void speck_expand_key_and_encrypt(uint64_t pt[], uint64_t ct[], uint64_t K[]) {
  uint64_t B = K[1], A = K[0];
  ct[0] = pt[0];
  ct[1] = pt[1];

  for (size_t i = 0; i < 32; i += 1) {
    R(ct[1], ct[0], A);
    R(B, A, i);
  }
}

uint64_t keyed_hash(const char *s, uint32_t length, uint64_t key[]) {
  uint64_t accum = 0;

  union {
    char b[sizeof(uint64_t)]; // 16 bytes fit into the same space as
    uint64_t ll[2]; // 2 64 bit numbers.
  } in;

  uint64_t out[2]; // Speck results in 128 bits of ciphertext
  uint32_t count;

  count = 0; // Reset buffer counter
  in.ll[0] = 0x0;
  in.ll[1] = 0x0; // Reset the input buffer (zero fill)

  for (size_t i = 0; i < length; i += 1) {
    in.b[count++] = s[i]; // Load the bytes

    if (count % (2 * sizeof(uint64_t)) == 0) {
      speck_expand_key_and_encrypt(in.ll, out, key); // Encrypt 16 bytes
      accum ^= out[0] ^ out[1]; // Add (XOR) them in for a 64 bit result
      count = 0; // Reset buffer counter
      in.ll[0] = 0x0;
      in.ll[1] = 0x0; // Reset the input buffer
    }
  }

  // There may be some bytes left over, we should use them.
  if (length % (2 * sizeof(uint64_t)) != 0) {
    speck_expand_key_and_encrypt(in.ll, out, key);
    accum ^= out[0] ^ out[1];
  }

  return accum;
}

uint32_t hash(uint64_t *salt, char *key) {
  union {
    uint64_t full;
    uint32_t half[2];
  } value;

  value.full = keyed_hash(key, strlen(key), salt);

  return value.half[0] ^ value.half[1];
}
