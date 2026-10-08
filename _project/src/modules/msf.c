#include "graph.h";
#include "msf.h";
#include "union_find.h"
#include "error-manager.h"
#include <stdlib.h>
#include "debug.h"
#include <assert.h>
#include "graph.h"

// il grafo al termine di questo algoritmo dovrà avere l'insieme degli archi (già popolato nel parser dentro "gHash")
// le liste di adiacenza dei singoli nodi (tabella "vicini"), le componenti connesse (array cCon).
void mst_kruskal(grafo *graph)
{

    // devo raccogliere tutti i puntatori di tutti gli archi

    printf("edge_count: %d \n", graph->edge_count);
    // permette di non fare la free perchè ho fatto allocazione nella stack
    arco edge_list[graph->edge_count];
    // l'array edge_list viene convertito in un puntatore al primo arco
    fill_edge_list(graph, edge_list);
    for (size_t i = 0; i < graph->edge_count; i++)
    {
        debug_print_edge(&edge_list[i]);
        printf("\n");
    }
    sort_edge_list_by_weight(edge_list, graph->edge_count);

    for (size_t i = 0; i < graph->edge_count; i++)
    {
        debug_print_edge(&edge_list[i]);
        printf("\n");
    }
}
