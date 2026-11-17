#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H


#include <pthread.h>
#include "graph/graph_operation.h"
#include <data_structures/circular_buffer.h>


// quali sono le prop del buffer? head e tail servono


typedef struct bounded_buffer {
    circular_buffer queue;

    // mutex per mutua esclusione per acesso e modifica indici
    pthread_mutex_t mutex;
    // cv per garantire condizioni valide di inserimento 
    pthread_cond_t is_full;
    pthread_cond_t is_empty;


} bounded_buffer;


void bounded_buffer_init(bounded_buffer *buffer, size_t capacity);

void bounded_buffer_destroy(bounded_buffer *buffer);

void enqueue_operation(bounded_buffer *buffer, graph_operation operation);


graph_operation dequeue_operation(bounded_buffer *buffer);


#endif
