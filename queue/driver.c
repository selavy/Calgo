#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


#define copy(x) (memcpy(malloc(sizeof(*x)),(x),sizeof(*x)))

int main(int argc, char ** argv )
{
  queue_t * queue;
  int *a, i;
  
  queue = queue_create();
  
  for( i = 0; i < 10; ++i )
    {
      a = copy(&i);
      queue_enqueue( queue, a );
    }

  while( queue->size )
    {
      a = queue_dequeue( queue );
      printf("%i ", *a);
      free( a );
    }

  queue_delete( &queue, NULL );
  return 0;
}
