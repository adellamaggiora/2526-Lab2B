#ifndef OPERATION_PARSER_H
#define OPERATION_PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include "concurrency/bounded_buffer.h"

bool read_next_operation(
    FILE *file,
    graph_operation *operation);

void produce_operations(
    FILE *file,
    bounded_buffer *buffer);

#endif
