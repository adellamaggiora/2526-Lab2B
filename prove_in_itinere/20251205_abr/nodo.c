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

    // caso base
    if(ris_compara < 0 && albero->left == NULL) {
        albero->left = n;
        return;
    }
    else if(ris_compara > 0 && albero->right == NULL) {
        albero->right = n;
        return;
    }


    // casi ricorsivi
    else if(ris_compara > 0) {
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

void visita_albero(nodo *albero, FILE *f) {
    if(albero == NULL) {
        return;
    }
    visita_albero(albero->left, f);
    int chiave_vuota = (strcmp(albero->chiave, "") == 0);
    if(chiave_vuota) {
        albero->chiave = "MANCA";
    }
    nodo_stampa(albero, f);
    visita_albero(albero->right, f);
}