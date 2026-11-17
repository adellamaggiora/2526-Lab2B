#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph/msf.h"
#include "io/graph_parser.h"
#include "graph/graph.h"
#include "graph/graph_operation.h"
#include "utils/xerrori.h"
#include "utils/debug.h"


int main(int argc, char *argv[])
{

    // valori di default
    int threads = 3;
    int hashsize = 100000;
    int nmutex = 1000;


    const char *usage = "Uso: msf.out file_grafo file_archi [-t threads] [-H hashsize] [-M nmutex]";

    int option;
    while ((option = getopt(argc, argv, "t:H:M:")) != -1)
    {
        if (option == '?')
            xtermina(usage, __LINE__, __FILE__);

        int value = xpositive_int(optarg, __LINE__, __FILE__);

        switch (option)
        {
        case 't': threads = value; break;
        case 'H': hashsize = value; break;
        case 'M': nmutex = value; break;
        }
    }

    if (argc - optind != 2)
        xtermina(usage, __LINE__, __FILE__);

    char *filepath = argv[optind];
    char *operations_path = argv[optind + 1];

    // Parametri letti, da usare nelle parti ancora da implementare.

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
