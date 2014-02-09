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

void portfolio_init( portfolio_t * portfolio, time_t start_date );

#endif
