#include <stddef.h>
#include <math.h>
#include <stdint.h>
#include "graph/graph.h"
#include "graph/hash.h"



// private

static int edge_hash_index(int u, int v, int hash_table_length)
{
    // 31 numero primo
    size_t hash = u * 31 + v;
    return hash % hash_table_length;
}

// public

int hash_table_length(int edge_count, double load_factor)
{
    if (load_factor <= 0.0 || !isfinite(load_factor))
        return 0;

    if (edge_count == 0)
        return 1;

    double hash_table_length = ceil((double)edge_count / load_factor);
    return (int)hash_table_length;
}

arco *find_edge_in_hash_table(int u, int v, arco **hash_table, int hash_table_length)
{
    int edge_index = edge_hash_index(u, v, hash_table_length);
    arco *edge = hash_table[edge_index];

    while (edge != NULL && (edge->u != u || edge->v != v))
    {
        edge = edge->next;
    }

    return edge;
}

arco *insert_edge_into_hash_table(int u, int v, int w, arco **hash_table, int hash_table_length) {
    int edge_index = edge_hash_index(u, v, hash_table_length);
    arco *new_edge = build_edge(u, v, w);
    arco *current_edge = hash_table[edge_index];

    // nessuna collisione
    if (current_edge == NULL)
    {
        hash_table[edge_index] = new_edge;
    }
    else
    // se c'è collisione
    {
        while (current_edge->next != NULL)
        {
            // scorrimento della lista concatenata
            current_edge = current_edge->next;
        }
        current_edge->next = new_edge;
    }

    return new_edge;
}

