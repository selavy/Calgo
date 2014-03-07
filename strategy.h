#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "general_types.h"
#include "portfolio.h"
#include "engine.h"

extern "C" {

extern void* strategy_init();
extern void* strategy( const date * curr_date, const portfolio_t * portfolio, void * args );

}

#endif
