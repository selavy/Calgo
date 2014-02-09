#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <string.h>
#include "hash.h"

#define N 900000

typedef uint32_t (*hash_t)(const void*, int);

int main( int argc, char ** argv )
{
  hash_t hash[] = { super_fast_hash, fnv_hash_32, murmurhash3_x86_32 };
  char text[] = "The quick brown fox jumps over the lazy dog.";
  int len = strlen( text );
  int i;
  int v;

  if( argc != 2 ) return 1;
  v = atoi( argv[1] );
  if( (v > 2) || (v < 0) ) return 1;
  for( i = 0; i < N; ++i )
    {
      hash[v](text, len);
    }

  return 0;
}
