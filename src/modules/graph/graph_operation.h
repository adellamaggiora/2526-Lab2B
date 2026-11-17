#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H

#include "graph/graph.h"


typedef enum graph_operation_type {
    ADD_EDGE,
    REMOVE_EDGE
} graph_operation_type;


// operazione parsata e nel buffer
typedef struct graph_operation {
    graph_operation_type type;
    int u;
    int v;
    int weight;
} graph_operation;


bool add_edge(grafo *graph, int u, int v, int w);

bool remove_edge(grafo *graph, int u, int v);




#endif
