#include "graph/graph.h"
#include "graph/msf.h"
#include "graph/hash.h"
#include "graph/union_find.h"
#include "utils/xerrori.h"
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

    
    uf_node *uf_node_list = malloc(graph->node_count * sizeof(uf_node));
    if (uf_node_list == NULL)
        xtermina("Memory allocation failed", __LINE__, __FILE__);

    // iterazione sui nodi
    for (int i = 0; i < graph->node_count; i++)
    {
        make_set(&uf_node_list[i], i);
    }

    graph->costoMSF = 0;
    // ogni nodo parte come componente a sè stante
    graph->numCoCo = graph->node_count;
    graph->vicini = calloc(graph->node_count, sizeof(elemento *));
    if (graph->vicini == NULL)
        xtermina("Memory allocation failed", __LINE__, __FILE__);

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

    graph->cCon = calloc(graph->node_count, sizeof(int));
    if (graph->cCon == NULL)
        xtermina("Memory allocation failed", __LINE__, __FILE__);

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

    int *parent = malloc(graph->node_count * sizeof(int));
    int *queue = malloc(graph->node_count * sizeof(int));
    if (parent == NULL || queue == NULL)
        xtermina("Memory allocation failed", __LINE__, __FILE__);
    for (int i = 0; i < graph->node_count; i++)
        parent[i] = -1;

    int head = 0, tail = 0;
    parent[u] = u;
    queue[tail++] = u;

    // bfs considerando solo gli archi della MSF
    while (head < tail && parent[v] == -1)
    {
        int node = queue[head++];
        for (elemento *neighbour = graph->vicini[node]; neighbour != NULL; neighbour = neighbour->next)
        {
            if (neighbour->msf && parent[neighbour->id] == -1)
            {
                parent[neighbour->id] = node;
                queue[tail++] = neighbour->id;
            }
        }
    }

    // se v e' raggiungibile cerco l'arco massimo risalendo i parent
    if (parent[v] != -1)
    {
        for (int node = v; node != u; node = parent[node])
        {
            int x = parent[node];
            int y = node;
            // nella hash gli archi hanno sempre u < v
            if (x > y)
            {
                int tmp = x;
                x = y;
                y = tmp;
            }
            arco *edge = find_edge_in_hash_table(graph->gHash, graph->gHash_length, x, y, NULL);
            if (result == NULL || edge->weight > result->weight)
                result = edge;
        }
    }

    free(parent);
    free(queue);

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
