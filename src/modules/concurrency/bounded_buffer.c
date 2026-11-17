#include <pthread.h>
#include <bounded_buffer.h>
#include "utils/xerrori.h"
#include <assert.h>


void bounded_buffer_init(bounded_buffer *buffer, size_t capacity)
{
    assert(buffer != NULL);

    circular_buffer_init(&buffer->queue, capacity, sizeof(graph_operation));
    xpthread_mutex_init(&buffer->mutex, NULL, __LINE__, __FILE__);
    xpthread_cond_init(&buffer->is_full, NULL, __LINE__, __FILE__);
    xpthread_cond_init(&buffer->is_empty, NULL, __LINE__, __FILE__);
}

void bounded_buffer_destroy(bounded_buffer *buffer)
{
    assert(buffer != NULL);

    xpthread_cond_destroy(&buffer->is_full, __LINE__, __FILE__);
    xpthread_cond_destroy(&buffer->is_empty, __LINE__, __FILE__);
    xpthread_mutex_destroy(&buffer->mutex, __LINE__, __FILE__);
    circular_buffer_destroy(&buffer->queue);
}


// produttore
void enqueue_operation(bounded_buffer *buffer, graph_operation operation) {

    xpthread_mutex_lock(&buffer->mutex, __LINE__, __FILE__);

    // semantica MESA
    while (circular_buffer_is_full(&buffer->queue))
    {
        xpthread_cond_wait(&buffer->is_full, &buffer->mutex, __LINE__, __FILE__);
    }

    bool inserted = circular_buffer_push(&buffer->queue, &operation);
    assert(inserted);

    // basta una signal visto che inserisco un solo elemento?
    xpthread_cond_broadcast(&buffer->is_empty, __LINE__, __FILE__);
    xpthread_mutex_unlock(&buffer->mutex, __LINE__, __FILE__);
}

// consumatore
graph_operation dequeue_operation(bounded_buffer *buffer) {


    xpthread_mutex_lock(&buffer->mutex, __LINE__, __FILE__);

    while (circular_buffer_is_empty(&buffer->queue))
    {
        xpthread_cond_wait(&buffer->is_empty, &buffer->mutex, __LINE__, __FILE__);
    }

    graph_operation op;

    
    bool extracted = circular_buffer_pop(&buffer->queue, &op);
    assert(extracted);

    xpthread_cond_signal(&buffer->is_full, __LINE__, __FILE__);
    xpthread_mutex_unlock(&buffer->mutex, __LINE__, __FILE__);

    return op;
}
