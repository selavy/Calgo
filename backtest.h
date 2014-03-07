#ifndef _BACKTEST_H_
#define _BACKTEST_H_

#include <string.h>
#include <time.h>
#include "queue.h"
#include "engine.h"
#include "general_types.h"
#include "strategy.h"

extern "C" {

/**
 * function: init()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
extern void init();

/**
 * function: cleanup()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
extern void cleanup();

/**
 * function: run()
 * parameters:
 * preconditions:
 * postconditions:
 * returns:
 * notes:
 */
extern void run();

}

#endif
