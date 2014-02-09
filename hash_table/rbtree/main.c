#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

inline int compare( void * a, void * b ) {
  return *((int*)a) < *((int*)b);
}

int main(int argc, char **argv) {
  Tree tree = NULL;
  int a = 1, b = 2, c = 3;
  
  rb_insert( &tree, &a, compare );
  rb_insert( &tree, &b, compare );
  rb_insert( &tree, &c, compare );
  return 0;
}
