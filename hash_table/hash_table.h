#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for malloc and free */
#include <string.h> /* for strlen */
#include <inttypes.h> /* for printing uint32_t */
#include "hash/hash.h" /* for hash function */
#include "general_types.h"

#define MAX_LOAD (0.7f)
#define FIRST_SIZE 1009
#define MAX_SIZE 32063

/* const size_t PRIMES[] = { 1009, 2029, 4049, 5779, 7919, 10007, 15773 }; */

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

/**
 * function: hash_init()
 * parameters:     +tbl: hash_t structure to be initialized
 * preconditions:  +tbl does not point to another hash_t that will be lost if tbl is changed
 *                 +enough memory exists to allocate a hash_t structure
 * postconditions: +tbl holds a blank hash_t structure
 * returns:
 * notes:
 */
void hash_init( hash_t ** tbl );

/**
 * function: hash_delete()
 * parameters:     +tbl: a pointer to the hash_t structure to be freed
 * preconditions:  +tbl is heap-allocated hash_t structure or NULL
 * postconditions: +tbl is NULL
 * returns:
 * notes: must be called to clean up heap allocated memory
 */
void hash_delete( hash_t ** tbl );

/**
 * function: hash_insert()
 * parameters:     +tbl: pointer to hash_t structure
 *                 +key: unique value that will be hashed to place the element in table
 *                 +buf: value to be stored
 * preconditions:  +tbl not NULL
 *                 +key is valid c-string
 *                 +key is not already in the table
 *                 +buf is heap-allocated structure
 * postconditions: +buf is stored in the table (by pointer, NOT COPIED) under key
 * returns:
 * notes: buf is not copied so do not delete buf, hash_delete() will do that
 */
void hash_insert( hash_t ** tbl, char * key, void * buf );

/**
 * function: hash_get_node()
 * parameters:     +tbl: hash_t structure to be accessed
 *                 +key: key to access element
 * preconditions:  +tbl is NOT NULL
 *                 +key is valid c-string
 * postconditions:
 * returns:        +node hashed by key
 *                 +NULL key not in table
 * notes: Since a pointer to the element is returned, you can modify the node.
 *        DO NOT change key otherwise you won't be able to find the node again.
 *        You can change the data in the node though without hurting anything,
 *        but remember to deallocate data first, then re-allocate for the new
 *        object.
 */
hash_node_t * hash_get_node( const hash_t * tbl, const char * key );

/**
 * function: hash_contains()
 * parameters:     +tbl: hash_t structure to be accessed
 *                 +key: key to access element
 * preconditions:  +tbl is NOT NULL
 * postconditions:
 * returns:        +data in node hashed by key
 *                 +NULL if key not in table
 * notes:
 */
void * hash_contains( const hash_t * tbl, const char * key );

/**
 * function: hash_remove()
 * parameters:     +tbl: hash_t structure to be modified
 *                 +key: key to access element
 * preconditions:  +tbl is NOT NULL
 *                 +key is valid c-string
 * postconditions: +node hashed by key is removed from table and freed
 * returns:        +TRUE if successfully removed
 *                 +FALSE if key not in table
 * notes:
 */
int hash_remove( hash_t ** tbl, const char * key );

#endif
