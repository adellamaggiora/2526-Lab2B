#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

/* 
    ***************************************
    strutture dati già fornite nel progetto
    ***************************************
    
    solo alcune prop verranno aggiunte da me
    per convenzione userò nomi delle prop in inglese 

    chiamare le prop in inglese mi aiuta anche a distinguere
    a colpo d'occhio le proprietà "extra"
    (ad eccezione di weight e next :( )

*/ 

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
typedef struct grafo {
    arco **gHash;
    elemento **vicini;
    int *cCon;
    int numCoCo;
    long costoMSF;
    /*
        prop aggiunte dopo il parsing
    */ 
    // tot nodi
    int node_count;
    // tot archi
    int edge_count;
} grafo;

/***********************************************/



#endif