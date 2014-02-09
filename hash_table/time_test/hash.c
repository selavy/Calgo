#include "hash.h"

uint32_t super_fast_hash( const void * buf, int len ) {
  char * data = (char*) buf;
  uint32_t hash, tmp;
  int rem;

  hash = len;

  if( len <= 0 || data == NULL ) return 0;

  rem = len & 3;
  len >>= 2;

  for(; len > 0; len--) {
    hash += get16bits( data );
    tmp = (get16bits( data + 2 ) << 11) ^ hash;
    hash = (hash << 16) ^ tmp;
    data += 2 * sizeof(uint16_t);
    hash += hash >> 11;
  }

  switch( rem ) {
  case 3: 
    hash += get16bits( data );
    hash ^= hash << 16;
    hash ^= ((signed char) data[sizeof( uint16_t )]) << 18;
    hash += hash >> 11;
    break;
  case 2:
    hash += get16bits( data );
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1:
    hash += (signed char)*data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }

  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;

  return hash;
}

uint32_t fnv_hash_32( const void * data, int len ) {
  unsigned char *bp = (unsigned char*)data;
  unsigned char *be = bp + len;
  uint32_t hash = 0x0;

  while (bp < be) {
    hash *= FNV_32_PRIME;
    hash ^= (uint32_t)*bp++;
  }
   
  return hash;
}

static inline uint32_t getblock32( const uint32_t * p, int i )
{
  return p[i];
}

static inline uint32_t fmix32( uint32_t h )
{
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;

  return h;
}

uint32_t murmurhash3_x86_32( const void * key, int len ) {
  const uint8_t * data = (const uint8_t*) key;
  const int nblocks = len / 4;
  
  uint32_t h1 = len; /* use length for seed */

  const uint32_t c1 = 0xcc9e2d51;
  const uint32_t c2 = 0x1b873593;

  const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);
  int i;
  for( i = -nblocks; i != 0; i++ )
    {
      uint32_t k1 = getblock32(blocks, i);

      k1 *= c1;
      k1 = ROTL32(k1,15);
      k1 *= c2;

      h1 ^= k1;
      h1 = ROTL32(h1,13);
      h1 = h1*5+0xe6546b64;
    }

  const uint8_t * tail = (const uint8_t*)(data + nblocks*4);

  uint32_t k1 = 0;

  switch( len & 3 )
    {
    case 3: k1 ^= tail[2] << 16;
    case 2: k1 ^= tail[1] << 8;
    case 1: k1 ^= tail[0];
      k1 *= c1; k1 = ROTL32(k1, 15); k1 *= c2; h1 ^= k1;
    }

  h1 ^= len;
  h1 = fmix32( h1 );
  return h1;
}
