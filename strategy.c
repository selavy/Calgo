#include "strategy.h"

void strategy_init() {
}

void strategy( const date * curr_date, const portfolio_t * portfolio, void * args ) {
  order( "AAA", 3 );
}

