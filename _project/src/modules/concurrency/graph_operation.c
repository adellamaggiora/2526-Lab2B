#include <graph.h>
#include <hash.h>
#include <components.h>
#include <error-manager.h>
#include "debug.h"


void add_raw_edge(grafo *graph, int u, int v, int w)
{
    // se u e v non appartengono alla stessa cCon allora devo aggiungere tale arco alla MSF
    int u_cCon = graph->cCon[u];
    int v_cCon = graph->cCon[v];

    // aggiunta di (u,v,w) alla tabella hash gHash
    arco *edge = insert_edge_into_hash_table(u, v, w, graph->gHash, graph->gHash_length);
    // aggiunta di u alla lista vicini[v] e di v alla lista dei vicini[u]
    add_vicini(graph, edge);

    if (u_cCon != v_cCon)
    {
        // aggiornamento dell'array cCon delle componenti connesse
        merge_connected_components(graph, u, v);
    }

    else
    {
        bsf_result bsf = bfs_on_mst(graph, u, v);
        debug_print_list(bsf.path, bsf.path_length, sizeof(int), debug_print_int);
    }
}

void remove_edge()
{
}
