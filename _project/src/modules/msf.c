#include "graph.h";
#include "msf.h";
#include "union_find.h"
#include "error-manager.h"
#include <stdlib.h>
#include "debug.h"
#include <assert.h>
#include "graph.h"

/**
 * *******************************************************
 * nota due archi con gli stessi estremi (u,v) non possono
 * appartenere a componenti connesse distinte
 *
 * *******************************************************
 */

// al termine di questo algoritmo dovrò avere valorizzato i campi
// "vicini", "cCon" e, per ogni arco, il campo "msf"
void mst_kruskal(grafo *graph)
{
    // serve una lista di puntatori perchè devo modificare gli archi del grafo
    arco **edge_list = get_edge_pointers_list(graph);
    sort_edge_pointers_list_by_weight(edge_list, graph->edge_count);
    // debug_print_pointer_list(edge_list, graph->edge_count, debug_print_edge);

    // iterazione sui nodi
    uf_node *uf_node_list = checked_malloc(graph->node_count * sizeof(*uf_node_list));
    
    for (int i = 0; i < graph->node_count; i++)
    {
        make_set(&uf_node_list[i], i);
    }

    graph->costoMSF = 0;
    graph->numCoCo = graph->node_count;

    // iterazione su archi
    for (size_t i = 0; i < graph->edge_count; i++)
    {
        arco *edge = edge_list[i];
        uf_node *u = &uf_node_list[edge->u];
        uf_node *v = &uf_node_list[edge->v];

        if (find_set(u) != find_set(v))
        {
            // modifico l'arco della lista, quindi del grafo
            edge->msf = true;
            // unione delle componenti con euristica del rango
            union_set(u, v);
            graph->costoMSF += edge->weight;
            graph->numCoCo--;
        }
    }

    free(uf_node_list);
    free(edge_list);


}
