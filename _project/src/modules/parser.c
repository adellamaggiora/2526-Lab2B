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


uf_node** parse_input_file() {
    
}
