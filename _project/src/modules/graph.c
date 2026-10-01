#include "graph.h"
#include <stdlib.h>

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
    arco *result = malloc(sizeof(arco));

    result->u = u;
    result->v = v;
    result->weight = w;
    result->msf = false;
    result->next = NULL;

    return result;
}
