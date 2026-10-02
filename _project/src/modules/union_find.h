#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef struct uf_node
{
    int id;
    struct uf_node *parent;
    int rank;
} uf_node;


// sono giuste?
void make_set(uf_node *x);
uf_node *find_set(uf_node *x);
void union_set(uf_node *x, uf_node *y);

#endif