#include "graph/components.h"

#include <assert.h>

void merge_connected_components(grafo *graph, int u, int v)
{
    assert(graph != NULL);
    assert(graph->cCon != NULL);
    assert(u >= 0 && u < graph->node_count);
    assert(v >= 0 && v < graph->node_count);

    int u_component = graph->cCon[u];
    int v_component = graph->cCon[v];

    if (u_component == v_component)
        return;

    // prendo la minima tra le due componenti connesse
    int min_cCon, max_cCon;
    if (u_component < v_component)
    {
        min_cCon = u_component;
        max_cCon = v_component;
    }
    else
    {
        min_cCon = v_component;
        max_cCon = u_component;
    }

    for (int i = 0; i < graph->node_count; i++)
    {
        // aggiorno la cCon più grande
        if (graph->cCon[i] == max_cCon)
            graph->cCon[i] = min_cCon;
    }

    graph->numCoCo--;
}
