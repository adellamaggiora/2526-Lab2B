#ifndef OPERATION_PARSER_H
#define OPERATION_PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include "graph/graph_operation.h"

bool read_next_operation(
    FILE *file,
    graph_operation *operation);

#endif
