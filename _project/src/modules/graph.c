#include "graph.h"
#include "error-manager.h"
#include <assert.h>

/*
    questa funzione ritorna un valore, non un puntatore
    quindi "muore" fuori dallo scope del chiamante

arco build_edge(int u, int v, int w)
{
    arco result = {
        .u = u,
        .v = v,
        .weight = w,
        .msf = false,
        .next = NULL};
    return result;
}
*/

arco *build_edge(int u, int v, int w)
{
    // invariante
    assert(u < v);
    arco *result = checked_malloc(sizeof(arco));

    result->u = u;
    result->v = v;
    result->weight = w;
    result->msf = false;
    result->next = NULL;

    return result;
}
