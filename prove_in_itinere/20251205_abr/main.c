#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // richiesto per usare errno dentro termina()


int main(int argc, char *argv[])
{

  if(argc!=2) {
    printf("Uso: %s nomefile\n",argv[0]);
    exit(1);
  }
  FILE *f = fopen(argv[1],"r");
  if(f==NULL) termina("Errore apertura file");
  fprintf(stdout, "Uso: %s file\n", argv[1]);
}

void termina(const char *messaggio)
{
  if(errno==0) 
     fprintf(stderr,"%s\n",messaggio);
  else 
    perror(messaggio);
  exit(1);
}