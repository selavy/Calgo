#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash_table.h"

/* #define N 20000 */
#ifndef savestring
#define savestring(x) (strcpy( malloc(strlen(x) + 1), (x) ))
#endif

inline uint64_t rdtsc() {
  uint32_t lo, hi;
  __asm__ __volatile__ (
			"xorl %%eax, %%eax\n"
			"cpuid\n"
			"rdtsc\n"
			: "=a" (lo), "=d" (hi)
			:
			: "%ebx", "%ecx");
  return (uint64_t)hi << 32 | lo;
}

typedef struct {
  char * name;
  int i;
} position_t;

int main( int argc, char **argv )
{
  hash_t * tbl;
  char line[25];
  int i = 0;
  FILE * in;
  char * found;

  char * text[2794];
  
  if( argc == 2 )
    {
      in = fopen( argv[1], "r" );
    }
  else
    {
      in = fopen( "nasdaq.symbols", "r" );
    }

  if( in == NULL ) return 1;

  hash_init( &tbl );

  while( 1 == fscanf( in, "%s\n", line ) )
    {
      text[i] = savestring(line);
      ++i;
    }

  for( i = 0; i < 2794; ++i )
    {
      position_t * pos = malloc( sizeof( *pos ) );
      pos->name = text[i];
      pos->i = i;
      hash_insert( &tbl, text[i], pos );
    }

  found = hash_contains( tbl, "AAIT" );
  if( found )
    {
      printf("found\n");
    }
  else
    printf("not found\n");

  hash_remove( &tbl, "AAIT" );

  found = hash_contains( tbl, "AAIT" );

  hash_delete( &tbl );

  for( i = 0; i < 2794; ++i )
    {
      free( text[i] );
    }
  fclose( in );
  return 0;
}
