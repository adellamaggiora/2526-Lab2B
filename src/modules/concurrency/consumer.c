#include "concurrency/consumer.h"
#include "concurrency/bounded_buffer.h"
#include <stddef.h>
#include <stdio.h>

void *consume_operations(void *arg)
{
    bounded_buffer *buffer = arg;
    graph_operation operation = dequeue_operation(buffer);

    // qui sono già fuori dalla sezione critica

    if (operation.type == END_OPERATIONS)
    {
        // quando la funzione eseguita dal thread fa un 'return' il thread termina
        // NULL è semplicemente il valore restituito
        return NULL;
    }


    while (true)
    {
        switch (operation.type)
        {
        case ADD_EDGE:
            fprintf(stderr, "add edge \n");

            /* code */
            break;
        case REMOVE_EDGE:
            fprintf(stderr, "remove edge \n");
            /* code */
            break;
        case END_OPERATIONS:
            // quando la funzione eseguita dal thread fa un 'return' il thread termina
            // NULL è semplicemente il valore restituito
            return NULL;
        default:
            break;
        }
    }
}
