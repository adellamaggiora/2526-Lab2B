#include "io/operation_parser.h"
#include "io/parser_utils.h"
#include "utils/error-manager.h"
#include <assert.h>

// lettura di un'operazione alla volta, true quando è un'operazione valida
bool read_next_operation(
    FILE *file,
    graph_operation *operation)
{
    assert(file != NULL);
    assert(operation != NULL);

    char operation_type;

    while (fscanf(file, " %c", &operation_type) == 1)
    {
        switch (operation_type)
        {

        case '+':
            if (fscanf(file, " %d %d %d", &operation->u, &operation->v, &operation->weight) != 3)
            {
                discard_rest_of_line(file);
                break;
            }
            operation->type = OPERATION_ADD;
            return true;

        case '-':
            if (fscanf(file, " %d %d", &operation->u, &operation->v) != 2)
            {
                discard_rest_of_line(file);
                break;
            }
            operation->type = OPERATION_REMOVE;
            operation->weight = 0;
            return true;

        default:
            discard_rest_of_line(file);
            break;
        }
    }

    if (ferror(file))
    {
        terminate("Operation file reading failed");
    }

    return false;
}

void produce_operations(FILE *file, operation_queue *queue)
{
    assert(file != NULL);
    assert(queue != NULL);

    graph_operation operation;

    while (read_next_operation(file, &operation))
    {
        if (!operation_queue_push(queue, operation))
        {
            return;
        }
    }

    operation_queue_close(queue);
}
