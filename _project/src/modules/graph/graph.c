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

// rimuove u dai vicini di v e viceversa
void remove_vicini(grafo *graph, const arco *edge)
{
    assert(graph != NULL);
    assert(graph->vicini != NULL);
    assert(edge != NULL);

    remove_vicino(&graph->vicini[edge->u], edge->v);
    remove_vicino(&graph->vicini[edge->v], edge->u);
}

bfs_node *bfs(const grafo *graph, int start, bool only_msf)
{
    assert(graph != NULL);
    assert(graph->vicini != NULL);
    assert(start >= 0 && start < graph->node_count);

    bfs_node *nodes = checked_calloc(graph->node_count, sizeof(bfs_node));

    circular_buffer queue;
    circular_buffer_init(&queue, graph->node_count, sizeof(int));

    // visited = true appena va nella coda
    // (anche prima di fare la pop)
    nodes[start].visited = true;
    nodes[start].parent = -1;
    circular_buffer_push(&queue, &start);

    while (!circular_buffer_is_empty(&queue))
    {
        int node;
        circular_buffer_pop(&queue, &node);

        elemento *neighbour = graph->vicini[node];
        while (neighbour != NULL)
        {
            int neighbour_id = neighbour->id;

            if ((!only_msf || neighbour->msf) && nodes[neighbour_id].visited == false)
            {
                nodes[neighbour_id].visited = true;
                nodes[neighbour_id].parent = node;
                nodes[neighbour_id].weight = neighbour->w;
                circular_buffer_push(&queue, &neighbour_id);
            }

            neighbour = neighbour->next;
        }
    }

    circular_buffer_destroy(&queue);
    return nodes;
}
