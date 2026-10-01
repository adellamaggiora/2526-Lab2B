#ifndef HASH_H
#define HASH_H


int hash_table_length(int edge_count, double load_factor);

int insert_edge_into_hash_table(int u, int v, int w, arco **hash_table, int hash_table_length);

#endif
