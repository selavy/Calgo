#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for malloc and free */
#include <string.h> /* for strlen */
#include <inttypes.h> /* for printing uint32_t */
#include "hash/hash.h" /* for hash function */

#include <stdio.h> /* for printf */

#ifndef NULL
#define NULL 0
#endif

#ifndef savestring
#define savestring(x) (strcpy(malloc(strlen(x)+1),(x)))
#endif

#define MAX_LOAD (0.7f)
#define FIRST_SIZE 1009
#define MAX_SIZE 32063

typedef struct _node_t
{
  char * key;
  void * data;
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
void hash_insert( hash_t ** tbl, char * key, void * buf );
hash_node_t * hash_get_node( const hash_t * tbl, const char * key );
void * hash_contains( const hash_t * tbl, const char * key );
int hash_remove( hash_t ** tbl, const char * key );

#endif
