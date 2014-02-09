#ifndef _HASH_H_
#define _HASH_H_

/* from www.azillionmonkeys.com/qed/hash.html */

#include <stdint.h>

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
uint32_t fnv_hash_32( const void * data, int len );

#define FNV_32_PRIME ((uint32_t)0x01000193)

#ifndef NULL
#define NULL 0
#endif

#if defined(_MSC_VER)

#define ROTL32(x,y) _rotl(x,y)
#define ROTL64(x,y) _rotl64(x,y)

#define BIG_CONSTANT(x) (x)

#else // defined(_MSC_VER)

static inline uint32_t rotl32( uint32_t x, int8_t r )
{
  return (x << r) | (x >> (32 - r));
}

static inline uint64_t rotl64( uint64_t x, int8_t r )
{
  return (x << r) | (x >> (64 - r));
}

#define ROTL32(x,y) rotl32(x,y)
#define ROTL64(x,y) rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

#endif // !defined(_MSC_VER)

static inline uint32_t getblock32( const uint32_t * p, int i );
static inline uint32_t fmix32( uint32_t h );
uint32_t murmurhash3_x86_32( const void * key, int len );

#endif // ifndef _HASH_H_
