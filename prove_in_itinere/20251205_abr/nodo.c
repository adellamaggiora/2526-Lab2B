#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nodo.h"

nodo *nodo_crea(char *s1, char *s2)
{
    nodo *a = malloc(sizeof(*a));

    a->chiave = strdup(s1);
    a->linea = strdup(s2);

    a->left = NULL;
    a->right = NULL;

    return a;
}

// il const dice: dentro questa funzione, a punta a un nodo che non deve essere modificato.
void nodo_stampa(const nodo *a, FILE *f)
{
    fprintf(f, "<%-14s> <%s>\n", a->chiave, a->linea);
}

// a > b => positivo; a < b => negativo; a = b => 0;
int compara_nodi(const nodo *a, const nodo *b)
{

    int ris_strcmp = strcmp(a->chiave, b->chiave);
    if (ris_strcmp == 0)
    {
        ris_strcmp = strcmp(a->linea, b->linea);
    }
    return ris_strcmp;
}

void inserisci_nodo_in_albero(nodo *n, nodo *albero)
{
    int ris = compara_nodi(n, albero);

    if (ris > 0) {
        if (albero->right == NULL)
            albero->right = n;
        else
            inserisci_nodo_in_albero(n, albero->right);
    }
    else if (ris < 0) {
        if (albero->left == NULL)
            albero->left = n;
        else
            inserisci_nodo_in_albero(n, albero->left);
    }
    else {
        // meglio: nodo_distruggi(n), non solo free(n)
        free(n);
        fprintf(stderr, "errore: nodi uguali\n");
    }
}

void aggiungi_chiave_mancante(nodo *n)
{
    if (n->chiave == NULL)
    {
        n->chiave = "MANCA";
    }    
}

void visita_albero(nodo *albero, FILE *f)
{
    if (albero == NULL)
    {
        return;
    }
    visita_albero(albero->left, f);
    aggiungi_chiave_mancante(albero);
    nodo_stampa(albero, f);
    // printf("%s: %s", albero->chiave, albero->linea);
    visita_albero(albero->right, f);
}