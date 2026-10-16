#include <graph_operation.h>
#include <pthread.h>
#include <bounded_buffer.h>
#include <error-manager.h>
#include <assert.h>


void bounded_buffer_init(bounded_buffer *buffer, size_t capacity)
{
    assert(buffer != NULL);

    circular_buffer_init(&buffer->queue, capacity, sizeof(graph_operation));
    checked_pthread_mutex_init(&buffer->mutex, NULL);
    checked_pthread_cond_init(&buffer->is_full, NULL);
    checked_pthread_cond_init(&buffer->is_empty, NULL);
}

void bounded_buffer_destroy(bounded_buffer *buffer)
{
    assert(buffer != NULL);

    checked_pthread_cond_destroy(&buffer->is_full);
    checked_pthread_cond_destroy(&buffer->is_empty);
    checked_pthread_mutex_destroy(&buffer->mutex);
    circular_buffer_destroy(&buffer->queue);
}


// produttore
void enqueue_operation(bounded_buffer *buffer, graph_operation operation) {

    checked_pthread_mutex_lock(&buffer->mutex);

    // semantica MESA
    while (circular_buffer_is_full(&buffer->queue))
    {
        checked_pthread_cond_wait(&buffer->is_full, &buffer->mutex);
    }

    bool inserted = circular_buffer_push(&buffer->queue, &operation);
    assert(inserted);

    // basta una signal visto che inserisco un solo elemento?
    checked_pthread_cond_broadcast(&buffer->is_empty);
    checked_pthread_mutex_unlock(&buffer->mutex);
}

// consumatore
graph_operation dequeue_operation(bounded_buffer *buffer) {


    checked_pthread_mutex_lock(&buffer->mutex);

    while (circular_buffer_is_empty(&buffer->queue))
    {
        checked_pthread_cond_wait(&buffer->is_empty, &buffer->mutex);
    }

    graph_operation op;
    bool extracted = circular_buffer_pop(&buffer->queue, &op);
    assert(extracted);

    checked_pthread_cond_signal(&buffer->is_full);
    checked_pthread_mutex_unlock(&buffer->mutex);

    return op;
}
