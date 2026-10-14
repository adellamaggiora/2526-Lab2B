#include "graph/graph.h"
#include "graph/msf.h"
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

// al termine di questo algoritmo devono essere valorizzat i campi
// "vicini", "cCon", "numCoCo", "gHash->msf" del grafo
void mst_kruskal(grafo *graph)
{
    arco **edge_list = get_edge_pointers_list(graph);
    sort_edge_pointers_list_by_weight(edge_list, graph->edge_count);
    // debug_print_pointer_list(edge_list, graph->edge_count, debug_print_edge);

    // iterazione sui nodi
    uf_node *uf_node_list = checked_malloc(graph->node_count * sizeof(uf_node));

    for (int i = 0; i < graph->node_count; i++)
    {
        make_set(&uf_node_list[i], i);
    }

    graph->costoMSF = 0;
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
