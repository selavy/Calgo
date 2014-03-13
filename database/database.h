#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "Python.h"
#include "general_types.h"

typedef struct {
  capital price;
  shares volume;
  capital open;
  capital close;
  capital high;
  capital low;
} db_rslt_t;

extern int     database_init( PyObject * module );
extern capital database_get_price( const char * symbol, const date * d );
extern shares  database_get_volume( const char * symbol, const date * d );
extern capital database_get_open( const char * symbol, const date * d );
extern capital database_get_close( const char * symbol, const date * d );
extern capital database_get_high( const char * symbol, const date * d );
extern capital database_get_low( const char * symbol, const date * d );
extern void    database_get_all( const char * symbol, const date * d, db_rslt_t * out );

#endif
