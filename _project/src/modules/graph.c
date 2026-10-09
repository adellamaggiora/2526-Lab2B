#include "graph.h"
#include "error-manager.h"
#include <assert.h>
#include <stdlib.h>

// private

int compare_edges(const void *x, const void *y)
{
    const arco e1 = *(const arco *)x;
    const arco e2 = *(const arco *)y;
    return e1.weight - e2.weight;
}

// public

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

void free_graph(grafo *graph)
{
    for (size_t i = 0; i < graph->gHash_length; i++)
    {
        arco *edge = graph->gHash[i];
        while (edge != NULL)
        {
            arco *next = edge->next;
            free(edge);
            edge = next;
        }
    }

    free(graph->gHash);
    free(graph);
}

void sort_edge_pointers_list_by_weight(arco **edge_pointers_list, int list_length)
{

    qsort(edge_pointers_list, list_length, sizeof(arco *), &compare_edges);
}

arco **get_edge_pointers_list(grafo *graph)
{
    arco **list = checked_malloc(graph->edge_count * sizeof(arco *));
    size_t edge_idx = 0;

    for (size_t i = 0; i < graph->gHash_length; i++)
    {
        arco *edge = graph->gHash[i];
        while (edge != NULL)
        {
            list[edge_idx] = edge;
            edge_idx++;
            edge = edge->next;
        }
    }

    return list;
}