/*Cinema (2/12/25)
Scrivere un programma Java che utilizzando i dati del file Mini.tsv (disponbile su moodle)
costruisce una mappa Map<String,Set<String>> ruoli che associa ad ogni persona le professioni 
che esso/essa ha avuto. Il file Mini.tsv ha il seguente formato:

nm0000001   Fred Astaire    1899       1987       actor,miscellaneous,producer        tt0072308,tt0050419,tt0027125,tt0031983
nm0000002   Lauren Bacall   1924       2014       actress,soundtrack,archive_footage  tt0037382,tt0075213,tt0117057,tt0038355
nm0000003   Brigitte Bardot 1934       \N         actress,music_department,producer   tt0057345,tt0049189,tt0056404,tt0054452
nm0000004   John Belushi    1949       1982       actor,writer,music_department       tt0072562,tt0077975,tt0080455,tt0078723
nm0000005   Ingmar Bergman  1918       2007       writer,director,actor               tt0050986,tt0069467,tt0050976,tt0083922
nm0000006   Ingrid Bergman  1915       1982       actress,producer,soundtrack         tt0034583,tt0038109,tt0036855,tt0038787
...
per l'esercizio interessano la seconda colonna contente i nomi, e la quinta colonna contenente le professioni 
separate dal carattere ,. Vedere l'esempio Citta.java per come effettuare la lettura di una riga alla volta. 
In ogni riga del testo le colonne sono separate dal carattere '\t' e quindi possono essere ottenute utilizzando 
il metodo split (vedere il costruttore della classe Citta). Per ottenere le singole professioni applicare il metodo split() 
alla quinta colonna.

Terminata la lettura, scrivere nel file attrici.txt l'elenco delle attrici ordinato alfabeticamente, cioè delle 
persone che hanno actress nell'elenco delle professioni. Per scrivere in un file, aprirlo con

BufferedWriter writer = new BufferedWriter(new FileWriter("attrici.txt")) 
(possibilmente dentro un try) e scrivere le singole linee con writer.write(String).

Seconda parte Durante la lettura del file, costruire anche una mappa che associa ad ogni professione l'insieme 
delle persone con quella professione. Al termine, per ogni professione (ad esempio actor) scrivere un file actor.txt 
contenente l'elenco delle persone con quella professione. Si noti che il file actress.txt dovrebbe avere lo stesso 
contenuto del file attrici.txt della prima parte dell'esercizio.
 */

//cosa deve fare il main?
//aprire il file -> leggere riga per riga -> estrarre nome e professioni-> mappa<nome,professione>->
//terminata la lettura scrive nel file attrici.txt l'elenco delle attrici ordinato alfabeticamnte dentro
//un try -> per ogni professione, scrivere un file che contiene l'elenco delle persone con quella professione
//oggetti da realizzare?
//oggetto map<name, professions>
//costruttore: prende name e professions e le associa ai campi dell'oggetto appena creato
//metodo main: legge un file riga per riga, estrae nome e professione, aggiorna la mappa, poi in un try scrive le linee
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Cinema {

    Map<String, Set<String>> professionPeapleMap;

    public Cinema() {
        this.professionPeapleMap = new HashMap();
    }

    public static void main(String[] args) {
        //verifico se il numero di argomenti è almeno 2 (deve guardare se sulla riga di comando ci sono almeno 2 argomenti)
        if (args.length != 1) {
            System.out.println("Uso: java Cinema nomefile");
            System.exit(1);
        }
        //come leggere la riga di un file:
        try {
            String fileName = args[0];
            BufferedReader br = new BufferedReader(new FileReader(fileName));
            String line;
            Cinema result = new Cinema();

            while ((line = br.readLine()) != null) {
                String[] columns = line.split("\t");
                String name = columns[0];
                String[] professions = columns[4].split(",");
                for (String profession : professions) {
                    Set<String> workersWithThatProfession = result.professionPeapleMap.get(profession);
                    if (workersWithThatProfession == null) {
                        workersWithThatProfession = new HashSet();
                    }
                    workersWithThatProfession.add(name);
                    result.professionPeapleMap.put(profession, workersWithThatProfession);
                }
                System.out.println(result.professionPeapleMap);
            }
            br.close();
        } catch (Exception e) {
            System.err.println("Errore: " + e);
            e.printStackTrace();
            System.exit(2);
        }
    }
}
