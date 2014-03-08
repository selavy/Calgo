#include "algoenginemodule.h"

static PyObject * get_price(PyObject*, PyObject*);
static PyObject * get_volume(PyObject*, PyObject*);
static PyObject * get_open(PyObject*, PyObject*);
static PyObject * get_close(PyObject*, PyObject*);
static PyObject * get_high(PyObject*, PyObject*);
static PyObject * get_low(PyObject*, PyObject*);
static PyObject * set_commission_func(PyObject*, PyObject*);
static PyObject * set_slippage_func(PyObject*, PyObject*);
static PyObject * order(PyObject*, PyObject*);

static PyMethodDef AlgoEngineMethods[] = {
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

/*
capital
slippage(const order_t * order, void * data) {
  PyObject *arglist, *result;
  double retVal;

  if(!slippage_fn) return 0;
  arglist = Py_BuildValue("(i)(s)(i)", order->datestamp, order->symbol, order->amount);
  result = PyObject_CallObject(slippage_fn, arglist);
  Py_DECREF(arglist);
  if(!PyArg_ParseTuple(result, "d", &retVal)) return 0;
  return retVal;
}

capital
commission(const order_t* order, void* data ) {
  PyObject *arglist, *result;
  double retVal;
  
  if(!commission_fn) return 0;
  arglist = Py_BuildValue("(i)(s)(i)", order->datestamp, order->symbol, order->amount);
  result = PyObject_CallObject(commission_fn, arglist);
  Py_DECREF(arglist);
  if(!PyArg_ParseTuple(result, "d", &retVal)) return 0;
  return retVal;
}
*/

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

  if(!PyArg_ParseTuple(args, "(s)(l)", &company_name, &amount)) return NULL;
  engine_order( company_name, amount );
  Py_RETURN_NONE;
}

PyMODINIT_FUNC
initalgoengine(void)
{
  Py_InitModule("algoengine", AlgoEngineMethods);
}
