#ifndef _GENERAL_TYPES_H_
#define _GENERAL_TYPES_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * macro: savestring()
 * parameters:     +x : string to be copied
 * preconditions:  +x is null-terminated string
 *                 +memory of size strlen(x) + 1 is available
 * postconditions: +memory is allocated the size of x
 *                 +the string in x is copied to the new memory
 * returns:        +pointer to new memory where x was copied
 * notes: does not handle malloc failing to allocate memory
 */
#define savestring(x) (strcpy( malloc(strlen(x) + 1), (x) ))

#define TRUE 1
#define FALSE 0

typedef double capital;
typedef long shares;
typedef time_t date;

typedef struct
{
  char * symbol;
  shares num_of_shares;
  capital cost_basis;
} position_t;

typedef struct
{
  /* int id; */
  char * symbol;
  char * full_name;
  date start_date;
  date end_date;
} security_t;

typedef struct
{
  date datestamp;
  char * symbol;
  shares amount;
} order_t;

typedef struct
{
  date datestamp;
  char * symbol;
  shares amount;
  capital price_per_share;
} filled_order_t;

typedef struct
{
  date datestamp;
  capital capital_used;
  capital realized_gains;
  capital unreaslized_gains;
  capital profit_n_loss;
  capital positions_value;
} bar_evnt_t;

#endif
