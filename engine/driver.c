#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "database.h"

void strategy( const date * curr_date, const portfolio_t * portfolio, void * args );
capital commission( const order_t * order, void * args );
capital slippage( const order_t * order, void * args );

int main(int argc, char ** argv)
{
  struct tm * start_tm;
  date now = time( NULL ), start;

  start_tm = localtime( &now );
  start_tm->tm_mday = 5;
  start = mktime( start_tm );

  printf("beginning...\n");

  engine_init();
  engine_register_strategy( &strategy );
  engine_register_commission_fn( &commission );
  engine_register_slippage_fn( &slippage );
  engine_set_start_date( &start );
  engine_set_end_date( &now );
  engine_run( stdout );
  engine_cleanup();
  return 0;
}

void strategy( const date * curr_date, const portfolio_t * portfolio, void * args ) {
  order( "AAA", 1 );
}

capital commission( const order_t * order, void * args ) {
  return 0.03f;
}

capital slippage( const order_t * order, void * args ) {
  const capital current_volume = database_get_volume( order->symbol, &(order->datestamp) );
  const capital order_amount = order->amount * database_get_price( order->symbol, &(order->datestamp) );
  const capital div = order_amount / current_volume;
  const double impact = .05;
  return (div * div * impact);
}

