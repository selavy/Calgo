#include "backtest.h"

void init() {
  struct tm * start_tm;
  date now = time( NULL ), start;

  start_tm = localtime( &now );
  start_tm->tm_year = 75; /* 1900 + 75 = 1975 */
  start = mktime( start_tm );

  engine_init();
  engine_register_strategy( &strategy );
  engine_set_start_date( &start );
  engine_set_end_date( &now );
}

void run() {
  engine_run( stdout, strategy_init() );
}

void cleanup() {
  engine_cleanup();
}
