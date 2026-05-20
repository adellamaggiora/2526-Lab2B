#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include "nodo.h"

nodo *nodo_crea(char *s1, char *s2) {
    nodo *a = malloc(sizeof(*a));

    a->chiave = strdup(s1);
    a->linea = strdup(s2);

    a->left = NULL;
    a->right = NULL;

    return a;
}

// il const dice: dentro questa funzione, a punta a un nodo che non deve essere modificato.
void nodo_stampa(const nodo *a, FILE *f) {
    fprintf(f, "<%-14s> <%s>\n", a->chiave, a->linea);
}

// a > b => positivo; a < b => negativo; a = b => 0; 
int compara_nodi(const nodo *a, const nodo *b) {

    int ris_strcmp = strcmp(a->chiave, b->chiave);
    if(ris_strcmp == 0) {
        ris_strcmp = strcmp(a->linea, b->linea);
    }
    return ris_strcmp; 
}

void inserisci_nodo_in_albero(nodo *n, nodo *albero) {
    int ris_compara = compara_nodi(n, albero);

    if(albero->left == NULL && albero->right == NULL) {
        if(ris_compara > 0) {
            albero->right = n;
        }
        else if(ris_compara < 0) {
            albero->left = n;
        }
        else {
            free(n);
            fprintf(stderr, "errore: nodi uguali\n");
        }
        return;
    }
    // n > albero; si inserisce nel sottoalbero destro
    if(ris_compara > 0) {
        inserisci_nodo_in_albero(n, albero->right);
    }
    else if(ris_compara < 0) {
        inserisci_nodo_in_albero(n, albero->left);
    }
    else {
        free(n);
        fprintf(stderr, "errore: nodi uguali\n");
    }
}

void visita_albero(nodo *albero) {
    if(albero == NULL) {
        return;
    }
    visita_albero(albero->left);
    printf("%s: %s", albero->chiave, albero->linea);
    visita_albero(albero->right);
}