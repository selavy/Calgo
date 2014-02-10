#include "queue.h"

queue_t * queue_create() {
  queue_t * queue = malloc( sizeof( *queue ) );
  if( queue == NULL ) return NULL;

  queue->front = NULL;
  queue->back = NULL;
  queue->size = 0;
  return queue;
}

void queue_delete( queue_t ** queue ) {
  queue_node_t *node, *prev;
  if( *queue == NULL ) return;

  node = (*queue)->front;
  while( node != NULL )
    {
      prev = node->prev;
      free( node->data );
      free( node );
      node = prev;
    }

  free( *queue );
  *queue = NULL;
}

int queue_enqueue( queue_t * queue, void * buf ) {
  queue_node_t * node = malloc( sizeof( *node ) );
  if( node == NULL ) return FALSE;

  node->data = buf;
  if( queue->front == NULL )
    {
      /* queue->back MUST also be NULL */
      node->prev = NULL;
      queue->front = node;
      queue->back = node;
    }
  else
    {
      queue->back->prev = node;
      queue->back = node;
    }

  (queue->size)++;
  return TRUE;
}

void * queue_dequeue( queue_t * queue ) {
  queue_node_t * node = queue->front;
  void * data;
  if( node != NULL )
    queue->front = node->prev;
  data = node->data;
  free( node );
  (queue->size)--;
  return data;
}

void * queue_peek( const queue_t * queue ) {
  return queue->front->data;
}
