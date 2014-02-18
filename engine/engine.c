#include "engine.h"

#define _PRINT_

static void engine_order_helper( date date, const char * symbol, shares amount );
static void engine_check_order_queue();
static filled_order_t * engine_execute_order( order_t * order );
static void engine_print_order( const void * const filled_order );

typedef struct {
  strategy_fn strategy;
  commission_fn commission;
  slippage_fn slippage;
  date start_date;
  date end_date;
  date curr_date;
  FILE * out_stream;
  long granularity;

  queue_t * order_queue;
  queue_t * filled_order_queue;
  queue_t * bar_queue;

  portfolio_t * portfolio;
} engine_t;

/* for now just one engine at a time */
static engine_t * engine = NULL;

int engine_init() {
  const date now = time( NULL );
  
  engine = malloc( sizeof( *engine ) );
  if( engine == NULL ) return FALSE;

  engine->strategy = NULL;
  engine->commission = NULL;
  engine->slippage = NULL;
  engine->start_date = now;
  engine->end_date = now;
  engine->curr_date = now;
  engine->out_stream = stdout;
  engine->granularity = SEC_IN_DAY;

  engine->order_queue = queue_create();
  engine->filled_order_queue = queue_create();
  engine->bar_queue = queue_create();
  
  engine->portfolio = portfolio_create( now );
  return TRUE;
}

void engine_register_strategy( strategy_fn fn ) {
  engine->strategy = fn;
}

void engine_register_commission_fn( commission_fn fn ) {
  engine->commission = fn;
}

void engine_register_slippage_fn( slippage_fn fn ) {
  engine->slippage = fn;
}

void engine_set_start_date( const date * start_date ) {
  engine->start_date = *(start_date);
}

void engine_set_end_date( const date * end_date ) {
  engine->end_date = *(end_date);
}

void engine_set_granularity( long granularity ) {
  engine->granularity = granularity;
}

void engine_run( FILE * out ) {
  engine->out_stream = out;
#ifdef _PRINT_
  fprintf( engine->out_stream, "Running engine...\n" );
#endif
  if( !engine->strategy )
    {
      fprintf( engine->out_stream, "No strategy loaded.\n" );
      return;
    }

  engine->curr_date = engine->start_date;
  while( engine->curr_date < engine->end_date )
    {
      engine->strategy( &(engine->curr_date), engine->portfolio, NULL );

      engine_check_order_queue();

      /* TODO : add to bar queue */

      /* increment by granuarlity */
      engine->curr_date += engine->granularity;
    }

#ifdef _PRINT_
  fprintf( engine->out_stream, "Finished.\n" );
#endif
  queue_traverse( engine->filled_order_queue, engine_print_order );
#ifdef _PRINT_
  fprintf( engine->out_stream, "capital used:    %f\ncash available:  %f\npositions value: %f\nstarting cash:   %f\n",
	   engine->portfolio->capital_used,
	   engine->portfolio->cash_available,
	   engine->portfolio->positions_value,
	   engine->portfolio->starting_cash );
#endif

}

static void engine_helper_delete_order_string( void * buf ) {
  order_t * order = (order_t*) buf;
  free( order->symbol );
}

static void engine_helper_delete_filled_order_string( void * buf ) {
  filled_order_t * order = (filled_order_t*) buf;
  free( order->symbol );
}

void engine_cleanup() {
  /* clear the memory in the queues */
  queue_delete( &(engine->order_queue), engine_helper_delete_order_string );
  queue_delete( &(engine->filled_order_queue), engine_helper_delete_filled_order_string );
  queue_delete( &(engine->bar_queue), NULL );

  portfolio_delete( &(engine->portfolio) );
  free( engine );
  engine = NULL;
}

void order( const char * symbol, shares amount ) {
  engine_order_helper( engine->curr_date + engine->granularity, symbol, amount );
  /* engine_order_helper( engine_get_date() + engine_get_granularity(), symbol, amount ); */
}

static void engine_order_helper( date date, const char * symbol, shares amount ) {
  order_t * order = malloc( sizeof(*order) );
  /* TODO: handle if not enough memory for order_t */
  
  order->symbol = savestring( symbol );
  order->amount = amount;
  order->datestamp = date;
  
  queue_enqueue( engine->order_queue, order );
}

static void engine_check_order_queue() {
  order_t * order;
  filled_order_t * filled_order;

  while( engine->order_queue->size ) {
    shares volume, amount_to_purchase, left_over;
    const order_t * const peek = queue_peek( engine->order_queue );
    
    if( peek->datestamp > engine->curr_date )
      break; /* have done all the orders for the day */

    /* we have an order to process, so remove it from the queue */
    order = queue_dequeue( engine->order_queue );
    if( order->amount == 0 )
      {
	free( order->symbol );
	free( order );
	order = NULL;
	continue;
      }

    volume = database_get_volume( order->symbol, &(order->datestamp) ); 
    amount_to_purchase = (order->amount > volume) ? volume : order->amount;
    left_over = order->amount - amount_to_purchase;
    if( left_over > 0 )
      {
	order_t * new_order = malloc( sizeof( *new_order ) );
	strcpy( new_order->symbol, order->symbol );
	new_order->amount = left_over;
	/* schedule the new order for the next day when more volume available */
	new_order->datestamp = order->datestamp + engine->granularity;

	queue_enqueue( engine->order_queue, new_order );
      }

    /* execute order */
    filled_order = engine_execute_order( order );
    if( filled_order != NULL )
      queue_enqueue( engine->filled_order_queue, filled_order );
    free( order->symbol );
    free( order );
  }
}

static void engine_print_order( const void * const filled_order ) {
  const filled_order_t * const o = (filled_order_t*) filled_order;
#ifdef _PRINT_
  printf("%li shares of %s at $%.4f per share at %d\n", (long) o->amount, o->symbol, (double) o->price_per_share, (int) o->datestamp );
#endif
}

static filled_order_t * engine_execute_order( order_t * order ) {
  const shares amount = order->amount;
  const capital slippage = (engine->slippage) ? (engine->slippage)( order, NULL ) : 0.0f;
  const capital commission = (engine->commission) ? (engine->commission)( order, NULL ) : 0.0f;
  const capital price = database_get_price( order->symbol, &(order->datestamp) ) * ( 1 + slippage ) - commission;
  const capital total_spent = price * amount;
  hash_node_t * stock;
  position_t * position;
  filled_order_t * filled_order;
  
  /* check if we already have this stock */
  stock = hash_get_node( engine->portfolio->positions, order->symbol );
  if( stock != NULL )
    {
      position = (position_t*) stock->data;
      position->cost_basis = ((position->cost_basis * position->num_of_shares) + (amount * price)) / (position->num_of_shares + amount );
      position->num_of_shares += order->amount;
    }
  else
    {
      position = malloc( sizeof( *position ) );
      position->cost_basis = price;
      position->num_of_shares = amount;
      hash_insert( &(engine->portfolio->positions), order->symbol, position );
    }

  engine->portfolio->capital_used += total_spent;
  engine->portfolio->cash_available -= total_spent;
  /* TODO : recalc the value of all positions */
  engine->portfolio->positions_value += total_spent;

  if( position->num_of_shares == 0 )
    {
      hash_remove( &(engine->portfolio->positions), order->symbol );
      return NULL;
    }

    filled_order = malloc( sizeof( *filled_order ) );
    if( filled_order == NULL ) return NULL;
    filled_order->datestamp = order->datestamp;
    filled_order->symbol = savestring( order->symbol );
    filled_order->price_per_share = price;
    filled_order->amount = order->amount;
    return filled_order;
}

date engine_get_date() {
  if(!engine)
    engine_init();
  return engine->curr_date;
}

date engine_get_granularity() {
  if(!engine)
    engine_init();
  return engine->granularity;
}

portfolio_t * get_portfolio() {
  return engine->portfolio;
}
