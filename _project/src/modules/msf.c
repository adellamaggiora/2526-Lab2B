#include "graph.h";
#include "msf.h";
#include "union_find.h"
#include "error-manager.h"
#include <stdlib.h>;
#include "debug.h";
#include <assert.h>

// void sort_edge_list_by_weight(arco **edge_list, size_t list_length)
// {
//     int compare_edges(const void *x, const void *y)
//     {
//         const arco *e1 = (const arco *)x;
//         return e1->weight - e2->weight;
//     }


//     qsort(edge_list, list_length, sizeof(arco *), &compare_edges);
// }

// vuole una lista vuota già allocata in memoria
void fill_edge_list(grafo *graph, arco **empty_edge_list)
{
    size_t edge_idx = 0;

    for (size_t i = 0; i < graph->gHash_length; i++)
    {
        arco *edge = graph->gHash[i];
        while (edge != NULL)
        {
            empty_edge_list[edge_idx] = edge;
            edge_idx++;
            edge = edge->next;
        }
    }
}

// il grafo al termine di questo algoritmo dovrà avere l'insieme degli archi (già popolato nel parser dentro "gHash")
// le liste di adiacenza dei singoli nodi (tabella "vicini"), le componenti connesse (array cCon).
void mst_kruskal(grafo *graph)
{

    // devo raccogliere tutti i puntatori di tutti gli archi

    printf("edge_count: %d \n", graph->edge_count);
    // permette di non fare la free perchè ho fatto allocazione nella stack
    arco *edge_list[graph->edge_count];
    fill_edge_list(graph, edge_list);

    for (size_t i = 0; i < graph->edge_count; i++)
    {
        debug_print_edge(edge_list[i]);
        printf("\n");
    }
}

// dentro la union find faccio il calcolo delle componenti connesse
