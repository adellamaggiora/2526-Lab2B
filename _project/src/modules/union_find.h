#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef struct uf_node
{
    int id;
    uf_node *parent;
    int rank;
} uf_node;


// sono giuste?
uf_node *make_set(int x);
uf_node *find_set(uf_node *x);
uf_node *union_set(uf_node *x, uf_node *y);

#endif