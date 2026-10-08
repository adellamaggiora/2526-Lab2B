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
    // VLA variable length array sullo stack
    arco edge_list[graph->edge_count];
    // prendo tutti gli archi dalla tabella hash del grafo
    // permette di non fare la free perchè ho fatto allocazione nella stack
    // l'array edge_list viene convertito in un puntatore al primo arco
    fill_edge_list(graph, edge_list);
    sort_edge_list_by_weight(edge_list, graph->edge_count);

    debug_print_array(edge_list, graph->edge_count, sizeof(arco), debug_print_edge);

    // arco *edge_set = NULL;
    // int edge_set_size = 0;

    // // VLA
    // uf_node uf_node_list[graph->node_count];

    // // gli id dei nodi del grafo sono in biezione con l'indice
    // for (size_t i = 0; i < graph->node_count; i++)
    // {
    //     make_set(&uf_node_list[i], i);
    // }

    // for (size_t i = 0; i < graph->edge_count; i++)
    // {
    //     arco edge = edge_list[i];
    // }
}
