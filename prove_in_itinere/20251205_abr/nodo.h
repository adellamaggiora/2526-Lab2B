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

int compara_nodi(const nodo *a, const nodo *b);

void inserisci_nodo_in_albero(nodo *n, nodo *albero);

void aggiungi_chiave_mancante(nodo *n);

void visita_albero(nodo *albero, FILE *f);

#endif