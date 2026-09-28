#include "graph.h";
#include "msf.h";


void kruskal(arco *archi, int num_archi, int num_nodi)
{
    uf_node *uf = malloc(num_nodi * sizeof(*uf));

    for (int i = 0; i < num_nodi; i++) {
        uf[i].parent = i;
        uf[i].rank = 0;
    }

    // usa uf in Kruskal

    free(uf);
}