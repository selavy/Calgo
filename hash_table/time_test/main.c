#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include "hash.h"

#define N 4000
#define T 15

typedef uint32_t (*hash_func)(const void*, int);

int main( int argc, char **argv )
{
  FILE * file;
  char line[20];
  uint32_t hashval;
  int buckets[N], num_inputs, i, j, k, empty = 0, hist[T];
  // int count = 0;
  char text[3000][20];
  time_t t, diff;
  double tsec;
  hash_func hashers[] = { super_fast_hash, fnv_hash_32, murmurhash3_x86_32 };

  file = fopen( "nasdaq.symbols", "r" );
  if( file == NULL )
    {
      fputs( "unable to open file!\n", stderr );
      exit(1);
    }

  for( i = 0; (i < 3000) && ( fscanf( file, "%s\n", line ) == 1 ); ++i )
    {
      strcpy( text[i], line );
    }
  
  num_inputs = i;
  
  for( j = 0; j < 3; ++j )
    {
      for( i = 0; i < N; ++i )
	buckets[i] = 0;

      for( i = 0; i < T; ++i )
	hist[T] = 0;
      
      //t = clock();
      time(&t);
      for( i = 0; i < num_inputs; ++i )
	{
	  //diff = clock();
	  hashval = hashers[j]( text[i], strlen( text[i] ) );
	  //diff = clock() - diff;
	  //t += diff;
	  buckets[ hashval % N ]++;
	}
      //t = clock() - t;
      time(&diff);

      for( i = 0; i < N; ++i )
	{
	  if(! buckets[i] )
	    empty++;

	  if( buckets[i] < T )
	    hist[ buckets[i] ]++;
	}

      for( i = 0; i < T; ++i )
	{
	  printf("%d:", i );
	  
	  for( k = 0; k < hist[i]; ++k )
	    printf("X");
	  printf("\n");
	}
      printf("Elements %d\n", num_inputs );
      printf("Load: %f\n", (double) num_inputs / N );
      printf("Empty buckets: %d\n", empty);
      tsec = difftime( diff, t );
      //printf("Took %d clicks (%f seconds).\n", t, ((float)t)/CLOCKS_PER_SEC);
      printf("Took %f seconds.\n", tsec );
      printf("\n------------------------\n\n");

      rewind( file );
      empty = 0;
      // count = 0;
    }

  fclose( file );

  return 0;
}
