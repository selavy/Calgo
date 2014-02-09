#include "hash_table.h"

/* First hash table implementation using separate chaining with buckets of linked lists */
static void hash_init_helper( hash_t ** tbl, size_t size );
static void hash_shallow_delete( hash_t ** tbl );
static hash_node_t * hash_node_insert( hash_node_t ** node, char * key, void * buf );
static size_t hash_next_size( size_t curr );

static void hash_init_helper( hash_t ** tbl, size_t size ) {
  int i;

  *tbl = malloc( sizeof( **tbl ) );
  if( *tbl == NULL ) return;
  
  (*tbl)->count = 0;
  (*tbl)->tbl_sz = size;
  (*tbl)->tbl_p = malloc( sizeof( *((*tbl)->tbl_p) ) * size);
  if( (*tbl)->tbl_p == NULL )
    {
      /* wasn't able to get memory for the table so free the struct */
      free( *tbl );
      *tbl = NULL;
      return;
    }

  /* initialize all the buckets to NULL */
  for( i = 0; i < size; ++i )
    {
      ((*tbl)->tbl_p)[i] = NULL;
    }
}

void hash_init( hash_t ** tbl )
{
  hash_init_helper( tbl, FIRST_SIZE );
}

void hash_delete( hash_t ** tbl ) {
  int i;
  const size_t len = (*tbl)->tbl_sz;
  hash_node_t *curr, *next;

  if( *tbl == NULL ) return;

  for( i = 0; i < len; ++i )
    {
      /* free linked list in the bucket */
      curr = ((*tbl)->tbl_p)[i];
      while( curr != NULL )
	{
	  next = curr->next;
	  free( curr->data );
	  free( curr->key );
	  free( curr );
	  curr = next;
	}
    }

  /* free table */
  free( (*tbl)->tbl_p );
  free( *tbl );
  *tbl = NULL;
}

static void hash_shallow_delete( hash_t ** tbl )
{
  int i;
  const size_t len = (*tbl)->tbl_sz;
  hash_node_t *curr, *next;

  if( *tbl == NULL ) return;

  for( i = 0; i < len; ++i )
    {
      /* free linked list in the bucket */
      curr = ((*tbl)->tbl_p)[i];
      while( curr != NULL )
	{
	  next = curr->next;
	  free( curr->key );
	  /* don't: delete( curr->data );                     */
	  /* i.e. don't delete the data contained in the node */
	  /* because it is still being used by another        */
	  /* table.                                           */
	  free( curr );
	  curr = next;
	}
    }

  /* free table */
  free( (*tbl)->tbl_p );
  free( *tbl );
  *tbl = NULL;
}

static hash_node_t * hash_node_insert( hash_node_t ** node, char * key, void * buf ) {
  hash_node_t * n;
  if( *node == NULL )
    {
      *node = malloc( sizeof( **node ) );
      if( *node == NULL ) return NULL;
      
      (*node)->data = buf;
      (*node)->key = savestring(key);
      (*node)->next = NULL;
      return (*node);
    }
  else
    {
      n = *node;
      while( n->next != NULL )
	n = n->next;

      n->next = malloc( sizeof( *n ) );
      if( n->next == NULL ) return NULL;

      n = n->next;
      n->data = buf;
      n->key = savestring(key);
      n->next = NULL;
      return n;
    }
}

static size_t hash_next_size( size_t curr ) { 
  /* TODO: check if more/less efficient to use switch or if/elsif */
  if( curr == 0 ) {
    return 1009;
  }
  else if( curr == 1009 ) {
    return 2029;
  }
  else if( curr == 2029 ) {
    return 4049;
  }
  else if( curr == 4049 ) { 
    return 5779;
  }
  else if( curr == 5779 ) {
    return 7919;
  }
  else if( curr == 7919 ) {
    return 10007;
  }
  else if( curr == 10007 ) {
    return 15773;
  }
  else {
    return 32063;
  }
}

void hash_insert( hash_t ** tbl, char * key, void * buf ) {
  const uint32_t loc = super_fast_hash( key, strlen( key ) ) % (*tbl)->tbl_sz;
  double load;

  /*printf("loc = %"PRIx32"\n", loc); */
  /* init table if it hasn't been yet */
  if( *tbl == NULL ) hash_init( tbl );

  if( hash_node_insert( &(*tbl)->tbl_p[loc], key, buf ) == NULL )
    return; /* failed to insert */
  /* else */
  (*tbl)->count++;
  
  if( (*tbl)->tbl_sz != MAX_SIZE )
    {
      /* check if the table needs to be rebalanced and rehashed */
      load = ((double) (*tbl)->count) / (*tbl)->tbl_sz;
  
      /* rehash if needed */
      if( (load > MAX_LOAD) )
	{
	  const size_t prev_size = (*tbl)->tbl_sz;
	  const size_t next_size = hash_next_size( prev_size );
	  int i;
	  hash_t * new_tbl;

	  /* printf("needs rebalanced\n"); */
	  /* TODO remove this function and do it by hand so don't loop through array so many times */
	  hash_init_helper( &new_tbl, next_size );

	  for( i = 0; i < prev_size; ++i )
	    {
	      hash_node_t * node = ((*tbl)->tbl_p)[i];
	      while( node != NULL )
		{
		  hash_insert( &new_tbl, node->key, node->data );
		  node = node->next;
		}
	    }

	  /* don't delete the pointers in the table, because we just */
	  /* copied the pointer locations not the data.              */
	  hash_shallow_delete( tbl );
	  *tbl = new_tbl;
	}
    }

}

hash_node_t * hash_get_node( const hash_t * tbl, const char * key ) {
  const uint32_t loc = super_fast_hash( key, strlen( key ) ) % tbl->tbl_sz;
  hash_node_t * node = tbl->tbl_p[loc];

  while( node != NULL )
    {
      if( strcmp( node->key, key ) == 0 )
	{
	  return node;
	}
      else
	{
	  node = node->next;
	}
    }
  
  /* did not find the value so return NULL */
  return NULL;
}

void * hash_contains( const hash_t * tbl, const char * key ) {
  hash_node_t * node = hash_get_node( tbl, key );
  if( node == NULL ) return NULL;
  else return (void*) node->data;
}

int hash_remove( hash_t ** tbl, const char * key ) {
  const uint32_t loc = super_fast_hash( key, strlen(key) ) % (*tbl)->tbl_sz;
  hash_node_t * node = (*tbl)->tbl_p[loc];
  
  if( strcmp( node->key, key ) == 0 )
    {
      (*tbl)->tbl_p[loc] = node->next;
      free( node->key );
      free( node->data );
      free( node );
      return 1;
    }

  while( node->next != NULL )
    {
      if( strcmp( node->next->key, key ) == 0 )
	{
	  hash_node_t * next = node->next->next;
	  free( node->next->key );
	  free( node->next->data );
	  free( node->next );
	  node->next = next;
	  return 1;
	}
    }
  
  return 0;
}

