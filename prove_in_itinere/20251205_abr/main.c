#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // richiesto per usare errno dentro termina()


void termina(const char *messaggio) {
  if(errno==0) 
     fprintf(stderr,"%s\n",messaggio);
  else 
    perror(messaggio);
  exit(1);
}


// argc è un intero che indica il numero di parametri passato (lunghezza dell'array argv)
// argv[0] è il nome con cui è stato avviato il programma
int main(int argc, char *argv[]) {

  if(argc!=2) {
    printf("Uso: %s nomefile\n",argv[0]);
    exit(1);
  }

  FILE *f = fopen(argv[1], "r");

  if (f == NULL) {
    termina("Errore apertura file");
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, f)) != -1) {
    printf("%zd\n", read);
    printf("%s", line);
  }
   printf("%zd\n", read);

  free(line);
  fclose(f);
}
