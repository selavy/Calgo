#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "general_types.h"
#include "portfolio.h"
#include "queue.h"
#include "database.h"
#include <stdio.h> /* for FILE */

#define SEC_IN_DAY 86400
#define SEC_IN_MIN 60

typedef void (*strategy_fn)(const date *, const portfolio_t *, void *);
typedef capital (*commission_fn)(const order_t *, void *);
typedef capital (*slippage_fn)(const order_t *, void *);

int  engine_init();
void engine_register_strategy( strategy_fn fn );
void engine_register_commission_fn( commission_fn fn );
void engine_register_slippage_fn( slippage_fn fn );
void engine_set_start_date( const date * start_date );
void engine_set_end_date( const date * end_date );
void engine_run( FILE * out );
void engine_cleanup();
void order( const char * symbol, shares amount );

#endif
