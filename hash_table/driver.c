#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash_table.h"

/* #define N 20000 */
#define savestring(x) (strcpy( malloc(strlen(x) + 1), (x) ))

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

int str_cmp( const void * data1, const void * data2 )
{
  const char * str1 = (char*) data1;
  const char * str2 = (char*) data2;

  /* printf("comparing %s to %s\n", str1, str2 ); */
  return ( strcmp( str1, str2 ) == 0 ) ? 1 : 0;
}

int main( int argc, char **argv )
{
  hash_t * tbl;
  /*  char * a; */
  char line[25];
  int i = 0;
  FILE * in;
  clock_t t;
  /* uint64_t x, y; */
  char * found;
  /* time_t t1, t2; */
  /* double seconds; */

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

  /*  for( i = 0; i < N; ++i ) */
  while( 1 == fscanf( in, "%s\n", line ) )
    {
      /* a = savestring(line); */
      /* strcpy( text[i], line ); */
      text[i] = savestring(line);
      /* hash_insert( &tbl, a, sizeof( *a ) ); */
      ++i;
    }

  /* t = clock(); */
  /* x = rdtsc(); */
  /* time( &t1 ); */
  for( i = 0; i < 2794; ++i )
    {
      hash_insert( &tbl, text[i], strlen(text[i]) );
    }
  /* y = rdtsc(); */
  /* t = clock() - t; */
  /* time( &t2 ); */
  /* seconds = difftime( t2, t1 ); */
  /* printf("%"PRIu64"\n", y - x ); */
  /* printf("%f seconds.\n", seconds ); */
  
  t = clock();
  found = hash_contains( tbl, "AAIT", strlen("AAIT"), str_cmp );
  t = clock() - t;
  printf("%d ticks. (%f seconds)\n", (int)t, (double) t / CLOCKS_PER_SEC );
  if( found )
    {
      printf("found\n");
    }
  else
    printf("not found\n");

  

  hash_delete( &tbl );
  fclose( in );
  return 0;
}
