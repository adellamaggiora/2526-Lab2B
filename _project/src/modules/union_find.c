#include "union_find.h"
#include "error-manager.h"
#include <assert.h>

/*
    I nodi del grafo sono contenuti in un insieme   che è
    implementato con un albero. Tale insieme serve a Kruskal
    per verificare se due nodi u, v di un arco appartengo
    allo stesso insieme, quindi alla stessa componente connessa

    è utile usare 2 euristiche per ottimizzare
    le operazioni su tale insieme (albero)

    UNION BY RANK = Il rango rappresenta l'altezza dell'albero
    quando unisco 2 insiemi (2 alberi) attacco l'albero di rango
    più basso alla radice dell'albero con rango più alto.
    Questo serve ad avere un ALBERO BILANCIATO

    PATH COMPRESSION = quando vado a cercare l'insieme di appartenenza
    di un nodo (quindi il nodo rappresentante, quindi la radice)
    mano a mano che incontro nodi lungo il "cammino di risalita"
    li attacco al nodo rappresentante (radice) non appena quest'ultimo
    verrà trovato
*/

/*
    inizializza un uf_node
    senza sprecare memoria dinamica
*/
void make_set(uf_node *node, int x)
{
    assert(node != NULL);
    assert(x >= 0);

    node->id = x;
    node->rank = 0;
    node->parent = NULL;
}

uf_node *find_set(uf_node *x)
{
    assert(x != NULL);

    if (x->parent == NULL)
    {
        return x;
    }

    uf_node *parent = find_set(x->parent);
    x->parent = parent;
    return parent;
}

uf_node *union_set(uf_node *x, uf_node *y)
{
    assert(x != NULL);
    assert(y != NULL);

    // l'albero più basso viene attaccato
    // alla radice dell'albero più alto

    uf_node *set_x = find_set(x);
    uf_node *set_y = find_set(y);

    if (set_x == set_y)
    {
        return set_x;
    }

    uf_node *set;

    if (set_x->rank > set_y->rank)
    {
        set_y->parent = set_x;
        set = set_x;
    }
    else if (set_y->rank > set_x->rank)
    {
        set_x->parent = set_y;
        set = set_y;
    }
    // ranghi uguali
    else
    {
        set_y->parent = set_x;
        set_x->rank++;
        set = set_x;
    }
    
    return set;
}
