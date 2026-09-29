#ifndef MSF_H
#define MSF_H

/*
    id in biezione con l'indice dell'array
*/
typedef struct uf_node
{
    int id;
    int parent;
    int rank;
} uf_node;

#endif