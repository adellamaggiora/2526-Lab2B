#ifndef MSF_H
#define MSF_H

#include "graph/graph.h"

void mst_kruskal(grafo *graph);

// aggiorna solo i flag msf, senza cancellare l'arco dal grafo
void remove_edge_from_msf(grafo *graph, arco *edge);

// restituisce l'arco massimo del cammino nella MSF, oppure NULL se non ci sono archi
// l'arco appartiene al grafo e non deve essere liberato dal chiamante
arco *find_max_edge_on_mst_path(grafo *graph, int u, int v);

#endif
