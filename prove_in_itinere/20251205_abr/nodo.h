#ifndef NODO_H
#define NODO_H

#include <stdio.h>

typedef struct nodo {
    char *chiave;
    char *linea;
    struct nodo *left;
    struct nodo *right;
} nodo;

nodo *nodo_crea(char *s1, char *s2);

void nodo_stampa(const nodo *a, FILE *f);

#endif