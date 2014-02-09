#include "portfolio.h"

void portfolio_init( portfolio_t * portfolio, time_t start_date ) {
  portfolio->capital_used = 0.0f;
  portfolio->cash_available = 0.0f;
  portfolio->positions_value = 0.0f;
  portfolio->starting_cash = 0.0f;
  portfolio->start_date = start_date;
  hash_init( &(portfolio->positions) );
}
