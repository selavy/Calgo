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
  time_t start_date;
  hash_t * positions;
} portfolio_t;

/**
 * function: portfolio_new()
 * preconditions:  none
 * postconditions: +heap memory is allocated for a portfolio_t struct
 *                 +portfolio settings are set to 0
 *                 +positions hash table is initialized
 * parameters:     none
 * notes:          should pair call to this with portfolio_delete()
 */
portfolio_t * portfolio_new( time_t start_date );

/**
 * function: portfolio_delete()
 * preconditions:  +either portfolio is NULL or points to a heap allocated portfolio_t struct
 *                 +portfolio->positions should either be NULL or point to a heap allocated hash_t struct
 * postconditions: +heap memory is deallocated
 *                 +(*portfolio) is set to NULL
 * notes:
 */
void portfolio_delete( portfolio_t ** portfolio );

#endif
