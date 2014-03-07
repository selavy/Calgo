#include <Python.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
  PyObject *pName, *pModule, *pDict, *pFunc;
  PyObject *pArgs, *pValue;
  int i;

  if(argc < 2) {
    fprintf(stderr, "Usage: call pythonfile funcname\n");
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

  pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  if(pModule != NULL) {
    pFunc = PyObject_GetAttrString(pModule, "init");
    if(pFunc && PyCallable_Check(pFunc)) {
      pValue = PyObject_CallObject(pFunc, NULL);
      if(!pValue) {
	Py_DECREF(pFunc);
	PyErr_Print();
	fprintf(stderr, "Call to init failed\n");
      }
    } else {
      printf("No init function defined so skipping over to strategy function...\n");
    }

    pFunc = PyObject_GetAttrString(pModule, "strategy");
    /* pFunc is a new reference */

    if(pFunc && PyCallable_Check(pFunc)) {
      pArgs = PyTuple_New(1);
      pValue = PyInt_FromLong(1);
      if(!pValue) {
	Py_DECREF(pArgs);
	Py_DECREF(pModule);
	fprintf(stderr, "Cannot convert argument\n");
	return 1;
      }
      PyTuple_SetItem(pArgs, i, pValue);
      pValue = PyObject_CallObject(pFunc, pArgs);
      Py_DECREF(pArgs);
      if(pValue) {
	printf("Result of call: %ld\n", PyInt_AsLong(pValue));
	Py_DECREF(pValue);
      } else {
	Py_DECREF(pFunc);
	Py_DECREF(pModule);
	PyErr_Print();
	fprintf(stderr, "Call failed\n");
	return 1;
      }
    }
    else {
      if (PyErr_Occurred()) PyErr_Print();
      fprintf(stderr, "Cannot find strategy function!\n");
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
  }
  else {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
    return 1;
  }
  Py_Finalize();
  return 0;
}
