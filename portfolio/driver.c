#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "portfolio.h"
#include "general_types.h"

int main(int argc, char **argv) {
  portfolio_t * portfolio; 
  hash_node_t * node;
  char * str;
  portfolio = portfolio_create( time(NULL) );
  portfolio->starting_cash = 1000;
  str = savestring("AIIT");
  hash_insert( &(portfolio->positions), "AIIT", str );
  str = savestring("ABC");
  hash_insert( &(portfolio->positions), "ABC", str );
  node = hash_get_node( portfolio->positions, "ABC" );
  if( node != NULL )
    {
      free( node->data );
      node->data = (void*) savestring("NEW STRING");
    }
  node = hash_get_node( portfolio->positions, "ABC" );
  printf("%s\n", (char*) node->data );

  portfolio_delete( &portfolio );
  return 0;
}
