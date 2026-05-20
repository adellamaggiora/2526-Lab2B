#include <stdlib.h>
#include <string.h>
#include "nodo.h"

nodo *nodo_crea(char *s1, char *s2) {
    nodo *a = malloc(sizeof(*a));

    a->chiave = strdup(s1);
    a->linea = strdup(s2);

    a->left = NULL;
    a->right = NULL;

    return a;
}

//il const dice: dentro questa funzione, a punta a un nodo che non deve essere modificato.
void nodo_stampa(const nodo *a, FILE *f) {
    fprintf(f, "<%-14s> <%s>\n", a->chiave, a->linea);
}

int nodi_uguali(const nodo *a, const nodo *b) {
    int result = 0;
    if(a->chiave == b->chiave && a->linea == b->linea) {
        result = 1;
    }
    return result; 
}
