#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

/* strutture dati già fornite nel progetto */ 

// invariante: u < v
typedef struct arco {
    int u, v;
    int weight;
    // se l'arco appartiene alla msf del grafo
    bool msf;
    struct arco *next;
} arco;

// nodo del grafo nelle liste di adiacenza della hash table
typedef struct elemento {
    int id;
    int w;
    bool msf;
    struct elemento *next;
} elemento;

// grafo
typedef struct {
    arco **gHash;
    elemento **vicini;
    int *cCon;
    int numCoCo;
    long costoMSF;
} grafo;

/***********************************************/



#endif