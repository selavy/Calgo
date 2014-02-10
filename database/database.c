#include "database.h"

capital database_get_price( const char * symbol, const date * d ) {
  return 5.0f;
}

shares database_get_volume( const char * symbol, const date * d ) {
  return 10000;
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
