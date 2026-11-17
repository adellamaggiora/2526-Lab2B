# Bug Fixed

## Funzione inserisci_nodo_in_albero 

```C
void inserisci_nodo_in_albero(nodo *n, nodo *albero) {
    int ris_compara = compara_nodi(n, albero);

    if(albero->left == NULL && albero->right == NULL) {
        if(ris_compara > 0) {
            albero->right = n;
        }
        else if(ris_compara < 0) {
            albero->left = n;
        }
        else {
            free(n);
            fprintf(stderr, "errore: nodi uguali\n");
        }
        return;
    }
    // n > albero; si inserisce nel sottoalbero destro
    if(ris_compara > 0) {
        inserisci_nodo_in_albero(n, albero->right);
    }
    else if(ris_compara < 0) {
        inserisci_nodo_in_albero(n, albero->left);
    }
    else {
        free(n);
        fprintf(stderr, "errore: nodi uguali\n");
    }
    return result; 
}
```

[BUG]
albero è foglia -> posso inserire il nodo

[OK]
albero ha figlio sx vuoto -> posso inserire nodo a sx (se ris_compara < 0)
albero ha figlio dx vuoto -> posso inserire nodo a dx (se ris_compara > 0)

### Comportamento

radice a (prima linea)
nodo b (seconda linea)
nodo c (altra linea)
nodo d (lineasenzasecondaparola)
nodo e (linea molto moooooooooooolto lunga)


ins(b, a) // inserimento b in radice a
b < a -> b figlio sx a
c < a -> c va nel sottoalbero sx di a
c < b -> c figlio sx di b
d < a -> d va nel sottoalbero sx di a
d < b -> d va nel sottoalbero sx di b
d < c -> d è figlio sx di c 

[BUG] e > a -> e è figlio dx di a


```text
             a
      		/ \	
           b   e	
	      /
         c
        /
       d
```

## Funione tokenize

```C
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
  result[0] = key;
  return result;
}
```

[WARNING]
Semantica di ownership poco chiara:
Il chiamante si aspetterebbe di utilizzare la funzione e deallocare tutti i riferimenti (puntatori) del risultato (una coppia di stinghe, quindi un puntatore a 2 puntatori). 
Invece la funzione non alloca tutti i puntatori del risultato: 
```C
result[0] = strtok(NULL);
```
infatti la funzione strtok non alloca niente ma va a modifica la stringa passata come input.
Soluzione:
```C
result[0] = strdup(key);
```
perchè la strdup alloca un nuovo spazio di memoria per clonare la stringa (malloc under the hood)

### Relaazione in-place / modifica l'argomento passato

implicazione:
in-place -> modifica l'argomento