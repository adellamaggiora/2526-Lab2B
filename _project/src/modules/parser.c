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

uf_node *parse_file(char *filepath)
{

    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        perror("fopen");
        return NULL;
    }

    // possibile problema di memoria (valgrind) identificatore non inizalizzato
    char line_type;
    //
    int max_node_index, total_edges;
    arco **edges;
    uf_node *nodes = NULL;

    // lo spazio iniziale ignora tutti gli spazi, tab e newline
    // finché non viene trovato un carattere vero.
    while (fscanf(file, " %c", &line_type) == 1)
    {
        switch (line_type)
        {
        case 'p':
            // memorizzo i dati, verranno usati gli ultimi
            // nel caso ci fosse la riga p multipla
            fscanf(file, " sp %d %d", &max_node_index, &total_edges);
            break;
        case 'a':
            int u, v, w;
            fscanf(file, " a %d %d", &u, &v, &w);
            break;
        default:
            break;
        }
    }

    int total_nodes = max_node_index + 1;
    nodes = malloc(total_nodes * sizeof(uf_node));

    for (size_t i = 0; i < (total_nodes); i++)
    {
        uf_node node = {
            .id = i,
            .parent = NULL, // occorre inizializzare al parent corretto o va bene NULL?
            .rank = 0};
        
        nodes[i] = node;
    }

    

    fclose(file);
    return nodes;
}
