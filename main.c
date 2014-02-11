#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include "engine.h"
#include "database.h"

static void print_usage_message();
static inline void print_unable_to_open_strategy();

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
  *(void**) (&strategy) = dlsym( dynamic_lib, "strategy" );
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
  engine_register_strategy( (strategy_fn) &strategy );
  /*
  engine_register_commission_fn( &commission );
  engine_register_slippage_fn( &slippage );
  */
  engine_set_start_date( &start );
  engine_set_end_date( &now );
  engine_run( stdout );
  engine_cleanup();
  dlclose( dynamic_lib );

  return 0;
}

void print_usage_message() {
  /* TODO */
  fputs("Usage message\n", stderr);
}

static inline void print_unable_to_open_strategy() {
  fputs("Unable to open strategy\n", stderr);
}
