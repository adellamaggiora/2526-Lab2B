# Compilazione, debug e memoria

Nel terminale Linux/WSL o del container, dalla root del progetto:

```bash
make                # compila e crea msf.out
make clean          # elimina l'eseguibile
make debug          # ricompila sempre e avvia gdbgui
make memory-check   # ricompila sempre ed esegue Valgrind
```

Puoi eseguire direttamente `make debug` o `make memory-check`: entrambi ricompilano sempre il programma C prima di avviare lo strumento. Se la compilazione fallisce, si fermano.

Apri `http://localhost:5000` nel browser e premi **Run**. Per fermarti all'inizio, scrivi `break main` nella console GDB prima di avviare il programma.

Debug e controllo della memoria usano 3 thread, il grafo `msf/minimo.gr` e le operazioni `msf/minimo.mp`. Per cambiarli, modifica `ARGS` nel `Makefile`.

Valgrind mostra accessi non validi, valori non inizializzati e perdite di memoria; restituisce un codice diverso da zero se rileva errori.