#include "database.h"

static PyObject *get_price_fn;
static PyObject *get_volume_fn;
static PyObject *get_open_fn;
static PyObject *get_close_fn;
static PyObject *get_high_fn;
static PyObject *get_low_fn;

int database_init( PyObject *module ) {
  if(!module) {
    fprintf(stderr, "Error: unable to load python database module\n");
    return -1;
  }

  get_price_fn = PyObject_GetAttrString( module, "get_price" );
  get_volume_fn = PyObject_GetAttrString( module, "get_volume" );
  get_open_fn = PyObject_GetAttrString( module, "get_open" );
  get_close_fn = PyObject_GetAttrString( module, "get_close" );
  get_high_fn = PyObject_GetAttrString( module, "get_high" );
  get_low_fn = PyObject_GetAttrString( module, "get_low" );
  
  if(!get_price_fn  || !PyCallable_Check(get_price_fn) ) fprintf(stderr, "Error: unable to load get_price()\n");
  if(!get_volume_fn || !PyCallable_Check(get_volume_fn)) fprintf(stderr, "Error: unable to laod get_volume()\n");
  if(!get_open_fn   || !PyCallable_Check(get_open_fn)  ) fprintf(stderr, "Error: unable to load get_open()\n");
  if(!get_close_fn  || !PyCallable_Check(get_close_fn) ) fprintf(stderr, "Error: unable to load get_close()\n");
  if(!get_high_fn   || !PyCallable_Check(get_high_fn)  ) fprintf(stderr, "Error: unable to load get_high()\n");
  if(!get_low_fn    || !PyCallable_Check(get_low_fn)   ) fprintf(stderr, "Error: unable to load get_low()\n");
  
  return 0;
}

capital database_get_price( const char * symbol, const date * d ) {
  PyObject *arglist;
  PyObject *result;
  PyObject *pValue;
  long retVal;

  if(!get_price_fn) { fprintf(stderr, "Error: attempted to call get_price() function that wasn't loaded\n"); return 0; }
  if(!symbol) { fprintf(stderr, "Error: symbol passed in is NULL\n"); return 0; }
  arglist = PyTuple_New(2);
  if(!arglist) { fprintf(stderr, "Error: unable to make argument list\n"); return 0; }
  pValue = PyString_FromString(symbol);
  if(!pValue) { fprintf(stderr, "Error: unable to create PyString from symbol\n"); return 0; }
  PyTuple_SetItem(arglist, 0, pValue);
  pValue = PyInt_FromLong(*d);
  if(!pValue) { fprintf(stderr, "Error: unable to create PyInt from date\n"); return 0; }
  PyTuple_SetItem(arglist, 1, pValue);
  result = PyObject_CallObject(get_price_fn, arglist);
  Py_DECREF(arglist);
  if(!result) {
    PyErr_Print();
    fprintf(stderr, "Error: call to get_price() failed\n");
    return 0;
  }
  retVal = PyInt_AsLong(result);
  if(PyErr_Occurred() && (retVal == -1)) {
    PyErr_Print();
    fprintf(stderr, "Error: unable to convert result from PyObject to long\n");
    return 0;
  }
  return retVal;
}

shares database_get_volume( const char * symbol, const date * d ) {
  return 100000;
}

capital database_get_open( const char * symbol, const date * d ) {
  return 4.5f;
}

capital database_get_close( const char * symbol, const date * d ) {
  return 6.4f;
}

capital database_get_high( const char * symbol, const date * d ) {
  return 9.9f;
}

capital database_get_low( const char * symbol, const date * d ) {
  return 4.5f;
}

void database_get_all( const char * symbol, const date * d, db_rslt_t * out ) {
  /* DO NOT USE */
  out = NULL;
}
