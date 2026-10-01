#include "hash.h"
#include <math.h>
#include <stdint.h>
#include "graph.h"


// private

int edge_hash_index(int u, int v, int hash_table_length)
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

int insert_edge_into_hash_table(int u, int v, int w, arco **hash_table, int hash_table_length) {
    int edge_index = edge_hash_index(u, v, w);
    arco *new_edge = build_edge(u, v, w);
    arco *existing_edge = hash_table[edge_index];
    if (existing_edge == NULL)
    {
        hash_table[edge_index] = new_edge;
    }
    else
    {
        while (existing_edge->next != NULL)
        {
            // scorrimento della lista di adiacenza
            existing_edge = existing_edge->next;
        }
        hash_table[edge_index] = new_edge;
    }    
}