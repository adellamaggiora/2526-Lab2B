#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // richiesto per usare errno dentro termina()
#include "nodo.h"

// inserimento dei nodi in un ABR secondo il seguente ordinamento:

// ordinamento nodi secondi il campo chiave
// chiave uguale -> ordinamento secondo il campo linea
// chiave e linea uguali -> nodi uguali

/* algoritmo */

// 1. leggere dal file
// 2. forall linea -> crea_nodo
// 3. inserimento (log n?) ordinato (strcmp) in ABR (rispettando le prop ABR)
// 4. visita in-order e inserire nel file output_stampa.txt
// 5. free e controllo con valgrind su memoria

// funzione che verifica se esiste il file
void check_file_exists(FILE *file) {
  if (file == NULL) {
    printf("Errore apertura file");
    exit(1);
  }
}


// line in input: 'prima linea'
// output atteso: <linea> <prima linea>
char **tokenize(const char *line) {
  //sistemare 
  char *separator = " ";
  int token_index = 1;
  char *cloned_line = strdup(line);
  // alloca un array di 2 stringhe
  // sizeof(char *) -> quanti byte occupa un puntatore a char
  // puntatore a stringa occupa 8 byte
  char **result = malloc(2 * sizeof(char *));
  result[1] = cloned_line;
  strtok(line, separator);
  // NULL serve a passare al token successivo nella strtok
  char *key = strtok(NULL, separator);
  //controlla il valore del puntatore, cioè l’indirizzo contenuto in key, non la stringa puntata.
  if(key == NULL) {
    // non scrive dentro la memoria puntata da key. 
    // Cambia dove punta key: ora key punta a una string literal vuota, 
    key = ""; 
  }
  result[0] = strdup(key);
  return result;
}
// argc è un intero che indica il numero di parametri passato (lunghezza dell'array argv)
// argv[0] è il nome del file eseguito
int main(int argc, char *argv[]) {

  if(argc!=2) {
    printf("Uso: %s nomefile\n",argv[0]);
    exit(1);
  }
  
  FILE *f_input = fopen(argv[1], "r");
  check_file_exists(f_input);

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  
  nodo *albero;
  int counter = 0;

  while ((read = getline(&line, &len, f_input)) != -1) {
    // -2 perchè il terminatore di linea di windows è \r\n
    line[strlen(line)-2] = '\0';
    char **couple = tokenize(line);
    // printf("%s - %s\n", couple[0], couple[1]);
    
    nodo *n = nodo_crea(couple[0], couple[1]);
    if(counter == 0) {
      albero = n;
      counter++;
    }
    else {
      inserisci_nodo_in_albero(n, albero);
    }
    visita_albero(albero);
    free(couple[0]);
    free(couple[1]);
    free(couple);
  }

  free(line);
  fclose(f_input);

  return 0;
  
}
