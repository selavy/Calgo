#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <Python.h>
#include "portfolio.h"
#include "queue.h"
#include "general_types.h"
#include "database.h"

#define SEC_IN_DAY 86400
#define SEC_IN_MIN 60

  /*
typedef void* (*strategy_fn)(const date *, const portfolio_t *, void *);
typedef capital (*commission_fn)(const order_t *, void *);
typedef capital (*slippage_fn)(const order_t *, void *);
typedef void* (*strategy_init_fn)();
  */

/**
 * function: engine_init()
 * parameters:
 * preconditions: 
 * postconditions: instance of an engine is prepared to run
 * returns:
 * notes: must be paired with call to engine_cleanup()
 */
extern int  engine_init(void);

/**
 * function: engine_register_strategy()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
extern void engine_register_strategy( PyObject* fn );

/**
 * function: engine_register_commission_fn()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
extern void engine_register_commission_fn( PyObject* fn );

/**
 * function: engine_register_slippage_fn()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
extern void engine_register_slippage_fn( PyObject* fn );

/**
 * function: engine_set_start_date()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
extern void engine_set_start_date( const date * start_date );

/**
 * function: engine_set_end_date()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
extern void engine_set_end_date( const date * end_date );

/**
 * function: engine_run()
 * parameters:     +out : FILE pointer to stream to which to output
 *                 +data: void* that will be passed to strategy can be used to maintain state 
                          in strategy
 * preconditions:  +engine_init() has been called
 * postconditions: +engine is run on specified date range as setup with engine_set_start_date()
 *                  and engine_set_end_date() using the given strategy function
 *                 +will print the output of the strategy to out
 * returns:
 * notes:
 */
extern void engine_run( FILE * out, void * data );

/**
 * function: engine_cleanup()
 * parameters:
 * preconditions:  +engine_t structure initialized
 * postconditions: +engine_t structure freed
 * returns:
 * notes: must be paired with engine_init()
 */
extern void engine_cleanup(void);

/**
 * function: engine_order()
 * parameters:     +symbol: stock symbol to be ordered
 *                 +amount: number of shares to buy or sell
 * preconditions:
 * postconditions: +order_t structure placed in engine->order_queue
 * returns:
 * notes: amount > 0 means buy, amount < 0 means sell
 */
extern void engine_order( const char * symbol, shares amount );

extern date engine_get_date(void);
extern long engine_get_granularity(void);

extern portfolio_t * get_portfolio(void);

#endif
