#include "database.h"

/*
void init_database() {
  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  DatabaseClient client(protocol);

  try {
    transport->open();
  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }
}
*/

capital database_get_price( const char * symbol, const date * d ) {
  /* client.get_price(symbol, date); */
  return 5.0f;
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
