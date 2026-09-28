#include <stdio.h>
#include <stdlib.h>
#include "msf.h"

/*
    ******************************************
    parser per i file con formato .gr

    formato delle linee

    p sp <indice_massimo_nodi> <numero_archi>
    c <commento>
    a <u> <v> <peso>

    ******************************************
*/

// un nodo è identificabile con un numero
// ogni nodo è in biezione con un numero

// i nodi validi sono tutti quelli nell'intervallo 0..n
// se un nodo non compare in alcun arco, esiste comunque ed è una componente isolata

/*

*/

// file.txt -> array di uf_node

// ricorda pre condizioni e post condizioni
// all'inizio e la fine delle funzoini!!

uf_node **parse_input_file(char *filepath)
{

    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        perror("fopen");
        return NULL;
    }

    char *line_type;

    // lo spazio iniziale ignora tutti gli spazi, tab e newline finché trovi un carattere vero.
    while (fscanf(file, " %c", &line_type) == 1)
    {
        switch (*line_type)
        {
        case 'p':
            printf("p type!\n");
            break;
        case 'a':
            printf("a type\n");
            break;

        default:
            break;
        }
    }
    


    // parsing...

    fclose(file);
    return NULL;
}
