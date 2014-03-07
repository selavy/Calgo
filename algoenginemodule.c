#include <Python.h>

static PyObject * get_price(PyObject*, PyObject*);
static PyObject * get_volume(PyObject*, PyObject*);
static PyObject * get_open(PyObject*, PyObject*);
static PyObject * get_close(PyObject*, PyObject*);
static PyObject * get_high(PyObject*, PyObject*);
static PyObject * get_low(PyObject*, PyObject*);
static PyObject * set_commission_func(PyObject*, PyObject*);
static PyObject * set_slippage_func(PyObject*, PyObject*);
PyMODINIT_FUNC initalgoengine(void);

static PyMethodDef AlgoEngineMethods[] = {
  {"get_price", get_price, METH_VARARGS, "Get the price of a stock at a given date"},
  {"get_volume", get_volume, METH_VARARGS, "Get the volume of a stock on a given day"},
  {"get_open", get_open, METH_VARARGS, ""},
  {"get_close", get_close, METH_VARARGS, ""},
  {"get_high", get_high, METH_VARARGS, ""},
  {"get_low", get_low, METH_VARARGS, ""},
  {"set_commission_func", set_commission_func, METH_VARARGS, ""},
  {"set_slippage_func", set_slippage_func, METH_VARARGS, ""},
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
  /* Py_RETURN_NONE; */
  return Py_BuildValue("i", 5);
}

static PyObject *
set_commission_func(PyObject *self, PyObject *args)
{
  printf("Called set_commission_func()\n");
  /* Py_RETURN_NONE; */
  return Py_BuildValue("i", 5);
}

static PyObject *
set_slippage_func(PyObject *self, PyObject *args)
{
  printf("Called set_slippage_func()\n");
  /* Py_RETURN_NONE; */
  return Py_BuildValue("i", 5);
}

PyMODINIT_FUNC
initalgoengine(void)
{
  Py_InitModule("algoengine", AlgoEngineMethods);
}
