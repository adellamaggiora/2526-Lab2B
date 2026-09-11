Si noti che un generico arco `(u,v,w)` appare in tre posti diversi: nella tabella hash `gHash` nella lista `vicini[u]` e nella lista `vicini[v]`.

La tabella delle componente connesse deve essere mantenuta in un array cCon di lunghezza pari al numero dei nodi tale che cCon[i] contiene l'identificatore della componente connessa a cui appartiene il nodo i. L'identificatore di una componente connessa è semplicemente l'indice del nodo più piccolo in essa contenuto.

Ad esempio, in un grafo di 10 nodi le cui quattro componenti connesse sono:

```text
0 4 7 9
8 6
5 2 1
3
```

gli identificatori delle componenti sono 0, 6, 1, e 3 e l'array cCon deve contenere i valori:

```text
0 1 1 3 0 1 6 0 6 0
```

Per semplicità è opportuno che queste tre strutture dati siano riunite in una unica struct:

```c
typedef struct {
  arco **gHash;       // tabella hash (array di liste di archi)
  elemento **vicini;  // array di liste di adiacenza
  int *cCon;          // array delle componenti connesse
  int numCoCo;        // numero di componente connesse
  long costoMSF;      // costo della MSF 
} grafo;
```

Si noti che malgrado gli identificatori degli archi e dei pesi possono essere rappresentati con un int (32 bit), per il costo della MSF è necessario usare un long in quanto ci sono istanze in cui tale costo è maggiore di 2^31^.

Oltre a questi campi ne dovranno essere inseriti altri per gestire le operazioni in multithreading.

# Operazioni da supportare

Il progetto deve contenere le funzioni in grado di aggiornare le tre strutture dati viste sopra a seguito delle due seguenti operazioni.

## Aggiungi arco (u,v,w) [solo progetto completo]

Dato l'arco (u,v,w) se i due nodi u e v sono in componenti diverse della MSF l'arco viene aggiunto alla MSF. Le operazioni da fare sono quindi:

- aggiunta di (u,v,w) alla tabella hash gHash
- aggiunta di u alla lista vicini[v] e di v alla lista dei vicini[u]
- aggiornamento dell'array cCon delle componenti connesse: i nodi di una delle componenti connesse devono infatti ricevere un nuovo identificatore.

Se invece i due nodi u e v sono nella stessa componente connessa C, dopo aver aggiunto l'arco si deve verificare se il nuovo arco deve essere inserito nella MSF eseguendo le seguenti operazioni:

- si cerca l'unico cammino che collega u e v all'interno dell'albero che ricopre la componente C (si tratta di un cammino formato tutti di archi della MSF, si utilizzi vicini per costruirlo ma considerando solo gli archi con msf==true)
- all'interno di tale cammino si cerca l'arco (x,y,v) di peso massimo: se v>w allora si elimina (x,y,v) dalla MSF e si aggiunge (u,v,w)

Rispetto al caso precedente l'array cCon non deve essere modificato, ma attenzione che per eliminare (x,y,v) dalla MSF il flag msf deve essere posto a false in tutte le rappresentazioni dell'arco.

## Cancella arco (u,v,w)

Se l'arco (u,v,w) non è nella MSF si cancella dal grafo (aggiornando gHash e vicini) e non ci sono altre operazioni da fare.

Se l'arco è nella MSF lo si cancella dal grafo ma come effetto di questo la componente C contente u e v potrebbe essere spezzata in due componenti diverse. Si proceda nel seguente modo:

- si esegue una visita della componente contenente u e si costruisce la lista Lu dei nodi dell'albero di copertura raggiungibili da u (e senza passare da v dato che l'arco (u,v) è stato tolto)

- si costruisce una analoga lista Lv dei nodi della componente raggiungibili da v

- sempre utilizzando le liste di adiacenza vicini si cerca l'arco di costo minimo che collega un nodo in Lu con un nodo di Lv. Tale arco viene aggiunto alla MSF.

- Se non esistono archi che collegano Lu con Lv allora queste diventano due componenti connesse diverse ed è necessario aggiornare l'array cCon.

Al termine di entrambe le operazioni di modifica, oltre alle strutture dati devono essere aggiornati i campi costoMSF e numCoCo con i nuovi valori del costo della MSF e il numero delle componenti connesse.

# Gestione di aggiornamenti concorrenti

Le operazioni di cancellazione e inserimento degli archi sono fatti in maniera concorrente da thread diversi. Per evitare race conditions è necessario usare dei meccanismi di sincronizzazione. A questo scopo si utilizzino gli strumenti visti durante il corso; idealmente si potrebbe usare:

- un mutex per ogni posizione della tabella hash gHash: quando si deve inserire/cancellare un arco (u,v,w) che si trova nella lista gHash[i] prima di accedere alla lista si fa un lock al relativo mutex,

- una condition variable per la gestione delle componenti connesse. L'idea di base è che soltanto un thread alla volta può lavorare su una componente connessa: per imporre questo vincolo si può utilizzare un array di boolean che indica se una certa componente connessa è busy nel senso che qualche thread ci sta operando. Prima di fare un'operazione su un arco (u,v,w) si può usare una condition variable per mettersi in attesa fino a quando le componenti connesse a cui appartengono i nodi u e v non sono più busy.

Dato che non è pratico usare un numero elevato di mutex, se volete implementare la strategia del punto 1. utilizzate un array mut_gHash di nmutex elementi; quando si deve accedere a gHash[i] si effettua un lock su mut_gHash[i%nmutex].

Se lo ritenete necessario potete usare altri mutex, condition variables, o altri metodi di sincronizzazione: il valore nmutex però va considerato come la dimensione massima ammissibile di un array di mutex.

# Gestione dei thread

Il thread principale legge le operazioni di inserimento/cancellazioni da fare da un file e svolge il ruolo di produttore in uno schema produttori/consumatori. I thread consumatori, il cui numero e specificato sulla linea di comando, leggono dal buffer produttori/consumatori la descrizione di una operazione e la eseguono in maniera concorrente.

# Avvio del programma

Il programma eseguibile si deve chiamare msf.out deve essere invocato con la seguente linea di comando:

```text
msf.out  file_grafo file_archi [-t threads] [-H hashsize] [-M nmutex]  
```

dove file_grafo è il file contenente la descrizione del grafo, file_archi è il file contenente le descrizione delle operazioni di inserimento/cancellazione degli archi, il parametro -t indica il numero di threads consumatori (default 3 se -t non viene indicato), il parametro -H la dimensione della tabella hash (default 100K), il parametro -M la dimensione massima di un array di mutex (default 1000). Si noti che il parametro -H indica la dimensione massima della tabella hash, se ad esempio usate uno schema di hashing che richiede una tabella di dimensione un numero primo, utilizzate il numero primo immediatamente inferiore.

Per la gestione delle opzioni sulla linea di comando utilizzare la funzione getopt(3).

# Formato dei file di input

Il file contenente la descrizione del grafo sarà nel formato .gr descritto in questa pagina. Un esempio minimo di file .gr è il seguente:

```text
c Esempio minimo di formato .gr
p sp 6 7
c
c arco dal nodo 1 al nodo 2 di peso 17
a 1 2 17
c
a 1 3 10
a 2 4 2
a 3 5 0
a 4 6 3
a 2 5 1
a 5 6 20
```

Si noti che come indicato nella documentazione la linea p sp contiene il numero di nodi e di archi. Attenzione però che nel file i nodi sono numerati a partire da 1: dato che per noi il nodo 0 è perfettamente valido il numero di nodi effettivi è uno in più di quello indicato, Nell'esempio i nodi del grafo sono 7: 0 1 2 3 4 5 6. In alcuni file possono essere presenti anche archi che coinvolgono il nodo 0, ma se 0 non avesse archi che lo collegano agli altri nodi costituirà semplicemente una componente connessa a se stante.

Potete assumere che il file di input contenga solamente archi con u<v e che non contenga archi duplicati (attenzione che sul web si trovano grafi che non rispettano queste assunzioni).

Il file contenente le operazioni sui grafi ha il seguente formato: ogni linea deve iniziare con uno dei caratteri +, o -:

- se la linea ha la forma - u v (ad esempio - 4 10) indica un arco che deve essere eliminato
- se la linea ha la forma + u v w (ad esempio + 3 9 5) indica un arco da aggiungere, nell'esempio un arco di peso 5 che collega i nodi 3 e 9.

Le linee che non rispettano questo formato vanno ignorate. Potete assumere che in questo file gli archi siano sempre indicati con u<v.

# Esecuzione del programma

Inizialmente il programma deve calcolare la MSF con l'algoritmo di Kruskal e visualizzare su stdout tre interi che indicano rispettivamente: il numero totale di archi, il numero di componenti connesse, il costo della MSF. Nell'esempio minimo fornito sopra, ci sono 7 archi, 2 componenti connesse, e la MSF ha costo 16 quindi il primo output deve essere

```text
7 2 16
```

(scrivete semplicemente questi valori senza altre informazioni).

Successivamente il programma deve deve leggere il file delle operazioni sui grafi distribuirle ai thread consumatori i quali per ogni operazione devono scrivere l'esito che può essere di due tipi:

- una terna con: archi, componenti connesse, e costo nuovo MSF se l'operazione era valida
- il valore 0 se l'operazione non era valida: ad esempio si tenta di cancellare un arco non esistente, si tenta di aggiungere un arco già presente, oppure gli identificatori dei nodi non sono validi.

Il thread che gestisce l'operazione deve stampare su stdout con una singola printf la descrizione dell'operazione e l'esito.

Continuando l'esempio minimo fornito sopra, supponiamo che il file delle operazioni contenga le linee:

```text
+ 0 2 7
+ 4 6 1
- 5 6 
- 1 6
+ 3 9 2
- 2 4
- 3 5
```

L'output corrispondente deve essere

```text
+ 0 2 7 8 1 23
+ 4 6 1 0
- 5 6 7 1 23
- 1 6 0
+ 3 9 2 0
- 2 4 6 2 21
- 3 5 5 2 38
```

in quanto:

- l'inserimento dell'arco 0 2 7 riduce a 1 il numero delle componenti connesse e aumenta il costo della MSF a 23
- l'inserimento dell'arco 4 6 1 è illegale per l'arco è già presente
- la cancellazione dell'arco 5 6 non modifica il numero delle componenti connesse o il costo della MSF
- la cancellazione di 1 6 è illegale perché tale arco non esiste
- l'arco 3 9 è illegale perché in questo grafo i nodi vanno da 0 a 7 (dopo la costruzione iniziale il numero dei nodi non può più cambiare).
- la cancellazione dell'arco 2 3 crea due componenti connesse e il costo della MSF diventa 21.
- la cancellazione dell'arco 3 5 non modifica il numero delle componenti connesse ma il costo della MSF diventa 38 in quanto viene tolto un arco di costo 0 e viene inserito nella MSF un arco di costo 17.

> **NOTA:** chi ha il progetto ridotto deve considerare illegali tutte le operazioni di inserimento: nell'esempio precedente il risultato della prima operazione deve essere 0 2 7 0 e il grafo non deve essere cambiato.

Al termine della lettura delle operazioni i thread consumatori devono essere fatti terminare e il programma deve stampare su stdout la stringa "Operazioni terminate". Successivamente il programma deve ricalcolare il numero di archi e il costo della MSF facendo una scansione competa della tabella hash gHash e il numero delle componenti connesse contando il numero di elementi distinti in cCon e stampare la solita terna di valori: archi, componenti, costo MSF. Se non ci sono stati errori questa terna deve coincidere con quella stampata per l'ultima operazione valida. Durante questo ricalcolo finale il programma deve anche calcolare alcune statistiche sulla tabella hash: il numero di posizioni della tabella non vuota, e la lunghezza media e massima delle liste. Se nell'esempio qui sopra, i 5 archi dell grafo sono distribuite in 3 posizioni della tabella hash in liste di lunghezza rispettivamente 1, 1, e 3, il programma deve terminare stampando le seguenti stringhe:

```text
Operazioni terminate
Numero posizioni non vuote: 3
Lunghezza media liste: 1.6666667
Lunghezza massima liste: 3
5 2 38
```

Si noti che il programma deve funzionare anche con un file di operazioni vuoto o che non contiene operazioni legali: in tal caso semplicemente il grafo non viene modificato e le informazioni sulle componenti connesse stampate dopo la stringa Operazioni terminate saranno le stesse stampate al termine della lettura del grafo.

# Requisiti fondamentali

La violazione di uno solo di questi punti rende il progetto non sufficiente indipendentemente dalla correttezza dei risultati.

- non si devono usare variabili globali
- tutte le allocazioni devono essere fatte dinamicamente mediante malloc/realloc (è escluso solo il buffer-produttori consumatori)
- tutta la memoria deve essere correttamente deallocata (verificare con valgrind) .
- in caso di errori durante l'esecuzione (input non valido, malloc fallita etc) il programma deve terminare con un messaggio esplicativo su stderr e con un exit code diverso da zero; in tal caso non è necessario deallocare la memoria.
- il programma deve usare stderr per eventuali messaggi di debug e scrivere su stdout solamente le informazioni indicate nel testo
- L'eseguibile si deve chiamare msf.out e la compilazione deve avvenire in maniera automatica con il comando make. Consegnate una versione nel quale il programma viene compilato con l'opzione -O3 per velocizzare l'esecuzione.

Purtroppo a volte valgrind genera falsi positivi sostenendo erroneamente che parte della memoria non sia stata deallocata. Questo succede ad esempio se si termina un thread con la chiamata pthread_exit: evitate questo problema terminando il thread eseguendo return NULL dalla funzione iniziale del thread. Se invocate valgrind con le opzioni --leak-check=full --show-leak-kinds=all per ogni blocco di memoria non deallocato viene indicato in quale linea viene fatta l'allocazione.

# Implementazione python

Scrivere un programma python msf.py che invocato sulla linea di comando scrivendo

```text
msf.py file_grafo file_archi
```

legge il grafo contenuto in file_grafo e successivamente effettua sul grafo tutte le operazioni descritte in file_archi e infine calcola la MSF del grafo così ottenuto utilizzando l'algoritmo di Jarník/Prim. Si noti che questo algoritmo calcola l'albero di copertura per una singola componente, quindi esso deve essere ripetuto su nodi non coperti fino a quando non è stato calcolato l'albero per tutte le componenti.

Al termine della computazione il programma deve stampare su stdout il numero degli archi, il numero delle componenti connesse e il costo della MSF. Non scrivete altre informazioni su stdout, potete invece usare liberamente stderr.

Si noti che il calcolo della MSF deve esser fatta una volta sola al termine di tute le operazioni sugli archi; anche chi fa il progetto ridotto deve supportare le operazioni di aggiunta di archi.

# Implementazione java (solo progetto completo)

Scrivere un programma java che invocato sulla linea di comando scrivendo

```text
java Msf file_grafo file_archi  
```

si comporta come il programma python (legge il grafo e le operazioni sugli archi e calcola la MSF del grafo corrispondente) tranne che la MSF deve essere calcolata con l'algoritmo di Kruskal (lo stesso del C). Al termine della computazione il programma deve stampare su stdout il numero degli archi, il numero delle componenti connesse e il costo della MSF. Non scrivete altre informazioni su stdout, potete invece usare liberamente stderr.

# Consegna del progetto

La consegna deve avvenire esclusivamente mediante GitHub. Se non lo avete già createvi un account e create un repository privato dedicato a questo progetto.

Al momento della consegna aggiungete come collaboratore al repository l’utente Laboratorio2B in modo che i docenti abbiano accesso al codice. IMPORTANTE: la consegna effettiva del progetto per un dato appello consiste nello scrivere l'url per la clonazione del vostro progetto nell'apposito contenitore consegna su moodle. L'url deve essere della forma git@github.com:user/progetto.git (non deve quindi iniziare per https). Dopo la data di consegna non dovete fare altri commit al progetto. Ricordatevi che almeno cinque giorni prima della data di consegna dovete iscrivervi all'appello su esami.unipi.it.

Nel repository dovete mettere solamente i file veramente essenziali per la compilazione del progetto: quindi non i file .o gli eseguibili. All'interno del repository deve essere presente un file README.md contente la descrizione dei seguenti punti:

- il dettaglio di come vengono costruite le liste Lu e Lv all'interno della funzione cancella_arco: in particolare quali struttre dati vengono usate durante la visita della componente connessa
- Il dettaglio dell'utilizzo di mutex/condition variables/etc durante le operazioni concorrenti di aggiunta e cancellazione archi: in particolare quali operazioni sono fatte, in quale sequenza temporale e cosa garantisce che non ci siano race condition. Si deve anche illustrare con degli esempi in quali casi le operazioni vengono effettivamente effettuate in parallelo.

# Test del codice

Per controllare in anticipo la correttezza del codice quest'anno utilizzeremo le github actions che permettono di testare il vostro codice su una macchina virtuale linux, eliminando così l'uso della macchina laboratorio2 che sta diventando sempre meno affidabile.

I test sono controllati dal file ci.yml nella cartella .github/workflows e dai file di esempio che si trovano nell'archivio msf.zip. Tale archivio deve essere scompattato nella root del vostro progetto e tutti i file in esso contenuto devono essere aggiunti al progetto.

I file della cartella msf.zip vanno considerati parte del meccanismo di correzione quindi non dovete modificarli in nessun modo: ogni violazione di questa regola verrà considerata un tentativo di "imbrogliare" e segnalata alla commissione etica. L'unica eccezione è il file COMPLETO che deve essere cancellato dagli studenti che svolgono il progetto ridotto.

Quando il file ci.yml è presente, dopo ogni push verranno eseguiti i test in esso contenuti e i risultati saranno visibili nel tab Actions del progetto. Non dovete consegnare una versione che non ottiene la spunta verde nel test contenuto in ci.yml.

Si noti che per eseguire correttamente il test:

- l'eseguibile C si deve chiamare msf.out e si deve ottenere dal comando make (senza argomenti)
- il programma python deve essere in msf.py e viene eseguito con il comando python msf.py
- l'eseguibile Java deve essere Msf.class e si deve ottenere con il comando make Msf.class

Tutti questi file devono essere nella directory root del progetto (non usate directory build o simili).

---

*Ultime modifiche: lunedì, 18 maggio 2026, 12:12*
