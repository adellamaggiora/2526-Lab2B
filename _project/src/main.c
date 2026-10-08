#include <stdio.h>
#include <stdlib.h>
#include "msf.h"
#include "parser.h"
#include "graph.h"
#include "error-manager.h"
#include "debug.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        terminate("The program require a filepath argument");
    }

    char *filepath = argv[1];
    FILE *file = checked_fopen(filepath, "r");
    grafo *graph = parse_file(file);
    fclose(file);
    
    // debug_print_hash_table(graph->gHash, graph->gHash_length);
    mst_kruskal(graph);
    free_graph(graph);

    // equivale a return 0
    return EXIT_SUCCESS;
}
