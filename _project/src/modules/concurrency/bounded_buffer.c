#include <graph_operation.h>
#include <pthread.h>
#include <bounded_buffer.h>
#include <error-manager.h>


// produttore
void enqueue_operation(bounded_buffer *buffer, graph_operation operation) {

    checked_pthread_mutex_lock(&buffer->mutex);






}

// consumatore
void dequeue_operation(bounded_buffer *buffer) {

}
