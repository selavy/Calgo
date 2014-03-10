#ifndef _QSOLVEMODULE_
#define _QSOLVEMODULE_

#include "Python.h"
#include "general_types.h"
#include "engine.h"

PyMODINIT_FUNC initqsolve(void);
int setup_engine(void);
void set_strategy(PyObject*);
void set_start_date(time_t*);
void set_end_date(time_t*);
void run(void);


#endif
