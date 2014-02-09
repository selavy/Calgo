#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for malloc and free */
#include <string.h> /* for memcpy */
#include <inttypes.h> /* for printing uint32_t */
#include "hash/hash.h" /* for hash function */

#include <stdio.h> /* for printf */

#ifndef NULL
#define NULL 0
#endif

#define MAX_LOAD (0.7f)
#define FIRST_SIZE 1009
#define MAX_SIZE 32063

typedef struct _node_t
{
  void * data;
  size_t data_sz;
  struct _node_t * next;
} hash_node_t;


typedef struct _hash_t
{
  hash_node_t ** tbl_p;
  size_t tbl_sz;
  long count;
} hash_t;

/* const size_t PRIMES[] = { 1009, 2029, 4049, 5779, 7919, 10007, 15773 }; */

void hash_init( hash_t ** tbl );
void hash_delete( hash_t ** tbl );
void hash_insert( hash_t ** tbl, void * buf, size_t buf_sz );
hash_node_t * hash_contains_node( const hash_t * tbl, const void * buf, size_t buf_sz, int (*cmp)(const void*, const void*) );
void * hash_contains( const hash_t * tbl, const void * buf, size_t buf_sz, int (*cmp)(const void*, const void*) );
int hash_remove( hash_t ** tbl, const void * buf, size_t buf_sz, int (*cmp)(const void*, const void*) );

#endif
