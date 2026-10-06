#include "graph.h";
#include "msf.h";
#include "union_find.h"
#include "error-manager.h"
#include <stdlib.h>

void mst_kruskal(grafo *graph)
{

    uf_node *uf = checked_malloc(graph->node_count * sizeof(*uf));

    for (int i = 0; i < graph->node_count; i++) {
        uf[i].parent = i;
        uf[i].rank = 0;
    }

    // usa uf in Kruskal

    free(uf);
}


// dentro la union find faccio il calcolo delle componenti connesse
