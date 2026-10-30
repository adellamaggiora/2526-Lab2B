#include "graph/graph.h"
#include "graph/msf.h"
#include "graph/hash.h"
#include "graph/union_find.h"
#include "utils/error-manager.h"
#include <stdlib.h>
#include "utils/debug.h"
#include <assert.h>

/**
 * *******************************************************
 * nota due archi con gli stessi estremi (u,v) non possono
 * appartenere a componenti connesse distinte
 *
 * *******************************************************
 */

static int compare_edges(const void *x, const void *y)
{
    // arrivano puntatori a puntatori (invocazione da compare_edges)
    arco *e1 = *(arco **)x;
    arco *e2 = *(arco **)y;

    return (e1->weight > e2->weight) - (e1->weight < e2->weight);
}

static void sort_edge_pointers_list_by_weight(arco **edge_pointers_list, int list_length)
{

    // qsort chiama compare_edges passando gli indirizzi di ciò che è contenuto nell'array
    qsort(edge_pointers_list, list_length, sizeof(arco *), &compare_edges);
}

// al termine di questo algoritmo devono essere valorizzat i campi
// "vicini", "cCon", "numCoCo", "gHash->msf" del grafo
void mst_kruskal(grafo *graph)
{
    arco **edge_list = get_edge_pointers_list(graph);
    sort_edge_pointers_list_by_weight(edge_list, graph->edge_count);
    // debug_print_pointer_array(edge_list, graph->edge_count, debug_print_edge);

    
    uf_node *uf_node_list = checked_malloc(graph->node_count * sizeof(uf_node));

    // iterazione sui nodi
    for (int i = 0; i < graph->node_count; i++)
    {
        make_set(&uf_node_list[i], i);
    }

    graph->costoMSF = 0;
    // ogni nodo parte come componente a sè stante
    graph->numCoCo = graph->node_count;
    graph->vicini = checked_calloc(graph->node_count, sizeof(elemento *));

    // iterazione su archi
    for (size_t i = 0; i < graph->edge_count; i++)
    {
        arco *edge = edge_list[i];
        uf_node *u = &uf_node_list[edge->u];
        uf_node *v = &uf_node_list[edge->v];

        if (find_set(u) != find_set(v))
        {
            // modifico l'arco della lista, quindi del grafo (puntatore)
            edge->msf = true;
            // unione delle componenti con euristica del rango
            union_set(u, v);
            graph->costoMSF += edge->weight;
            // quando collego 2 nodi decremento le CoCo
            graph->numCoCo--;
        }

        // L'arco non orientato compare nella lista di entrambi gli estremi.
        add_vicini(graph, edge);
    }

    graph->cCon = checked_calloc(graph->node_count, sizeof(int));

    // seconda iterazione su nodi perchè qui conosco le componenti (alberi uf_node)
    for (int i = 0; i < graph->node_count; i++)
    {
        // find_set ha costo ammortizzato per la path compression
        uf_node *root = find_set(&uf_node_list[i]);
        // cCon è l'id minimo
        graph->cCon[i] = root->min_id;
    }

    free(uf_node_list);
    free(edge_list);


}

// restituisce l'arco massimo sul cammino da u a v nell'albero di copertura minimo
arco *find_max_edge_on_mst_path(grafo *graph, int u, int v)
{
    assert(graph != NULL);
    assert(u >= 0 && u < graph->node_count);
    assert(v >= 0 && v < graph->node_count);
    arco *result = NULL;

    bfs_node *nodes = bfs(graph, u, true);

    // se v e' raggiungibile cerco l'arco massimo risalendo i parent
    if (nodes[v].visited && u != v)
    {
        int max_node = v;
        for (int node = v; node != u; node = nodes[node].parent)
        {
            if (nodes[node].weight > nodes[max_node].weight)
                max_node = node;
        }

        int x = nodes[max_node].parent;
        int y = max_node;
        // nella hash gli archi hanno sempre u < v
        if (x > y)
        {
            int tmp = x;
            x = y;
            y = tmp;
        }
        result = find_edge_in_hash_table(graph->gHash, graph->gHash_length, x, y, NULL);
    }

    free(nodes);

    return result;
}

// sia nell'array vicini che nella tabella hash
void remove_edge_from_msf(grafo *graph, arco *edge)
{
    assert(graph != NULL);
    assert(graph->vicini != NULL);
    assert(edge != NULL);

    edge->msf = false;

    // aggiorno il flag anche nelle due liste di adiacenza
    for (elemento *neighbour = graph->vicini[edge->u]; neighbour != NULL; neighbour = neighbour->next)
    {
        if (neighbour->id == edge->v)
        {
            neighbour->msf = false;
            break;
        }
    }

    for (elemento *neighbour = graph->vicini[edge->v]; neighbour != NULL; neighbour = neighbour->next)
    {
        if (neighbour->id == edge->u)
        {
            neighbour->msf = false;
            break;
        }
    }
}
