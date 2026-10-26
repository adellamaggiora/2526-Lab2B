#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

/*
    ***************************************
    strutture dati già fornite nel progetto
    ***************************************

    solo alcune prop sono aggiunte da me (extra)
    uso nomi delle prop in inglese

    ad eccezione di "weight", "next" e "msf"
    erano le uniche prop già presenti in inglese
*/

// invariante: u < v
typedef struct arco
{
    int u, v;
    int weight;
    // se l'arco appartiene alla msf del grafo
    bool msf;
    struct arco *next;
} arco;


// elemento di una lista di adiacenza, id rappresenta il nodo vicino
typedef struct elemento
{
    int id;
    int w;
    bool msf;
    struct elemento *next;
} elemento;


typedef struct grafo
{
    arco **gHash;
    // questo array è indicizzato con l'id del nodo
    elemento **vicini;
    /*
        cCon[i] contiene l'identificatore della componente connessa del nodo i-esimo
        L'identificatore di una comp. connessa è il più piccolo dei nodi della componente
    */
    int *cCon;
    int numCoCo;
    long costoMSF;

    /*
        prop "extra" (aggiunte da me)
    */
    int node_count;
    int edge_count;
    int gHash_length;
} grafo;


// usato in un array: l'indice e' in biezione con l'id del nodo, quindi non serve next
typedef struct bfs_node
{
    bool visited;
    int parent;
    // peso dell'arco che collega il nodo al parent
    int weight;
} bfs_node;


// functions

arco *build_edge(int u, int v, int w);


arco **get_edge_pointers_list(grafo *graph);


void free_graph(grafo *graph);


void add_vicini(grafo *graph, const arco *edge);

void remove_vicini(grafo *graph, const arco *edge);

// visita tutti i nodi raggiungibili
// only_msf limita la visita agli archi della MSF
// restituisce un array indicizzato per nodo, da liberare con free
bfs_node *bfs(const grafo *graph, int start, bool only_msf);


#endif
