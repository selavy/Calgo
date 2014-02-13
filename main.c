#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include "engine.h"
#include "database.h"

static void print_usage_message();
static inline void print_unable_to_open_strategy();
void strat( const date * d, const portfolio_t * p, void * b );
capital commission( const order_t * order, void * args );
capital slippage( const order_t * order, void * args );

int main(int argc, char **argv) {
  void *dynamic_lib;
  strategy_fn strategy;
  char * error;
  struct tm * start_tm;
  date now = time( NULL ), start;

  if( argc > 1 ) {
    print_usage_message();
    exit(0);
  }

  dynamic_lib = dlopen( "./libstrategy.so", RTLD_NOW );
  if( !dynamic_lib )
    {
      print_unable_to_open_strategy();
      if( (error = dlerror()) )
	fprintf( stderr, "%s\n", error );
      exit(0);
    }

  dlerror(); /* clear any old errors */
  strategy = (strategy_fn) dlsym( dynamic_lib, "strategy" );
  if( (error = dlerror()) )
    {
      print_unable_to_open_strategy();
      fprintf( stderr, "%s\n", error );
      exit(0);
    }
  
  start_tm = localtime( &now );
  start_tm->tm_year = 100; /* 1900 + 100 = 2000 */
  start = mktime( start_tm );

  engine_init();
  engine_register_strategy( strategy );
  engine_register_commission_fn( &commission );
  engine_register_slippage_fn( &slippage );
  engine_set_start_date( &start );
  engine_set_end_date( &now );
  engine_run( stdout );
  engine_cleanup();
  dlclose( dynamic_lib );

  return 0;
}

void strat( const date * d, const portfolio_t * p, void * b ) {
  printf("hello");
}

void print_usage_message() {
  /* TODO */
  fputs("Usage message\n", stderr);
}

static inline void print_unable_to_open_strategy() {
  fputs("Unable to open strategy\n", stderr);
}

capital commission( const order_t * order, void * args ) {
  return 0.03f;
}

capital slippage( const order_t * order, void * args ) {
  const capital current_volume = database_get_volume( order->symbol, &(order->datestamp) );
  const capital order_amount = order->amount * database_get_price( order->symbol, &(order->datestamp) );
  const capital div = order_amount / current_volume;
  const double impact = .05;
  const double slippage_val = (div * div * impact);
  return (order->amount > 0) ? slippage_val : -1 * slippage_val;
}
