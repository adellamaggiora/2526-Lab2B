#include "graph.h";
#include "msf.h";
#include "union_find.h"
#include "error-manager.h"
#include <stdlib.h>
#include "debug.h"
#include <assert.h>
#include "graph.h"

/**
 * **************************************************************
 * nota che 2 componenti connesse non possono condividere nodi
 * due archi con gli stessi estremi (u,v) non possono appartenere
 * a componenti connesse distinte
 *
 * **************************************************************
 */


 // al termine di questo algoritmo dovrò avere valorizzato i campi
 // "vicini", "cCon" e, per ogni arco, il campo "msf"
void mst_kruskal(grafo *graph)
{
    // serve una lista di puntatori perchè devo modificare gli archi 
    // (in particolare campo msf) dentro la hash table
    arco **edge_list = get_edge_pointers_list(graph);     
    sort_edge_pointers_list_by_weight(edge_list, graph->edge_count);
    debug_print_pointer_list(edge_list, graph->edge_count, debug_print_edge);
    free(edge_list);


    // arco *A = NULL;

    // // VLA
    // uf_node uf_node_list[graph->node_count];

    // // gli id dei nodi del grafo sono in biezione con l'indice
    // for (size_t i = 0; i < graph->node_count; i++)
    // {
    //     make_set(&uf_node_list[i], i);
    // }

    // // debug_print_array(uf_node_list, graph->node_count, sizeof(uf_node), debug_print_uf_node);

    // for (size_t i = 0; i < graph->edge_count; i++)
    // {
    //     arco edge = edge_list[i];
    //     // se gli archi non appartengono allo stesso insieme allora posso aggiungerli
    //     // in quanto non andranno a formare un ciclo nel grafo (albero è aciclico)
    //     if (find_set(edge.u) != find_set(edge.v))
    //     {
    //         graph->
    //         if (A == NULL)
    //         {
    //             A = &edge;
    //         }
    //         else
    //         {
    //             A->next = &edge;
    //         }
    //     }
    // }
}
