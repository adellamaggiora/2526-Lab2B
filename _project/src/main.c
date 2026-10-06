#include <stdio.h>
#include <stdlib.h>
#include "msf.h"
#include "parser.h"
#include "graph.h"
#include "error-manager.h"



int main(int argc, char *argv[])
{

    if (argc != 2) {
        terminate("The program require a filepath argument");
    }

    char *filepath = argv[1];
    FILE *file = checked_fopen(filepath, "r");
    grafo *graph = parse_file(file);
    fclose(file);
    


    free(graph);

    // 2. Logica del programma o chiamata a funzioni esterne
    printf("Hello, World!\n");

    // 3. Pulizia della memoria (se applicabile)

    // Ritorna un codice di successo al sistema operativo
    return EXIT_SUCCESS; // Equivalente a 'return 0;'
}
