#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stdlib.h>

#define BLACK 0
#define RED 1

typedef struct _rb_node_t {
  unsigned short color; /* 0: BLACK, 1: RED */
  void * data;
  struct _rb_node_t *left,
    *right,
    *parent;
} rb_node_t;

typedef rb_node_t * Tree;
typedef rb_node_t * node;

/*static void left_rotate( Tree * T, node x );
static void right_rotate( Tree * T, node x );
static void tree_insert( Tree * T, node x, int (*cmp)(void*, void*) );
static void _rb_insert( Tree * T, node x, int (*cmp)(void*, void*) ); */
void rb_insert( Tree * T, void * buf, int (*cmp)(void*, void*) );


#endif
