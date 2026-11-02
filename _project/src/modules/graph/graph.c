#include "graph/graph.h"
#include "data_structures/circular_buffer.h"
#include "utils/error-manager.h"
#include <assert.h>
#include <stdlib.h>

// passo puntatore alla testa per poterla modificare
static void insert_vicino_sorted_by_id(elemento **head, int id, int weight, bool msf)
{
    assert(head != NULL);

    elemento *new_element = checked_malloc(sizeof(*new_element));
    new_element->id = id;
    new_element->w = weight;
    new_element->msf = msf;
    new_element->next = NULL;

    // inserisco prima del primo vicino con id >= id
    while (*head != NULL && (*head)->id < id)
    {
        head = &((*head)->next);
    }

    new_element->next = *head;
    *head = new_element;
}

static void remove_vicino(elemento **head, int id)
{
    while (*head != NULL && (*head)->id != id)
    {
        head = &((*head)->next);
    }

    if (*head != NULL)
    {
        elemento *removed = *head;
        *head = removed->next;
        free(removed);
    }
}

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


void remove_vicini(grafo *graph, const arco *edge)
{
    assert(graph != NULL);
    assert(graph->vicini != NULL);
    assert(edge != NULL);

    remove_vicino(&graph->vicini[edge->u], edge->v);
    remove_vicino(&graph->vicini[edge->v], edge->u);
}


bool *bfs(const grafo *graph, int start, bool only_msf)
{
    assert(graph != NULL);
    assert(graph->vicini != NULL);
    assert(start >= 0 && start < graph->node_count);

    bool *nodes = checked_calloc(graph->node_count, sizeof(bool));

    circular_buffer queue;
    circular_buffer_init(&queue, graph->node_count, sizeof(int));

    // è visitato (true) appena va nella coda
    // (anche prima di fare la pop, non uso coplore grigio)
    nodes[start] = true;
    circular_buffer_push(&queue, &start);

    while (!circular_buffer_is_empty(&queue))
    {
        int node;
        circular_buffer_pop(&queue, &node);

        elemento *neighbours_list = graph->vicini[node];
        while (neighbours_list != NULL)
        {
            int neighbour_id = neighbours_list->id;

            if ((!only_msf || neighbours_list->msf) && nodes[neighbour_id] == false)
            {
                nodes[neighbour_id] = true;
                circular_buffer_push(&queue, &neighbour_id);
            }

            neighbours_list = neighbours_list->next;
        }
    }

    circular_buffer_destroy(&queue);
    return nodes;
}
