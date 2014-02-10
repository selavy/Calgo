#ifndef _GENERAL_TYPES_H_
#define _GENERAL_TYPES_H_

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

typedef double capital;
typedef long shares;

#define TRUE 1
#define FALSE 0

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
  time_t start_date;
  time_t end_date;
} security_t;

typedef struct
{
  security_t * security;
  shares amount;
} order_t;


#endif
