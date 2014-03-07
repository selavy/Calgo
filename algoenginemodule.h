#ifndef _ALGOENGINEMODULE_
#define _ALGOENGINEMODULE_

#include "Python.h"
#include "general_types.h"

PyMODINIT_FUNC initalgoengine(void);
capital slippage(const order_t *, void *);
capital commission(const order_t *, void *);

#endif
