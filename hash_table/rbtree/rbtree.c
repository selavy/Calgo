#include "rbtree.h"

static void left_rotate( Tree * T, node x )
{
  node y;
  y = x->right;
  /* Turn y's left sub-tree into x's right sub-tree */
  x->right = y->left;
  if( y->left != NULL )
    y->left->parent = x;
  /* y's new parent was x's parent */
  y->parent = x->parent;
  /* Set the parent to point to y instead of x */
  /* Firest see whether we are at the root */
  if( x->parent == NULL ) *T = y;
  else
    {
      if( x == x->parent->left )
	x->parent->left = y;
      else
	x->parent->right = y;
    }
  y->left = x;
  x->parent = y;
}

static void right_rotate( Tree * T, node x )
{
  node y;
  y = x->left;
  x->left = y->right;
  if( y->right != NULL )
    y->right->parent = x;
  y->parent = x->parent;
  if( x->parent == NULL ) *T = y;
  else
    {
      if( x == x->parent->right )
	x->parent->right = y;
      else
	x->parent->right = y;
    }
  y->right = x;
  x->parent = y;
}

static void tree_insert( Tree * T, node x, int (*cmp)(void*,void*) ) {
  node t;

  if( *T == NULL )
    {
      x->parent = NULL;
      x->left = NULL;
      x->right = NULL;
      *T = x;
      return;
    }

  t = *T;

  while( 1 )
    {
      if( cmp(t->data, x->data) )
	{
	  if( t->left == NULL )
	    {
	      x->left = NULL;
	      x->right = NULL;
	      t->left = x;
	      x->parent = t;
	    }
	  else
	    t = t->left;
	}
      else
	{
	  if( t->right == NULL )
	    {
	      x->left = NULL;
	      x->right = NULL;
	      t->right = x;
	      x->parent = t;
	    }
	  else
	    t = t->right;
	}
    }
}

static void _rb_insert( Tree * T, node x, int (*cmp)(void*, void*) ) {
  tree_insert( T, x, cmp );
  x->color = RED;
  while( (x != (*T)) && (x->parent->color == RED) ) {
    if( x->parent == x->parent->parent->left )
      {
	node y = x->parent->parent->right;
	if( y->color == RED )
	  {
	    x->parent->color = BLACK;
	    y->color = BLACK;
	    x->parent->parent->color = RED;
	    x = x->parent->parent;
	  }
	else
	  {
	    if( x == x->parent->right )
	      {
		x = x->parent;
		left_rotate( T, x );
	      }
	  
	    x->parent->color = BLACK;
	    x->parent->parent->color = RED;
	    right_rotate( T, x->parent->parent );
	  }
      }
    else
      {
	node y = x->parent->parent->left;
	if( y->color == RED )
	  {
	    x->parent->color = BLACK;
	    y->color = BLACK;
	    x->parent->parent->color = RED;
	    x = x->parent->parent;
	  }
	else
	  {
	    if( x == x->parent->left )
	      {
		x = x->parent;
		right_rotate( T, x );
	      }
	  
	    x->parent->color = BLACK;
	    x->parent->parent->color = RED;
	    left_rotate( T, x->parent->parent );
	  }
      }
  }
  (*T)->color = BLACK;
}

void rb_insert( Tree * T, void * buf, int (*cmp)(void*, void*) ) {
  node n = malloc( sizeof(*n) );
  if( n == NULL ) return;

  n->data = buf;
  _rb_insert( T, n, cmp );
}
