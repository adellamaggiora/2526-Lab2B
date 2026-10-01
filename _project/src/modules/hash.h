#ifndef HASH_H
#define HASH_H


#include "graph.h"

/*
 * Restituisce la lunghezza della tabella hash necessaria per ottenere il
 * fattore di carico richiesto. Restituisce 0 se load_factor non e' valido.
 */
int calculate_hash_table_length(int edge_count, double load_factor);

/* Restituisce l'indice di gHash in cui cercare o inserire edge. */
int hash_edge(const arco *edge, int hash_table_length);

#endif
