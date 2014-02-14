#include "backtest.h"

void init() {
  struct tm * start_tm;
  date now = time( NULL ), start;

  start_tm = localtime( &now );
  start_tm->tm_year = 100; /* 1900 + 100 = 2000 */
  start = mktime( start_tm );

  engine_init();
  engine_register_strategy( &strategy );
  engine_set_start_date( &start );
  engine_set_end_date( &now );
  engine_run( stdout );
}

void cleanup() {
  engine_cleanup();
}
