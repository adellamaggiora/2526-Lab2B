#include <graph_operation.h>
#include <pthread.h>
#include <bounded_buffer.h>
#include <error-manager.h>


// produttore
void enqueue_operation(bounded_buffer *buffer, graph_operation operation) {

    checked_pthread_mutex_lock(&buffer->mutex);

    // semantica MESA
    while (buffer->size == buffer->capacity)
    {
        checked_pthread_cond_wait(&buffer->is_full, &buffer->mutex);
    }

    buffer->queue[buffer->tail] = operation;
    // buffer circoalre, deve stare in un array di dimensione fissata
    buffer->tail = (buffer->tail + 1) % buffer->capacity;
    buffer->size++;

    // basta una signal visto che inserisco un solo elemento?
    checked_pthread_cond_broadcast(&buffer->is_empty);
    checked_pthread_mutex_unlock(&buffer->mutex);
}

// consumatore
graph_operation dequeue_operation(bounded_buffer *buffer) {


    checked_pthread_mutex_lock(&buffer->mutex);

    while (buffer->size == 0)
    {
        checked_pthread_cond_wait(&buffer->is_empty, &buffer->mutex);
    }

    graph_operation op = buffer->queue[buffer->head];
    buffer->head = (buffer->head + 1) % buffer->capacity;
    buffer->size--;

    checked_pthread_cond_signal(&buffer->is_full);
    checked_pthread_mutex_unlock(&buffer->mutex);

    return op;
}
