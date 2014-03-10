#include "qsolvemodule.h"

/* #define DEBUG */

static PyObject * get_price(PyObject*, PyObject*);
static PyObject * get_volume(PyObject*, PyObject*);
static PyObject * get_open(PyObject*, PyObject*);
static PyObject * get_close(PyObject*, PyObject*);
static PyObject * get_high(PyObject*, PyObject*);
static PyObject * get_low(PyObject*, PyObject*);
static PyObject * set_commission_func(PyObject*, PyObject*);
static PyObject * set_slippage_func(PyObject*, PyObject*);
static PyObject * order(PyObject*, PyObject*);

static PyMethodDef QSolveMethods[] = {
  {"get_price", get_price, METH_VARARGS, "Get the price of a stock at a given date"},
  {"get_volume", get_volume, METH_VARARGS, "Get the volume of a stock on a given day"},
  {"get_open", get_open, METH_VARARGS, ""},
  {"get_close", get_close, METH_VARARGS, ""},
  {"get_high", get_high, METH_VARARGS, ""},
  {"get_low", get_low, METH_VARARGS, ""},
  {"set_commission_func", set_commission_func, METH_VARARGS, ""},
  {"set_slippage_func", set_slippage_func, METH_VARARGS, ""},
  {"order", order, METH_VARARGS, "order(company_name, amount) : Place an order for a stock"},
  {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyObject *
get_price(PyObject *self, PyObject *args)
{
  printf("Called get_price()\n");
  Py_RETURN_NONE;
}

static PyObject *
get_volume(PyObject *self, PyObject *args)
{
  printf("Called get_volume()\n");
  Py_RETURN_NONE;
}
 
static PyObject *
get_open(PyObject *self, PyObject *args)
{
  printf("Called get_open()\n");
  /* Py_RETURN_NONE; */
  return Py_BuildValue("i", 5);
}

static PyObject *
get_close(PyObject *self, PyObject *args)
{
  printf("Called get_close()\n");
  /* Py_RETURN_NONE; */
  return Py_BuildValue("i", 5);
}

static PyObject *
get_high(PyObject *self, PyObject *args)
{
  printf("Called get_high()\n");
  /* Py_RETURN_NONE; */
  return Py_BuildValue("i", 5);
}

static PyObject *
get_low(PyObject *self, PyObject *args)
{
  printf("Called get_low()\n");
  Py_RETURN_NONE;
}

static PyObject *
set_commission_func(PyObject *self, PyObject *args)
{
  PyObject *temp, *result = NULL;
#ifdef DEBUG
  printf("Called set_slippage_func()\n");
#endif

  if(PyArg_ParseTuple(args, "O:set_callback", &temp)) {
    if(!PyCallable_Check(temp)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      return NULL;
    }
    Py_XINCREF(temp); /* Add a reference to new commission func */
    engine_register_commission_fn( temp );
    Py_RETURN_NONE;
  }
  
  return result;

}

static PyObject *
set_slippage_func(PyObject *self, PyObject *args)
{
  PyObject *temp, *result = NULL;
#ifdef DEBUG
  printf("Called set_slippage_func()\n");
#endif

  if(PyArg_ParseTuple(args, "O:set_callback", &temp)) {
    if(!PyCallable_Check(temp)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      return NULL;
    }
    Py_XINCREF(temp); /* Add a reference to new commission func */
    engine_register_slippage_fn( temp );
    Py_RETURN_NONE;
  }
  
  return result;
}

static PyObject *
order(PyObject* self, PyObject* args)
{
  const char * company_name;
  long amount;
#ifdef DEBUG
  printf("order()\n");
#endif

  if(!PyArg_ParseTuple(args, "sl", &company_name, &amount)) {
    fprintf(stderr, "trouble parsing parameters\n");
    return NULL;
  }
  engine_order( company_name, amount );
#ifdef DEBUG
  printf("order called with %s %ld\n", company_name, amount);
#endif
  Py_RETURN_NONE;
}

PyMODINIT_FUNC
initqsolve(void)
{
  Py_InitModule("qsolve", QSolveMethods);
}

int setup_engine(void) {
  return engine_init();
}

void set_strategy(PyObject * fn) {
  engine_register_strategy( fn );
}

void set_start_date( time_t * t ) {
  engine_set_start_date( t );
}

void set_end_date( time_t * t ) {
  engine_set_end_date( t );
}

void run(FILE * out) {
  engine_run( out, NULL );
  engine_cleanup();
}
