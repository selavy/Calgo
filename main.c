#include <Python.h>
#include <dlfcn.h>
#include "qsolvemodule.h"
#include "general_types.h"

int main(int argc, char **argv) {
  PyObject *pName, *pModule, *pFunc, *pValue;
  struct tm *start_tm, *end_tm;
  date now = time( NULL ), start, end;
  FILE * pFile;
  char * date;
  int val;

  if(argc < 4) {
    fprintf(stderr, "Usage: call [STRATEGY_FILE] [OUTPUT_FILE] [START_DATE] [END_DATE] (optional)\n");
    return 1;
  }

  pFile = fopen(argv[2], "w");
  if(!pFile) { perror("unable to open output file!"); exit (1); }

  start_tm = localtime( &now );
  date = strtok( argv[3], "-/." );
  if(date) {
    val = atoi( date );
    --val; /* for the tm struct, mon is the number of months SINCE janurary, so it starts at 0 */
    start_tm->tm_mon = val;
    printf("Start date parsed: %d-", val);
    date = strtok( NULL, "-/." );
    if(date) {
      val = atoi( date );
      start_tm->tm_mday = val;
      printf("%d-", val);
      date = strtok( NULL, "-/." );
      if(date) {
	val = atoi( date );
	printf("%d\n", val);
	start_tm->tm_year = val - 1900; /* tm_year is years since 1900 */
      } else {
	printf("Warning: could not parse a year value for the start date.\n");
      }
    } else {
      printf("Warning: could not parse a day or year value for the start date.\n");
    }
  } else {
    printf("Error: could not parse any of the start date given.\n");
  }
  start = mktime( start_tm );

  if(argc == 5) {
    end_tm = localtime( &now );
    date = strtok( argv[4], "-/." );
    if(date) {
      val = atoi( date );
      --val; /* for the tm struct, mon is the number of months SINCE janurary, so it starts at 0 */
      end_tm->tm_mon = val;
      printf("End date parsed: %d-", val);
      date = strtok( NULL, "-/." );
      if(date) {
	val = atoi( date );
	end_tm->tm_mday = val;
	printf("%d-", val);
	date = strtok( NULL, "-/." );
	if(date) {
	  val = atoi( date );
	  end_tm->tm_year = val - 1900;
	  printf("%d-", val);
	} else {
	  printf("Warning: could not parse a year value for the end date.\n");
	}
      } else {
	printf("Warning: could not parse a day or year value for the end date.\n");
      }
    } else {
      printf("Error: could not parse any of the end date given.\n");
    }
    end = mktime( end_tm );
  } else {
    end = now;
    end_tm = localtime(&now);
    printf("Using %d-%d-%d for end date\n", end_tm->tm_mon + 1, end_tm->tm_mday, end_tm->tm_year + 1900 );
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

    pFunc = PyObject_GetAttrString(pModule, "strategy");
    /* pFunc is a new reference */

    if (pFunc && PyCallable_Check( pFunc ) ) {
      if(!setup_engine()) { fprintf( stderr, "Unable to initialize engine!\n" ); exit (1); }
      set_strategy( pFunc );
      set_start_date( &start );
      set_end_date( &end );
      run( pFile );
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
