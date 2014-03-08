#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "general_types.h"

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
extern queue_t * queue_create(void);

/**
 * function: queue_delete()
 * parameters:     +queue: queue_t structure to be deleted
 *                 +delete_fn: function to free any other heap memory stored in data
 * preconditions:  +queue is NULL or heap allocated struct
 * postconditions: +queue is freed
 *                 +queue = NULL
 * returns:
 * notes: if free( node->data ) is enough to not leak memory then just pass NULL for delete_fn
 */
extern void queue_delete( queue_t ** queue, void (*delete_fn)(void *) );

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
extern int queue_enqueue( queue_t * queue, void * buf );

/**
 * function: queue_dequeue()
 * parameters:     +queue: queue_t structure to be modified
 * preconditions:  +queue is NOT NULL
 * postconditions: +node at front of list removed
 * returns:        +pointer to data in node at front of list
 * notes:
 */
extern void * queue_dequeue( queue_t * queue );

/**
 * function: queue_peek()
 * parameters:     +queue: queue_t structure to look at
 * preconditions:  +queue is NOT NULL
 * postconditions:
 * returns:        +pointer to data in node at front of list
 * notes:
 */
extern void * queue_peek( const queue_t * const queue );

/**
 * function: queue_traverse()
 * parameters:     +queue: the queue_t structure to be traversed
 *                 +fn: the function to be applied to each node in queue
 * preconditions:  +queue is NOT NULL
 * postconditions:
 * returns:
 * notes:
 */
extern void queue_traverse( const queue_t * const queue, void (*fn)(const void * const) );

#endif /* ifndef _QUEUE_H_ */
