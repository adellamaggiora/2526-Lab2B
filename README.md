## Materiale didattico per il corso di Laboratorio 2B, Anno accademico 2025/26 

Questo repository contiene gli esempi di codice fatti a lezione e il registro delle lezioni. Altro materiale utile si trova sul [corso Moodle](https://elearning.di.unipi.it/course/view.php?id=1059).

### Guida all'uso di Docker

- Abbiamo creato un Docker file (dentro a questo repository) dove usiamo Ubuntu e tutti gli strumenti necessari per la compilazione dei progetti
- ```docker build . -t ubuntu-dev``` (creazione immagine Docker)
- ```docker run -it --rm -v ${pwd}:/workspace ubuntu-dev``` (avvio del container in modo interattivo). Nota che pwd è la cartella corrente (dove ci troviamo) e deve essere quel progetto. In alternativa, al posto di ```${pwd}``` si può usare anche il proprio percorso assoluto, ad esempio ```docker run -it --rm -v C:\Users\Andrea\repos\2526-Lab2B:/workspace ubuntu-dev```

### Guida alla compilazione

```gcc -g -Wall -O -std=11 -o <output-file> <input-file.c>```

- -g -> includere info utili per il debugging
- -Wall -> warning su semantica dinamica
- -O -> ottimizzazione 
- -std=c11 -> versione del linguaggio C utilizzata
- -o -> output
- -g -> sostituisce il flag ```-o``` e si usa per il debug
- input-file -> contiene la funzione main()