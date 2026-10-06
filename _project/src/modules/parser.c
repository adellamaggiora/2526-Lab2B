#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error-manager.h"
#include "graph.h"
#include "hash.h"

/*
    ******************************************
    parser dei file con formato .gr
    ******************************************

    formato delle linee:

    p sp <indice_massimo_nodi> <numero_archi>
    c <commento>
    a <u> <v> <peso>

    //////////////////////////////////////////

    - un nodo è identificabile con un numero

    - ogni nodo è in biezione con un numero

    - i nodi validi sono tutti quelli nell'intervallo 0..n

    - se un nodo non compare in alcun arco, esiste comunque
      ed è una componente isolata

    ******************************************
*/

grafo *parse_file(FILE *file)
{
    assert(file != NULL);
    char line_type;
    grafo *graph = checked_calloc(1, sizeof(*graph));

    // lo spazio iniziale ignora tutti gli spazi, tab e newline
    // finché non viene trovato un carattere vero.
    while (fscanf(file, " %c", &line_type) == 1)
    {
        switch (line_type)
        {
        case 'p':
            int node_count, edge_count;
            if (fscanf(file, " sp %d %d", &node_count, &edge_count) != 2)
                terminate("Invalid graph header");
            graph->gHash_length = hash_table_length(edge_count, 0.6);
            graph->node_count = node_count + 1;
            graph->edge_count = edge_count;
            graph->gHash = checked_calloc(graph->gHash_length, sizeof(arco *));
            
            break;
        case 'a':
            int u, v, w;
            if (fscanf(file, " %d %d %d", &u, &v, &w) != 3)
                terminate("Invalid edge");
            insert_edge_into_hash_table(u, v, w, graph->gHash, graph->gHash_length);
            break;
        default:
            int ch;
            // faccio la get char finchè non cosnumo la linea (termina con \n)
            // oppure la fine del file EOF
            while ((ch = fgetc(file)) != '\n' && ch != EOF);
            break;
        }
    }

    return graph;
}
