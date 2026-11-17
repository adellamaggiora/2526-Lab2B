Dopo devi stabilire che tipo di vincolo di concorrenza esiste:

mutua esclusione: una sola thread alla volta può accedere a una risorsa condivisa.
Primitive tipiche: pthread_mutex_t.

coordinamento/ordine: una thread deve aspettare che un’altra produca un evento o renda disponibile un dato.
Primitive tipiche: semafori, condition variable.

conteggio di risorse disponibili: al massimo N thread possono entrare in una certa zona.
Primitive tipiche: semafori inizializzati a N.

attesa della terminazione: il main deve aspettare che le thread finiscano.
Primitive tipiche: pthread_join.

Quindi il criterio non è “ho una sezione critica, metto una primitiva”, ma:

identifico le variabili condivise;

capisco quali accessi possono interlecciarsi in modo scorretto;

definisco l’invariante da proteggere;

scelgo la primitiva minima che garantisce quell’invariante;

colloco lock/unlock o wait/post nel punto più stretto possibile.

Esempio: se più thread incrementano un contatore globale di primi trovati, la sezione critica è solo l’incremento: