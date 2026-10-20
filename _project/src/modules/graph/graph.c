#include "graph/graph.h"
#include "utils/error-manager.h"
#include <assert.h>
#include <stdlib.h>

/*
*******
private
*******
*/

static int compare_edges(const void *x, const void *y)
{
    // arrivano puntatori a puntatori (invocazione da compare_edges)
    arco *e1 = *(arco **)x;
    arco *e2 = *(arco **)y;

    return (e1->weight > e2->weight) - (e1->weight < e2->weight);
}

// passo puntatore alla testa per poterla modificare
static void insert_vicino_sorted_by_id(
    elemento **head,
    int id,
    int weight,
    bool msf)
{
    assert(head != NULL);

    elemento *new_element = checked_malloc(sizeof(*new_element));
    new_element->id = id;
    new_element->w = weight;
    new_element->msf = msf;
    new_element->next = NULL;

    // inserisco prima del primo vicino con id >= id.
    while (*head != NULL && (*head)->id < id)
    {
        head = &((*head)->next);
    }

    new_element->next = *head;
    *head = new_element;
}

/*
*******
public
*******
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

    if (graph->vicini != NULL)
    {
        for (int i = 0; i < graph->node_count; i++)
        {
            elemento *current = graph->vicini[i];

            while (current != NULL)
            {
                elemento *next = current->next;
                free(current);
                current = next;
            }
        }
    }

    free(graph->gHash);
    free(graph->vicini);
    free(graph->cCon);
    free(graph);
}

void sort_edge_pointers_list_by_weight(arco **edge_pointers_list, int list_length)
{

    // qsort chiama compare_edges passando gli indirizzi di ciò che è contenuto nell'array
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

// aggiunge u come vicino di v e viceversa
void add_vicini(grafo *graph, const arco *edge)
{
    assert(graph != NULL);
    assert(graph->vicini != NULL);
    assert(edge != NULL);

    insert_vicino_sorted_by_id(
        &graph->vicini[edge->u],
        edge->v,
        edge->weight,
        edge->msf);

    insert_vicino_sorted_by_id(
        &graph->vicini[edge->v],
        edge->u,
        edge->weight,
        edge->msf);
}


// cerca il path da u a v solo nell'albero di copertura minimo
arco *bfs_on_mst(grafo *graph, int u, int v)
{

    
    





    elemento *vicini_u = graph->vicini[u];

    

}
