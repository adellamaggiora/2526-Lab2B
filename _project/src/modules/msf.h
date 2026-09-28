#ifndef MSF_H
#define MSF_H

/*
    id del nodo non necessario;
    biezione con l'indice dell'array
*/
typedef struct uf_node
{
    int parent;
    int rank;
} uf_node;

#endif