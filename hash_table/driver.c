#include <stdlib.h>
#include "hash_table.h"

#define N 20000

int main( int argc, char **argv )
{
  hash_t * tbl;
  int * a, i;
  /* int b = 6;
     int c = 7; */

  hash_init( &tbl );

  for( i = 0; i < N; ++i )
    {
      a = malloc( sizeof( *a ) );
      *a = i;
      hash_insert( &tbl, a, sizeof( *a ) );
    }

  hash_delete( &tbl );
  return 0;
}
