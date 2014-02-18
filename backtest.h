#ifndef _BACKTEST_H_
#define _BACKTEST_H_

#include <string.h>
#include <time.h>
#include "queue.h"
#include "engine.h"
#include "general_types.h"
#include "strategy.h"

void init();
void cleanup();
void run();

#endif
