#include <Python.h>
#include <dlfcn.h>
#include "algoenginemodule.h"
#include "general_types.h"

int main(int argc, char **argv) {
  PyObject *pName, *pModule, *pDict, *pFunc;
  PyObject *pArgs, *pValue;
  int i;
  struct tm * start_tm;
  date now = time( NULL ), start;

  if(argc < 2) {
    fprintf(stderr, "Usage: call strategy_file\n");
    return 1;
  }

  Py_SetProgramName(argv[0]);
  Py_Initialize();
  PySys_SetArgv(argc, argv);

  pName = PyString_FromString(argv[1]);
  if(!pName) {
    perror("pName");
    Py_Finalize();
    exit(1);
  }

  pModule = PyImport_Import( pName );
  Py_DECREF( pName );

  if( pModule != NULL ) {
    pFunc = PyObject_GetAttrString( pModule, "init" );
    if(pFunc && PyCallable_Check(pFunc)) {
      pValue = PyObject_CallObject(pFunc, NULL);
      if( !pValue ) {
	Py_DECREF( pFunc );
	PyErr_Print();
	fprintf( stderr, "Call to init failed\n" );
      }
    } else {
      printf("No init function defined so skipping over to strategy function...\n");
    }

    /* engine_register_module( pModule ); */
    pFunc = PyObject_GetAttrString(pModule, "strategy");
    /* pFunc is a new reference */

    if (pFunc && PyCallable_Check( pFunc ) ) {
      start_tm = localtime( &now );
      start_tm->tm_year = 113; /* 1900 + 114 = 2014 */
      start = mktime( start_tm );
      /*
      if(!engine_init()) { fprintf( stderr, "Unable to initialize engine!\n" ); exit (1); }
      engine_register_strategy( pFunc );
      engine_set_start_date( &start );
      engine_set_end_date( &now );
      engine_run( stdout, NULL );
      engine_cleanup();
      */
      if(!setup_engine()) { fprintf( stderr, "Unable to initialize engine!\n" ); exit (1); }
      set_strategy( pFunc );
      set_start_date( &start );
      set_end_date( &now );
      run();
    }
    else {
      if( PyErr_Occurred() ) PyErr_Print();
      fprintf(stderr, "Cannot find strategy function!\n");
    }
      /*
	handled by engine
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
      */
  }
  else {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
    return 1;
  }
  Py_Finalize();
  return 0;
}
