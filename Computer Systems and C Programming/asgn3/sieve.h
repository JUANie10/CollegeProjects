// sieve.h - Header file for the Sieve of Eratosthenes function.
//code by DDEL
#ifndef __SIEVE_H__
#define __SIEVE_H__

#include "bv.h"

//
// The Sieve of Eratosthenes.
// Set bits in a BitVector represent prime numbers.
// Composite numbers are sieved out by clearing bits.
//
// v : The BitVector to sieve.
//
void sieve(BitVector *v) ;

#endif
