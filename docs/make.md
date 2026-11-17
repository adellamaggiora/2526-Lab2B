# Comandi Make

Dalla root del repository, in WSL/Linux con Docker attivo:

- `make help`: mostra tutti i comandi e le variabili disponibili.
- `make image`: costruisce o aggiorna l'immagine Docker `lab2`; ripetere dopo modifiche al `Dockerfile`.
- `make dev`: avvia il container, compila, avvia `gdbgui` su `http://localhost:5000` e apre Bash, con il progetto montato in `/workspace`.
- `make dev FILE=msf/rome99.gr`: apre il debugger con un altro file di input; il valore predefinito è `msf/minimo.gr`.
- `make run`: compila nel container ed esegue `build/msf.out` sul file `msf/minimo.gr`.
- `make run FILE=msf/rome99.gr`: compila ed esegue su un altro file, con percorso relativo alla root.
- `make valgrind`: compila nel container e controlla la memoria usando `msf/minimo.gr`.
- `make valgrind FILE=msf/rome99.gr`: esegue il controllo su un altro file. Mostra tutti i tipi di perdite e restituisce errore se Valgrind rileva problemi.
- `make dev DEBUG_PORT=5001`: avvia shell e debugger su `http://localhost:5001`, utile se la porta 5000 è occupata.
- `make dev IMAGE=nome-immagine`: usa un'immagine diversa; `IMAGE=...` vale anche per `image`, `run` e `valgrind`.

`dev`, `run` e `valgrind` creano automaticamente l'immagine se manca. Se la compilazione fallisce, esecuzione e Valgrind non partono. I container vengono rimossi al termine; i file del progetto restano sul computer.

Nella shell aperta da `make dev`:

- `make` oppure `make all`: compila in `build/msf.out`.
- `make clean`: elimina la cartella `build` e il vecchio eseguibile `msf.out`.
- `tail -f /tmp/gdbgui.log`: mostra i log del debugger già avviato da `make dev`.
- `exit`: chiude shell e debugger e rimuove il container.

Compilazione e debug manuali, nella shell del container:

- `gcc -g -O0 -Wall -Wextra -std=gnu11 -o programma file.c`: compila un singolo file C; per il progetto completo usare `make`.
- `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/msf.out msf/minimo.gr`: controlla accessi alla memoria, perdite e origine dei valori non inizializzati.

Nel prompt di GDB:

- `break main`: imposta un punto di arresto in `main`.
- `run`: avvia il programma.
- `next` / `step`: esegue la riga successiva, senza entrare / entrando nelle funzioni chiamate.
- `continue`: riprende l'esecuzione fino al prossimo arresto.
- `print variabile`: mostra il valore di una variabile.
- `bt`: mostra la sequenza delle chiamate attive.
- `quit`: chiude GDB.
