#include "hash.h"
#include <math.h>
#include <stdint.h>


int calculate_hash_table_length(int edge_count, double load_factor)
{
    if (load_factor <= 0.0 || !isfinite(load_factor))
        return 0;

    if (edge_count == 0)
        return 1;

    double hash_table_length = ceil((double)edge_count / load_factor);
    return (int)hash_table_length;
}

int hash_edge(const arco *edge, int hash_table_length)
{
    size_t hash = edge->u * 31 + edge->v;
    return hash % hash_table_length;
}

