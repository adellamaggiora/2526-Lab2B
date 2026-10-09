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



// il grafo al termine di questo algoritmo dovrà avere l'insieme degli archi (già popolato nel parser dentro "gHash")
// le liste di adiacenza dei singoli nodi (tabella "vicini"), le componenti connesse (array cCon).
void mst_kruskal(grafo *graph)
{
    // VLA variable length array sullo stack
    arco edge_list[graph->edge_count];
    
    // permette di non fare la free (allocazione nella stack)
    // l'array edge_list viene convertito in un puntatore al primo arco
    fill_edge_list(graph, edge_list);
    sort_edge_list_by_weight(edge_list, graph->edge_count);
    // debug_print_array(edge_list, graph->edge_count, sizeof(arco), debug_print_edge);


    uf_node *edge_set = NULL;

    // VLA
    uf_node uf_node_list[graph->node_count];

    // gli id dei nodi del grafo sono in biezione con l'indice
    for (size_t i = 0; i < graph->node_count; i++)
    {
        make_set(&uf_node_list[i], i);
    }

    // debug_print_array(uf_node_list, graph->node_count, sizeof(uf_node), debug_print_uf_node);

    for (size_t i = 0; i < graph->edge_count; i++)
    {
        arco edge = edge_list[i];
        // se gli archi non appartengono allo stesso insieme allora posso aggiungerli 
        // in quanto non andranno a formare un ciclo nel grafo (albero è aciclico)
        if (find_set(edge.u) != find_set(edge.v))
        {
            if (edge_set == NULL)
            {
                edge_set = &edge;
            }
            
            edge_set = &edge;
            edge_set += 1;
        }
        
    }
}
