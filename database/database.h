#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "general_types.h"

/** THRIFT **/
/*
#include <thrift/protocl/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace shared;

void init_database();
*/
/** END THRIFT **/

typedef struct {
  capital price;
  shares volume;
  capital open;
  capital close;
  capital high;
  capital low;
} db_rslt_t;

extern capital database_get_price( const char * symbol, const date * d );
extern shares  database_get_volume( const char * symbol, const date * d );
extern capital database_get_open( const char * symbol, const date * d );
extern capital database_get_close( const char * symbol, const date * d );
extern capital database_get_high( const char * symbol, const date * d );
extern capital database_get_low( const char * symbol, const date * d );
extern void    database_get_all( const char * symbol, const date * d, db_rslt_t * out );

#endif
