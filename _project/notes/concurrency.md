# Concorrenza del progetto

## Paradigma produttore-consumatore

Il thread principale (`main`) è l'unico **produttore**:

1. legge il file delle operazioni in modo sequenziale;
2. crea una `graph_operation` alla volta;
3. inserisce ogni operazione nella coda condivisa.

I thread worker sono i **consumatori**. Vengono creati una volta all'avvio e ciascuno:

1. estrae la prossima operazione disponibile;
2. esegue un'aggiunta oppure una cancellazione;
3. torna a prendere un'altra operazione.

Non esiste un thread dedicato alle aggiunte e uno alle cancellazioni. Ogni worker può
eseguire entrambi i tipi di operazione.

## Schema

```text
file operazioni
      |
      v
main: legge una riga alla volta
      |
      | push
      v
+------------------------+
| bounded buffer         |
| operazioni in attesa   |
+------------------------+
      |       |       |
      | pop   | pop   | pop
      v       v       v
  worker 1 worker 2 worker 3
      |       |       |
      v       v       v
    aggiunta o cancellazione
```

Esempio:

```text
main inserisce:     + arco A, - arco B, + arco C

worker 1 esegue:    + arco A
worker 2 esegue:    - arco B
worker 3 esegue:    + arco C
```

I worker possono quindi lavorare contemporaneamente. La coda garantisce che ogni
operazione venga estratta da un solo worker.

## Bounded buffer

La coda è un **bounded buffer circolare**, cioè può contenere al massimo `capacity`
operazioni:

- se è piena, il produttore attende sulla condition variable `not_full`;
- se è vuota, i consumatori attendono su `not_empty`;
- il mutex protegge `buffer`, `head`, `tail`, `count` e `closed`.

```text
0 <= count <= capacity
```

Le operazioni sono copiate direttamente nel buffer come valori di tipo
`graph_operation`: non viene eseguita una `malloc` per ogni operazione.

## Fine delle operazioni

Quando `main` raggiunge la fine del file chiama:

```c
operation_queue_close(&queue);
```

I worker completano le operazioni rimaste nella coda e terminano quando la coda è
contemporaneamente chiusa e vuota. Il `main` li attende con `pthread_join()`.

## Sincronizzazione del grafo

La coda è già thread-safe, ma questo non rende automaticamente thread-safe il grafo.

- operazioni su componenti disgiunte potranno procedere in parallelo;
- operazioni che coinvolgono la stessa componente dovranno attendere;
- le bucket della tabella hash saranno protette con mutex.

Questa seconda parte della sincronizzazione deve ancora essere implementata.

## Moduli

- `operation_queue.c/.h`: bounded buffer condiviso;
- `worker.c/.h`: ciclo dei consumatori;
- `operation_parser.c/.h`: lettura sequenziale e produzione delle operazioni;
- `main.c`: futuro produttore;
- `graph_sync.c/.h`: futura sincronizzazione del grafo.
