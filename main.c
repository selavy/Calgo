#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include "engine.h"
#include "database.h"

static void print_usage_message();
static inline void print_unable_to_open_strategy();
capital commission( const order_t * order, void * args );
capital slippage( const order_t * order, void * args );

int main(int argc, char **argv) {
  void *dynamic_lib;
  void (*init)();
  void (*cleanup)();
  void (*init_strat)();
  char * error;

  if( argc > 1 ) {
    print_usage_message();
    exit(0);
  }

  dynamic_lib = dlopen( "./libstrategy.so", RTLD_NOW );
  if( !dynamic_lib )
    {
      print_unable_to_open_strategy();
      if( (error = dlerror()) )
	fprintf( stderr, "%s\n", error );
      exit(0);
    }
  

  /* These are the calls that I am questioning      */
  /* The signature for dlsym is:                    */
  /* void *dlsym(void *handle, const char *symbol); */
  /* FROM MAN:                                      */
  /*        The  function dlsym() takes a "handle" of a dynamic library returned by
       dlopen() and the null-terminated symbol  name,  returning  the  address
       where  that  symbol is loaded into memory.  If the symbol is not found,
       in the specified library or any of the libraries  that  were  automati‐
       cally  loaded by dlopen() when that library was loaded, dlsym() returns
       NULL.  (The search performed by dlsym() is breadth  first  through  the
       dependency  tree  of  these  libraries.)  Since the value of the symbol
       could actually be NULL (so that a NULL return  from  dlsym()  need  not
       indicate  an  error),  the  correct way to test for an error is to call
       dlerror() to clear any old error conditions,  then  call  dlsym(),  and
       then call dlerror() again, saving its return value into a variable, and
       check whether this saved value is not NULL. */

  /* so the problem is that it returns a void* but I want a function pointer */
  /* and i don't think it is standard to cast void* to function pointer */

  /* The following are all from the C99 standard */
  /* 6.2.3.3:1 -> can do data pointer to data pointer  */
  /* A pointer to void may be converted to or from a pointer to any incomplete or object
type. A pointer to any incomplete or object type may be converted to a pointer to void
and back again; the result shall compare equal to the original pointer.
  */

  /* 6.2.3.3:8: -> can do function pointer to function pointer */
  /* A pointer to a function of one type may be converted to a pointer to a function of another
type and back again; the result shall compare equal to the original pointer. If a converted
pointer is used to call a function whose type is not compatible with the pointed-to type,
the behavior is undefined. */

  /* 6.2.5.26 -> defn of pointer */
  /* A pointer to void shall have the same representation and alignment requirements as a
pointer to a character type.39) Similarly, pointers to qualified or unqualified versions of
   compatible types shall have the same representation and alignment requirements. All
  pointers to structure types shall have the same representation and alignment requirements
 as each other. All pointers to union types shall have the same representation and
alignment requirements as each other. Pointers to other types need not have the same representation or alignment requirements.
  */

  *(void**) (&init) = dlsym( dynamic_lib, "init" );
  if( (error = dlerror()) )
    {
      print_unable_to_open_strategy();
      fprintf( stderr, "%s\n", error );
      exit(0);
    }

  *(void**) (&cleanup) = dlsym( dynamic_lib, "cleanup" );
  if( (error = dlerror()) )
    {
      print_unable_to_open_strategy();
      fprintf( stderr, "%s\n", error );
      exit(0);
    }

  *(void**) (&init_strat) = dlsym( dynamic_lib, "strategy_init" );
  if( (error = dlerror()) )
    {
      print_unable_to_open_strategy();
      fprintf( stderr, "%s\n", error );
      exit(0);
    }

  /* here I now use the void pointer as function pointers which is non-standard C because they could potentially be different sizes */
  (*init)();
  (*init_strat)();
  (*cleanup)();
  dlclose( dynamic_lib );

  return 0;
}

void print_usage_message() {
  /* TODO */
  fputs("Usage message\n", stderr);
}

static inline void print_unable_to_open_strategy() {
  fputs("Unable to open strategy\n", stderr);
}

capital commission( const order_t * order, void * args ) {
  return 0.03f;
}

capital slippage( const order_t * order, void * args ) {
  const capital current_volume = database_get_volume( order->symbol, &(order->datestamp) );
  const capital order_amount = order->amount * database_get_price( order->symbol, &(order->datestamp) );
  const capital div = order_amount / current_volume;
  const double impact = .05;
  const double slippage_val = (div * div * impact);
  return (order->amount > 0) ? slippage_val : -1 * slippage_val;
}
