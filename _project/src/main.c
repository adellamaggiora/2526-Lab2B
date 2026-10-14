#include <stdio.h>
#include <stdlib.h>
#include "graph/msf.h"
#include "io/graph_parser.h"
#include "graph/graph.h"
#include "utils/error-manager.h"
#include "utils/debug.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        terminate("The program require a filepath argument");
    }

    char *filepath = argv[1];
    FILE *file = checked_fopen(filepath, "r");
    grafo *graph = parse_graph(file);
    fclose(file);
    
    // debug_print_hash_table(graph->gHash, graph->gHash_length);
    mst_kruskal(graph);
    printf("%d %d %ld\n", graph->edge_count, graph->numCoCo, graph->costoMSF);
    free_graph(graph);

    
    return EXIT_SUCCESS;
}
