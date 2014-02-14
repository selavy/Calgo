#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "general_types.h"
#include "portfolio.h"

extern void order( const char * symbol, shares amount );

void strategy_init();
void strategy( const date * curr_date, const portfolio_t * portfolio, void * args );

#endif
