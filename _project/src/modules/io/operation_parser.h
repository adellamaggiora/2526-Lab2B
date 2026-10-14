#ifndef OPERATION_PARSER_H
#define OPERATION_PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include "concurrency/operation_queue.h"

bool read_next_operation(
    FILE *file,
    graph_operation *operation);

void produce_operations(
    FILE *file,
    operation_queue *queue);

#endif
