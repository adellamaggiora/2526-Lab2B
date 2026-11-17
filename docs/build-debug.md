# Guida alla compilazione e debug del progetto

## Ambiente di sviluppo con Docker

Dalla root del repository, creare l'immagine con gli strumenti di compilazione e debugging:

```bash
docker build . -t <image-name>
```

Per avviare il container ed entrare direttamente nella shell:

```bash
docker run -it --rm -v "${PWD}:/workspace" -p 5000:5000 <image-name>
```

Sostituire `<image-name>` con il nome scelto per l'immagine. La cartella del progetto viene montata in `/workspace`: le modifiche ai sorgenti sono subito disponibili nel container. La porta 5000 viene pubblicata per `gdbgui`.

I comandi di compilazione, debugging e Valgrind descritti sotto vanno eseguiti in questa shell. Con `exit` il container si ferma e viene rimosso; i file del progetto restano sul computer. Ricostruire l'immagine solo dopo modifiche al `Dockerfile`.

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
