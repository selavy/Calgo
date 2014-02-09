#ifndef _HASH_H_
#define _HASH_H_

/* from www.azillionmonkeys.com/qed/hash.html */

#include <stdint.h>

#ifndef NULL
#define NULL 0
#endif

#undef get16bits
#if (defined(__GNUC__) && defined(__i386)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined(__BORLANDC__) || defined( __TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8) \
		      *(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

uint32_t super_fast_hash( const void * data, int len );

#endif // ifndef _HASH_H_
