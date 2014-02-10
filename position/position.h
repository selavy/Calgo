#ifndef _POSITION_H_
#define _POSITION_H_

#include "general_types.h"

typedef struct _position_t
{
  char * symbol;
  shares num_of_shares;
  capital cost_basis;
} position_t;

#endif
