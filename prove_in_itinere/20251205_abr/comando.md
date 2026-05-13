# Esercizio: Albero Binario di Ricerca con chiave e linea

Si consideri la struttura:

```c
typedef struct nodo {
  char *chiave;
  char *linea;
  struct nodo *left, *right;
} nodo;
````

che rappresenta il nodo di un albero binario di ricerca, ABR, contenente i campi `chiave` e `linea`.

All'interno dell'ABR i nodi sono ordinati secondo il campo `chiave`; se i campi `chiave` sono uguali, l'ordinamento è basato sul campo `linea`; se entrambi sono uguali, i nodi sono considerati uguali.

È obbligatorio usare la funzione:

```c
nodo *nodo_crea(char *s1, char *s2)
{
  nodo *a  = malloc(sizeof(*a));
  a->chiave = strdup(s1); // creo una copia di s1 e l'assegno a chiave
  a->linea = strdup(s2);  // creo una copia di s2 e l'assegno a linea
  a->left = a->right = NULL;
  return a;
}
```

per la creazione di un nodo date le due stringhe `s1` e `s2`, e la funzione:

```c
void nodo_stampa(const nodo *a, FILE *f) {
  fprintf(f,"<%-14s> <%s>\n",a->chiave,a->linea);
}
```

per scrivere su `f` una rappresentazione del nodo `a`.

Scrivere un programma `abr.c` che legge dalla linea di comando il nome di un file di testo e, partendo da un ABR vuoto, esegue le seguenti operazioni su tutte le linee del file:

1. utilizzando la funzione `getline`, legge la linea copiandola in un buffer `b`;
2. esegue `b[strlen(b)-1]='\0'` per cancellare il carattere `\n` in fondo alla linea;
3. utilizzando la funzione `strtok`, tokenizza una copia della linea rispetto al separatore `" "` spazio e salva una copia del secondo token in una stringa `z`;
4. aggiunge all'ABR un nuovo nodo `n` con `z` come campo `chiave` e `b` come campo `linea`.

## Casi particolari

Se il nuovo nodo è uguale a un nodo già presente nell'albero, non deve essere inserito, ma semplicemente deallocato, e il programma deve stampare un messaggio su `stderr`.

Se non esiste il secondo token, come campo `chiave` si deve usare la stringa `"MANCA"`.

Dopo l'inserimento nell'ABR, il programma deve stampare su `stdout` l'elenco dei nodi nell'ordine crescente dell'ABR, deallocare tutta la memoria utilizzata, verificare con `valgrind`, e terminare.

## Esempio

Se il file di input contiene:

```text
prima linea
seconda linea
altra linea
lineasenzasecondaparola
linea molto moooooooooooooooooooooooooooooooooooooolto lunga
linea ripetuta più volte
linea ripetuta più volte
linea ripetuta più volte
QUI RICORDA CHE LE MAIUSCOLE PRECEDONO LE MINUSCOLE
linea ripetuta più volte
linea ripetuta più volte
linea ripetuta più volte
la prossima linea è vuota

fine
```

l'output dovrebbe essere:

```text
<MANCA         > <>
<MANCA         > <fine>
<MANCA         > <lineasenzasecondaparola>
<RICORDA       > <QUI RICORDA CHE LE MAIUSCOLE PRECEDONO LE MINUSCOLE>
<linea         > <altra linea>
<linea         > <prima linea>
<linea         > <seconda linea>
<molto         > <linea molto moooooooooooooooooooooooooooooooooooooolto lunga>
<prossima      > <la prossima linea è vuota>
<ripetuta      > <linea ripetuta più volte>
```

in quanto la quarta e le ultime due righe non hanno il secondo token e quindi la loro chiave è `MANCA`.

I caratteri `<` e `>` e gli spazi sono inseriti dalla funzione `nodo_stampa()`, che dovete usare per visualizzare un nodo.