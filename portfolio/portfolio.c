#include "portfolio.h"

portfolio_t * portfolio_create( time_t start_date ) {
  portfolio_t * portfolio = malloc( sizeof( *portfolio ) );
  if( portfolio == NULL ) return NULL;
  portfolio->capital_used = 0.0f;
  portfolio->cash_available = 0.0f;
  portfolio->positions_value = 0.0f;
  portfolio->starting_cash = 0.0f;
  portfolio->start_date = start_date;
  hash_init( &(portfolio->positions) );
  return portfolio;
}

void portfolio_delete( portfolio_t ** portfolio ) {
  if( *portfolio == NULL ) return;
  if( (*portfolio)->positions != NULL )
    hash_delete( &((*portfolio)->positions) );
  free( *portfolio );
  *portfolio = NULL;
}
