#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph/msf.h"
#include "io/graph_parser.h"
#include "io/operation_parser.h"
#include "concurrency/bounded_buffer.h"
#include "concurrency/consumer.h"
#include "graph/graph.h"
#include "graph/graph_operation.h"
#include "utils/xerrori.h"
#include "utils/debug.h"


int main(int argc, char *argv[])
{

    // valori di default (specs.md)
    int threads = 3;
    int hashsize = 100000;
    int nmutex = 1000;


    int option;
    while ((option = getopt(argc, argv, "t:H:M:")) != -1)
    {
        if (option == '?')
            xtermina("Unknown option or missing argument", __LINE__, __FILE__);

        int value = xpositive_int(optarg, __LINE__, __FILE__);

        switch (option)
        {
        case 't': threads = value; break;
        case 'H': hashsize = value; break;
        case 'M': nmutex = value; break;
        }
    }

    if (argc - optind != 2)
        xtermina("Exactly two files are required: graph file and operations file", __LINE__, __FILE__);

    char *filepath = argv[optind];
    char *operations_path = argv[optind + 1];

    // Parametri letti, da usare nelle parti ancora da implementare.

    FILE *file = xfopen(filepath, "r", __LINE__, __FILE__);
    grafo *graph = parse_graph(file);
    fclose(file);

    // debug_print_hash_table(graph->gHash, graph->gHash_length);

    mst_kruskal(graph);

    FILE *operations_file = xfopen(operations_path, "r", __LINE__, __FILE__);

    bounded_buffer buffer;
    bounded_buffer_init(&buffer, 64);

    // creazione dei consumatori che stanno in attesa di estrarre dal buffer
    pthread_t *consumers = checked_malloc((size_t)threads * sizeof(*consumers));
    for (int i = 0; i < threads; i++)
    {
        xpthread_create(&consumers[i], NULL, consume_operations, &buffer, __LINE__, __FILE__);
    }

    // produttore (main) che inserisce la prossima operazione
    graph_operation operation;
    while (read_next_operation(operations_file, &operation))
    {
        enqueue_operation(&buffer, operation);
    }
    fclose(operations_file);

    // la coda vuota non significa necessariamente che un consumatore abbia finito
    // occorre inserire un terminatore che permetta di fare la join
    graph_operation end = {.type = END_OPERATIONS};
    for (int i = 0; i < threads; i++)
    {
        enqueue_operation(&buffer, end);
    }

    for (int i = 0; i < threads; i++)
    {
        // join è un punto di attesa per il thread main (produttore)
        // prosegue solo quando tutti i thread sono terminati
        xpthread_join(consumers[i], NULL, __LINE__, __FILE__);
    }

    free(consumers);
    bounded_buffer_destroy(&buffer);



    // debug_print_hash_table(graph->gHash, graph->gHash_length);
    // fprintf(stderr, "edge count: %d numCoCo: %d costoMSF: %ld\n", graph->edge_count, graph->numCoCo, graph->costoMSF);




    // add_edge(graph, 1, 3, 3);
    // debug_print_hash_table(graph->gHash, graph->gHash_length);
    // remove_edge(graph, 2, 4); // nella MSF, peso 2
    // remove_edge(graph, 5, 6); // fuori dalla MSF, peso 20




    free_graph(graph);
    return EXIT_SUCCESS;
}
