#ifndef _PORTFOLIO_H_
#define _PORTFOLIO_H_

#include <time.h>
#include "general_types.h"
#include "hash_table.h"

typedef struct
{
  capital capital_used;
  capital cash_available;
  capital positions_value;
  capital starting_cash;
  date start_date;
  hash_t * positions;
} portfolio_t;

/**
 * function: portfolio_create()
 * parameters:     +start_date : unix time stamp for beginning date of simulation
 * preconditions:  none
 * postconditions: +heap memory is allocated for a portfolio_t struct
 *                 +portfolio settings are set to 0
 *                 +positions hash table is initialized
 * returns:        +a pointer to the newly created portfolio_t struct
 * notes:          should pair call to this with portfolio_delete()
 */
portfolio_t * portfolio_create( date start_date );

/**
 * function: portfolio_delete()
 * parameters:     +portfolio: the portfolio to be deleted
 * preconditions:  +either portfolio is NULL or points to a heap allocated portfolio_t struct
 *                 +portfolio->positions should either be NULL or point to a heap allocated hash_t struct
 * postconditions: +heap memory is deallocated
 *                 +(*portfolio) is set to NULL
 * returns:        (void)
 * notes:
 */
void portfolio_delete( portfolio_t ** portfolio );

#endif
