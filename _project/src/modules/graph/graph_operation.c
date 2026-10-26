#include "graph/graph_operation.h"
#include "graph/msf.h"
#include <hash.h>
#include <components.h>
#include <error-manager.h>
#include "debug.h"

bool add_edge(grafo *graph, int u, int v, int w)
{
    // se gli identificatori dei nodi non sono validi
    if (u < 0 || v < 0 || u >= graph->node_count || v >= graph->node_count || u >= v)
    {
        return false;
    }

    // se l'arco e' gia' presente l'operazione non e' valida
    if (find_edge_in_hash_table(graph->gHash, graph->gHash_length, u, v, NULL) != NULL)
    {
        return false;
    }

    // se u e v non appartengono alla stessa cCon allora devo aggiungere tale arco alla MSF
    int u_cCon = graph->cCon[u];
    int v_cCon = graph->cCon[v];

    // aggiunta di (u,v,w) alla tabella hash gHash
    arco *edge = insert_edge_into_hash_table(graph->gHash, graph->gHash_length, u, v, w);
    if (u_cCon != v_cCon)
    {
        edge->msf = true;
        graph->costoMSF += w;
        // aggiornamento dell'array cCon delle componenti connesse
        merge_connected_components(graph, u, v);
    }
    else
    {
        // bfs fino da u a v nell'mst
        arco *max_edge = find_max_edge_on_mst_path(graph, u, v);
        // se il peso del nuovo arco (u, v, w)
        // è minore del peso max di un arco nel cammino allora lo sostituisco
        if (max_edge != NULL && w < max_edge->weight)
        {
            remove_edge_from_msf(graph, max_edge);
            edge->msf = true;
            graph->costoMSF = graph->costoMSF + (long)w - max_edge->weight;
        }
    }

    // aggiunta di u alla lista vicini[v] e di v alla lista dei vicini[u]
    add_vicini(graph, edge);
    graph->edge_count++;

    return true;
}

bool remove_edge(grafo *graph, int u, int v)
{
    // se gli identificatori dei nodi non sono validi
    if (u < 0 || v < 0 || u >= graph->node_count || v >= graph->node_count || u >= v)
    {
        return false;
    }

    arco *previous = NULL;
    arco *edge = find_edge_in_hash_table(graph->gHash, graph->gHash_length, u, v, &previous);
    // se l'arco non è nella tabella hash
    if (edge == NULL)
    {
        return false;
    }

    if (!edge->msf)
    {
        remove_vicini(graph, edge);
        remove_edge_from_hash_table(graph->gHash, graph->gHash_length, edge, previous);
        graph->edge_count--;
        return true;
    }
    else
    {
        // cancellazione di un arco della MSF ancora da implementare
        return false;
    }
}
