#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*fn_ptr)();

int main(int argc, char **argv) {
  void *my_lib;
  fn_ptr my_func;

  my_lib = dlopen( "./libmy_function.so", RTLD_NOW );
  my_func = (fn_ptr) dlsym( my_lib, "my_function" );  
  (my_func)();
  dlclose( my_lib );

  if( !my_lib )
    {
      fputs( "Unable to open library!\n", stderr );
      exit(1);
    }

  dlerror(); /* clear any old errors */

  if( (!my_func) && dlerror() )
    {
      fputs("Unable to locate my_function()\n", stderr );
      dlclose( my_lib );
      exit(1);
    }


  

  return 0;
}
