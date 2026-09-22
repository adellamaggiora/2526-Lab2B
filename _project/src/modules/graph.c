#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

// argo del grafo
typedef struct arco {
    int u, v;
    int weight;
    bool msf;
    struct arco *next;
} arco;

// nodo del grafo
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

#endif