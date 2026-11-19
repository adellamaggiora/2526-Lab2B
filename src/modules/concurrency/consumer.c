#include "concurrency/consumer.h"
#include "concurrency/bounded_buffer.h"
#include <stddef.h>

void *consume_operations(void *arg)
{
    bounded_buffer *buffer = arg;
    while (true)
    {
        graph_operation operation = dequeue_operation(buffer);
        // La sentinella indica che non arriveranno altre operazioni.
        if (operation.type == END_OPERATIONS)
        {
            return NULL;
        }

        // Per ora estraiamo soltanto l'operazione, senza eseguirla.
    }
}
