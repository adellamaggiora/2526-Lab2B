#include <stdio.h>
#include <stdlib.h>
#include "graph/msf.h"
#include "io/graph_parser.h"
#include "graph/graph.h"
#include "graph/graph_operation.h"
#include "utils/xerrori.h"
#include "utils/debug.h"


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        xtermina("The program require a filepath argument", __LINE__, __FILE__);
    }

    char *filepath = argv[1];
    FILE *file = xfopen(filepath, "r", __LINE__, __FILE__);
    grafo *graph = parse_graph(file);
    fclose(file);

    // debug_print_hash_table(graph->gHash, graph->gHash_length);

    mst_kruskal(graph);
    // debug_print_hash_table(graph->gHash, graph->gHash_length);
    // fprintf(stderr, "edge count: %d numCoCo: %d costoMSF: %ld\n", graph->edge_count, graph->numCoCo, graph->costoMSF);

    // add_edge(graph, 1, 3, 3);
    // debug_print_hash_table(graph->gHash, graph->gHash_length);
    // remove_edge(graph, 2, 4); // nella MSF, peso 2
    // remove_edge(graph, 5, 6); // fuori dalla MSF, peso 20




    free_graph(graph);
    return EXIT_SUCCESS;
}
