#include <stdio.h>
#include <stdlib.h>
#include "msf.h"
#include "graph.h"

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

uf_node **parse_input_file(char *filepath)
{

    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        perror("fopen");
        return NULL;
    }

    char *line_type;
    int max_node_index, total_edges;
    arco **edges;

    // lo spazio iniziale ignora tutti gli spazi, tab e newline finché non trovi un carattere vero.
    while (fscanf(file, " %c", &line_type) == 1)
    {
        switch (*line_type)
        {
        case 'p':

            fscanf(file, " sp %d %d", &max_node_index, &total_edges);
            

            break;
        case 'a':
            int n, m;
            fscanf(file, " a %d %d", &n, &m);
            break;

        default:
            break;
        }
    }

    // parsing...

    fclose(file);
    return NULL;
}
