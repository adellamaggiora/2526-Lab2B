#include "union_find.h"
#include "error-manager.h"

uf_node *make_set(int x)
{
    uf_node *result = checked_malloc(sizeof(uf_node));
    result->id = x;
    result->rank = 0;
    // nodo radice
    result->parent = NULL;
    return result;
}

uf_node *find_set(uf_node *x)
{
    if (x->parent == NULL)
        return x;

    // (path compression) collega direttamente x alla radice del suo insieme
    x->parent = find_set(x->parent);
    return x->parent;
}

uf_node *union_set(uf_node *x, uf_node *y)
{
    uf_node *set_x = find_set(x);
    uf_node *set_y = find_set(y);

    if (set_x == set_y)
        return set_x;

    // (union by rank) collega la radice con rank minore a quella con rank maggiore
    if (set_x->rank < set_y->rank)
    {
        set_x->parent = set_y;
        return set_y;
    }

    if (set_x->rank > set_y->rank)
    {
        set_y->parent = set_x;
        return set_x;
    }

    // se i rank sono uguali, sceglie una radice e ne incrementa il rank
    set_y->parent = set_x;
    set_x->rank++;

    return set_x;
}
