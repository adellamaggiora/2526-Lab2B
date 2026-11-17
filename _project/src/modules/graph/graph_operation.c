#include "graph/graph_operation.h"
#include "graph/msf.h"
#include <hash.h>
#include <components.h>
#include <error-manager.h>
#include "debug.h"
#include <stdlib.h>

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
        graph->costoMSF -= edge->weight;
        remove_vicini(graph, edge);
        remove_edge_from_hash_table(graph->gHash, graph->gHash_length, edge, previous);
        graph->edge_count--;

        // se elimino un arco che appartiene al MST allora la cCon potrebbe cambiare

        bool *Lu = bfs(graph, u, true);
        bool *Lv = bfs(graph, v, true);

        // cerco l'arco di peso minimo che collega i due sottoalberi
        arco *min_edge = NULL;
        for (int i = 0; i < graph->node_count; i++)
        {
            if (!Lu[i])
                continue;

            for (elemento *neighbour = graph->vicini[i]; neighbour != NULL; neighbour = neighbour->next)
            {
                if (Lv[neighbour->id] && (min_edge == NULL || neighbour->w < min_edge->weight))
                {
                    int x = i < neighbour->id ? i : neighbour->id;
                    int y = i < neighbour->id ? neighbour->id : i;
                    min_edge = find_edge_in_hash_table(graph->gHash, graph->gHash_length, x, y, NULL);
                }
            }
        }

        if (min_edge != NULL)
        {
            remove_vicini(graph, min_edge);
            min_edge->msf = true;
            add_vicini(graph, min_edge);
            graph->costoMSF += min_edge->weight;
        }
        else
        {
            // i due sottoalberi diventano componenti connesse distinte
            int min_u = u;
            int min_v = v;
            for (int i = 0; i < graph->node_count; i++)
            {
                if (Lu[i] && i < min_u)
                    min_u = i;
                if (Lv[i] && i < min_v)
                    min_v = i;
            }

            for (int i = 0; i < graph->node_count; i++)
            {
                if (Lu[i])
                    graph->cCon[i] = min_u;
                if (Lv[i])
                    graph->cCon[i] = min_v;
            }
            graph->numCoCo++;
        }

        free(Lu);
        free(Lv);

        return true;
    }
}
