#ifndef _HASH_H_
#define _HASH_H_
#include <stdint.h>
#include "general_types.h"

/**
 * macro: get16bits()
 * parameters:     +d : any int with at least 16 bits
 * preconditions:  none
 * postconditions: none
 * returns:        +lowest 16 bits from d
 * notes:
 */
#undef get16bits
#if (defined(__GNUC__) && defined(__i386)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined(__BORLANDC__) || defined( __TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif
#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8) \
		      *(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

/**
 * function: super_fast_hash()
 * parameters:     +data: pointer to data to be hashed
 *                 +len: sizeof of data
 * preconditions:  +len >= 0
 * postconditions:
 * returns:        +32 bit integer hash
 * notes: taken from www.azillionmonkeys.com/qed/hash.html
 */
uint32_t super_fast_hash( const void * data, int len );
#endif /* ifndef _HASH_H_ */
