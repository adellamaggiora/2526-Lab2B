#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>


/* 
    ***************************************
    strutture dati già fornite nel progetto
    ***************************************
    
    solo alcune prop verranno aggiunte da me (extra)
    per convenzione userò nomi delle prop in inglese 

    le prop weight e next erano le uniche prop
    in inglese già presenti
*/



// invariante: u < v
typedef struct arco {
    int u, v;
    int weight;
    // se l'arco appartiene alla msf del grafo
    bool msf;
    struct arco *next;
} arco;


// elemento di una lista di adiacenza, id rappresenta il nodo vicino
typedef struct elemento {
    int id;
    int w;
    bool msf;
    struct elemento *next;
} elemento;


typedef struct grafo {
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
} grafo;


arco *build_edge(int u, int v, int w);


#endif