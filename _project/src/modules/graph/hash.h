#ifndef HASH_H
#define HASH_H

#include "graph/graph.h"


int hash_table_length(int edge_count, double load_factor);

arco *insert_edge_into_hash_table(arco **hash_table, int hash_table_length, int u, int v, int w);

// previous e' opzionale; se l'arco e' trovato riceve il precedente (NULL in testa)
arco *find_edge_in_hash_table(arco **hash_table, int hash_table_length, int u, int v, arco **previous);

// scollega e libera l'arco; previous e' ottenuto dalla ricerca nella hash
void remove_edge_from_hash_table(arco **hash_table, int hash_table_length, arco *edge, arco *previous);

#endif
