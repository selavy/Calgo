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

/**
 * function: engine_init()
 * parameters:
 * preconditions: 
 * postconditions:
 * returns:
 * notes: must be paired with call to engine_cleanup()
 */
int  engine_init();

/**
 * function: engine_register_strategy()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
void engine_register_strategy( strategy_fn fn );

/**
 * function: engine_register_commission_fn()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
void engine_register_commission_fn( commission_fn fn );

/**
 * function: engine_register_slippage_fn()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
void engine_register_slippage_fn( slippage_fn fn );

/**
 * function: engine_set_start_date()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
void engine_set_start_date( const date * start_date );

/**
 * function: engine_set_end_date()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
void engine_set_end_date( const date * end_date );

/**
 * function: engine_run()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
void engine_run( FILE * out );

/**
 * function: engine_cleanup()
 * parameters:
 * preconditions:  +engine_t structure initialized
 * postconditions: +engine_t structure freed
 * returns:
 * notes: must be paired with engine_init()
 */
void engine_cleanup();

/**
 * function: order()
 * parameters:     +symbol: stock symbol to be ordered
 *                 +amount: number of shares to buy or sell
 * preconditions:
 * postconditions: +order_t structure placed in engine->order_queue
 * returns:
 * notes: amount > 0 means buy, amount < 0 means sell
 */
void order( const char * symbol, shares amount );

#endif
