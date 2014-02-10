#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "general_types.h"

#ifdef _DEBUG_
#include <stdio.h>
#endif /* _DEBUG_ */

typedef struct _queue_node_t
{
  void * data;
  struct _queue_node_t * prev;
} queue_node_t;

typedef struct _queue_t
{
  queue_node_t * front;
  queue_node_t * back;
  size_t size;
} queue_t;

/**
 * function: queue_create()
 * parameters:
 * preconditions:  +enough memory is available to allocate a queue_t struct
 * postconditions: +new queue_t struct allocated on heap
 *                 +size = 0
 *                 +front = back = NULL
 * returns:        +pointer to new queue_t struct
 * notes: must pair with call to queue_delete() to not leak memory
 */
queue_t * queue_create();

/**
 * function: queue_delete()
 * parameters:     +queue: queue_t structure to be deleted
 * preconditions:  +queue is NULL or heap allocated struct
 * postconditions: +queue is freed
 *                 +queue = NULL
 * returns:
 * notes:
 */
void queue_delete( queue_t ** queue );

/**
 * function: queue_enqueue()
 * parameters:     +queue: queue_t structure to be modified
 *                 +buf: pointer to element to be stored
 * preconditions:  +queue is NOT NULL
 *                 +buf is NOT NULL
 *                 +buf is pointer to heap allocated data
 *                 +if successful, size incremented by 1
 * postconditions: +node pointing to buf added to end of queue
 * returns:        +TRUE if inserted
 *                 +FALSE if not inserted
 * notes:
 */
int queue_enqueue( queue_t * queue, void * buf );

/**
 * function: queue_dequeue()
 * parameters:     +queue: queue_t structure to be modified
 * preconditions:  +queue is NOT NULL
 * postconditions: +node at front of list removed
 * returns:        +pointer to data in node at front of list
 * notes:
 */
void * queue_dequeue( queue_t * queue );

/**
 * function: queue_peek()
 * parameters:     +queue: queue_t structure to look at
 * preconditions:  +queue is NOT NULL
 * postconditions:
 * returns:        +pointer to data in node at front of list
 * notes:
 */
void * queue_peek( const queue_t * const queue );

#ifdef _DEBUG_
/**
 * function: queue_print_pointers()
 * parameters:     +queue: the queue_t structure to be printed
 * preconditions: 
 * postconditions: +contents of queue is printed to stdout
 * returns:
 * notes:
 */
void queue_print_pointers( const queue_t * const queue );
#endif /* _DEBUG_ */

void queue_traverse( const queue_t * const queue, void (*fn)(const void * const) );

#endif /* ifndef _QUEUE_H_ */
