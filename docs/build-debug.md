# Guida alla compilazione e debug del progetto

## Ambiente di sviluppo con Docker Compose

Dalla root del repository, al primo avvio:

```bash
docker compose up -d --build
```

Compose costruisce l'immagine dal `Dockerfile` e avvia il servizio `dev` in background. La cartella del progetto viene montata in `/workspace`: le modifiche ai sorgenti sono subito disponibili nel container. La porta 5000 di `gdbgui` viene pubblicata su `localhost`.

Per gli avvii successivi basta:

```bash
docker compose up -d
```

Per entrare nella shell del container:

```bash
docker compose exec dev bash
```

I comandi di compilazione, debugging e Valgrind descritti sotto vanno eseguiti in questa shell. Si possono anche eseguire direttamente dalla root del repository, ad esempio:

```bash
docker compose exec dev make
```

Il container resta acceso anche dopo `exit` dalla shell. Per fermarlo e rimuoverlo:

```bash
docker compose down
```

I file del progetto restano sul computer. Dopo modifiche al `Dockerfile`, ripetere `docker compose up -d --build`; per modifiche ai soli sorgenti non serve ricostruire l'immagine.

Riferimenti: [docker compose up](https://docs.docker.com/reference/cli/docker/compose/up/) e [docker compose exec](https://docs.docker.com/reference/cli/docker/compose/exec/).

## Guida alla compilazione

```bash
gcc -g -Wall -Wextra -std=c11 -o <output-file> <input-file>.c
```

* `-g` -> include info utili per il debugging
* `-Wall` -> abilita molti warning utili
* `-Wextra` -> abilita warning aggiuntivi
* `-std=c11` -> usa la versione C11 del linguaggio C
* `-o <output-file>` -> indica il nome del file eseguibile prodotto
* `<input-file>.c` -> file sorgente C, contenente la funzione `main()`

Esempio:

```bash
gcc -g -Wall -Wextra -std=c11 -o <output-file> <input-file>.c
```

## Guida al debugging

Per compilare un programma in modo adatto al debugging:

```bash
gcc -g -Wall -Wextra -std=gnu11 -o <output-file> <input-file>.c
```

Poi si può avviare il debugger da terminale:

```bash
gdb <compiled-file>
```

Oppure dal browser con `gdbgui`:

```bash
gdbgui -r --host 0.0.0.0 --port 5000 <compiled-file>
```

Per passare argomenti al programma, ad esempio il percorso di un file di input, usare `--args` come ultima opzione:

```bash
gdbgui -r --host 0.0.0.0 --port 5000 --args ./<compiled-file> <input-file>
```

Tutto ciò che segue `--args` viene passato al programma da eseguire.

Dal browser aprire:

```text
http://localhost:5000
```

## Controllo della memoria con Valgrind

Compilare il programma con l'opzione `-g`, quindi eseguirlo con:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./<compiled-file> [argomenti]
```

Valgrind segnala accessi non validi alla memoria e blocchi allocati che non sono stati correttamente deallocati. Al termine dell'esecuzione verificare in particolare che non siano presenti errori e perdite indicate come `definitely lost`.
