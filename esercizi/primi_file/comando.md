### Esercizio: produttore-consumatori con buffer circolare, pthread e semafori

Realizzare in linguaggio C un programma concorrente basato sul paradigma **1 produttore / N consumatori**. Il programma deve ricevere da riga di comando il nome di un file contenente una sequenza di interi positivi, uno per riga o separati da spazi. Il produttore, eseguito dal thread principale, deve leggere gli interi dal file e inserirli in un **buffer circolare condiviso** di dimensione finita. I consumatori, eseguiti da thread ausiliari, devono prelevare i valori dal buffer, verificare quali sono numeri primi e calcolare localmente quanti primi hanno trovato e la loro somma.

#### Specifiche funzionali

Il programma deve essere eseguito nel formato `./programma file_input`. Se il numero di argomenti non è corretto, deve stampare un messaggio d’uso e terminare. Il file di input contiene esclusivamente interi positivi. Il thread principale deve leggere progressivamente i valori dal file e inserirli nel buffer condiviso. I thread consumatori devono prelevare i valori dal buffer, testarli con una funzione `primo(int n)` e aggiornare due contatori locali: numero di primi trovati e somma dei primi trovati.

#### Specifiche concorrenti

Il buffer condiviso deve essere gestito come **buffer circolare**. L’accesso agli indici condivisi deve essere protetto da un mutex. La sincronizzazione tra produttore e consumatori deve essere realizzata con due semafori: uno per contare gli slot liberi del buffer e uno per contare gli elementi disponibili. Il produttore non deve scrivere se il buffer è pieno. I consumatori non devono leggere se il buffer è vuoto. La soluzione deve evitare busy waiting, race condition, deadlock e accessi fuori dai limiti del buffer.

#### Terminazione

Quando il produttore ha terminato la lettura del file, deve inserire nel buffer un valore speciale di terminazione per ciascun consumatore. Il valore di terminazione deve essere riconoscibile perché non appartiene ai dati validi del file. Ogni consumatore, quando legge il valore di terminazione, deve terminare correttamente restituendo al thread principale i propri risultati parziali. Il thread principale deve eseguire la `join` di tutti i consumatori, sommare i risultati parziali e stampare il numero totale di primi trovati e la loro somma complessiva.

#### Vincoli tecnici

Usare `pthread`, `pthread_mutex_t` e `sem_t`. Definire una struttura dati per passare ai thread consumatori tutti i parametri necessari, inclusi buffer condiviso, indice di lettura, mutex, semafori e campi di output. La dimensione del buffer deve essere fissata tramite `#define`. Il numero di consumatori può essere fissato nel codice, purché sia maggiore di zero. Le primitive di sincronizzazione devono essere inizializzate prima della creazione dei thread e distrutte prima della terminazione del programma. La funzione di test di primalità deve gestire correttamente i casi `n < 2`, i numeri pari e i divisori dispari.

#### Output richiesto

Al termine dell’esecuzione, il programma deve stampare una riga contenente il numero totale di primi trovati e la somma totale dei primi. Il formato dell’output è libero ma deve essere chiaro, ad esempio: `Trovati X primi con somma Y`.

#### Test consigliati

Verificare il programma con file piccoli, costruiti manualmente, per controllare facilmente il risultato atteso. Successivamente testare il programma con file più grandi generati automaticamente, contenenti molti interi positivi. Controllare che il risultato sia stabile su esecuzioni ripetute: risultati diversi a parità di input indicano quasi certamente una race condition.

#### Obiettivo didattico

L’obiettivo dell’esercizio è comprendere il coordinamento tra thread produttori e consumatori tramite buffer condiviso, mutex e semafori, distinguendo correttamente tra mutua esclusione, disponibilità di dati, disponibilità di spazio e terminazione ordinata dei thread.
