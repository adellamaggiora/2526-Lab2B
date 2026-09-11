## Analisi del programma

Questo è un esempio del classico paradigma **produttore-consumatori** in C con thread POSIX.

### Struttura generale

Il programma legge una lista di interi da un file e, usando più thread in parallelo, trova quali sono **numeri primi** calcolandone la **somma totale**.

---

### Componenti principali

**Buffer circolare condiviso**
Un array `buffer[Buf_size]` (20 slot) funge da "canale" tra produttore e consumatori. L'accesso è gestito con:
- un **mutex** (`mu`) per proteggere l'indice di lettura condiviso `cindex`
- due **semafori**:
  - `sem_free_slots` — slot liberi disponibili per scrivere (inizia a 20)
  - `sem_data_items` — elementi pronti da leggere (inizia a 0)

---

**Thread produttore (il `main`)**

1. Apre il file passato come argomento
2. Legge gli interi uno alla volta con `fscanf`
3. Per ogni intero: aspetta uno slot libero → scrive nel buffer → segnala dato disponibile
4. Al termine, inserisce **`cons` valori `-1`** (uno per consumer) come segnale di stop

**Thread consumatori (funzione `tbody`, × 3)**

Ogni consumer in loop:
1. Aspetta che ci sia un dato disponibile (`sem_data_items`)
2. Acquisisce il mutex, legge `buffer[cindex % Buf_size]`, incrementa `cindex`, rilascia il mutex
3. Segnala che lo slot è libero (`sem_free_slots`)
4. Se il numero è primo, incrementa il proprio contatore e somma
5. Si ferma quando legge `-1`

---

### Flusso di sincronizzazione

```
Produttore                        Consumatori (×3)
─────────────────────────────────────────────────
sem_wait(free_slots)    ←——→    sem_post(free_slots)
  scrivi buffer[pindex]           leggi buffer[cindex]  ← mutex
sem_post(data_items)    ←——→    sem_wait(data_items)
```

---

### Raccolta risultati

Dopo il `join` di tutti i thread, il main somma i risultati parziali (`quanti` e `somma`) di ogni consumer e stampa il totale dei primi trovati e la loro somma.

---

### Punto critico da notare

Il valore `-1` viene usato sia come **sentinella di terminazione** che come valore da ignorare nel calcolo (`if(n>0 && primo(n))`). Ogni consumer consuma **esattamente un** `-1` e poi esce, il che funziona correttamente solo se il produttore inserisce **esattamente `cons` sentinelle** — cosa che fa.


## Spiegazione del diagramma di sincronizzazione

Il diagramma mostra come produttore e consumatori si **coordinano** tramite i due semafori per non pestarsi i piedi.

---

### Leggi le frecce `←——→`

Non indicano una comunicazione diretta, ma una **dipendenza**: l'operazione di un lato **sblocca** quella dell'altro lato.

---

### Riga per riga

**`sem_wait(free_slots)` ←——→ `sem_post(free_slots)`**

Il produttore prima di scrivere chiede *"c'è almeno uno slot libero?"*. Se il buffer è pieno, si blocca e aspetta. È un consumer che, dopo aver letto un dato, esegue `sem_post(free_slots)` e libera uno slot — sbloccando così il produttore.

**`scrivi buffer[pindex]` … `leggi buffer[cindex]` ← mutex**

Le due operazioni non avvengono simultaneamente. Il mutex protegge solo la lettura lato consumer (perché `cindex` è condiviso tra tutti e 3 i consumer). Il produttore non ha bisogno del mutex perché `pindex` è una variabile **locale al main**, nessun altro la tocca.

**`sem_post(data_items)` ←——→ `sem_wait(data_items)`**

Dopo aver scritto, il produttore segnala *"ho messo un dato disponibile"*. I consumer stavano aspettando su `sem_wait(data_items)`: uno di loro si sblocca e va a leggere.

---

### Il ciclo completo

```
BUFFER PIENO?  →  produttore bloccato  →  consumer legge
                                           → sem_post(free_slots)
                                           → produttore sbloccato

BUFFER VUOTO?  →  consumer bloccato   →  produttore scrive
                                           → sem_post(data_items)
                                           → consumer sbloccato
```

I due semafori si comportano come **vasi comunicanti**: `free_slots` parte pieno (20) e `data_items` parte vuoto (0). Ogni scrittura sposta un "gettone" da `free_slots` a `data_items`, ogni lettura lo riporta indietro.