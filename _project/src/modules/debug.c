#include <stdio.h>
#include "debug.h"

void debug_print_hash_table(arco **hash_table, int table_length)
{
    for (int i = 0; i < table_length; i++)
    {
        arco *edge = hash_table[i];
        printf("gHash[%d]:", i);

        while (edge != NULL)
        {
            debug_print_edge(edge);
            edge = edge->next;
        }

        printf("\n");
    }
}

void debug_print_edge(arco *edge)
{
    printf("->(u %d, v %d, w %d, msf %s)",
           edge->u, edge->v, edge->weight,
           edge->msf ? "true" : "false");
}
