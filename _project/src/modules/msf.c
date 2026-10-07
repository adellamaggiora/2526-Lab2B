#include "graph.h";
#include "msf.h";
#include "union_find.h"
#include "error-manager.h"
#include <stdlib.h>



void sort_graph_edges_by_weight(grafo *graph)
{

}



// il grafo al termine di questo algoritmo dovrà avere l'insieme degli archi (già popolato nel parser dentro "gHash")
// le liste di adiacenza dei singoli nodi (tabella "vicini"), le componenti connesse (array cCon).
void mst_kruskal(grafo *graph)
{


    // devo raccogliere tutti i puntatori di tutti gli archi

    arco *edge_list = checked_calloc(graph->edge_count, sizeof(arco));
    int edge_idx = 0;

    for (size_t i = 0; i < graph->gHash_length; i++)
    {
        // arco edge* = graph->gHash[i];
        // while (edge != NULL)
        // {
        //     edge_list[edge_idx] = edge;    
        //     edge = edge + sizeof(arco);
        //     edge_idx ++;    
        // }
        
    }

    free(edge_list);
    
}


// dentro la union find faccio il calcolo delle componenti connesse
