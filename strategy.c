#include "strategy.h"

void* strategy_init() {
  int * a = malloc(sizeof(int));
  *a = 0;
  return a;
}

void* strategy( const date * curr_date, const portfolio_t * portfolio, void * args ) {
  int * a = (int*) args;
  printf("%d\n", (*a)++);
  order( "AAA", 10 );
  return a;
}

