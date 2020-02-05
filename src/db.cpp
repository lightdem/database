/*****************************************************************************
 *
 *  Linux Pro Staff
 *
 *  NOMEFILE:
 *      db.cpp
 *
 *  DESCRIZIONE:
 *      Un programma tutorial per esercitarsi con SQL usando la classe Database
 *
 *  COMPILATORE:
 *      g++ 9.1.1
 *
 *
 *****************************************************************************/


#include <stdlib.h>             // definisce EXIT_SUCCESS e EXIT_FAILURE
#include "Database.h"           // inclapsula la connessione al database
#include "Place.h"              // utility per mostrare i risultati
#include "Language.h"           // utility per mostrare i risultati
#include "Terminal.h"           // utility per scrivere su schermo 
#include "StrStrmBuf.h"         // utile per la manipolazione dei testi

int main(int argc, char *argv[])
{
  Terminal::resetAndClearScreen();
  try
  {
    // Quando pDB esce dallo scope l'oggetto Database al quale punta
    // viene cancellato automaticamente
    std::unique_ptr <Database> pDB(new Database("utente", "password"));

    Terminal::displayLabel("Un'introduzione gentile a SQL");
    Terminal::displayCaption("\n\nBenvenuti in questo breve tutorial SQL.\n"
							 "Qui incontrerete diverse interrogazioni SQL"
							 " e istruzioni, che utilizzano il database"
							 " di esempio world.\nIl database world è soltanto "
							 "un parametro di default utilizzato dal programma."
							 " Potete sostituire\nil database, così come qualunque"
							 " comando o query vogliate. Potete anche creare e "
							 "utilizzare il vostro database personale.\nIl programma "
							 "modificherà anche il suo processo a seconda dei "
							 "risultati delle query SQL.\n\n"
							 "Durante questo tutorial, potete rivedere"
							 " le schermate precedenti utilizzando il mouse,\n"
							 "basterà far scorrere la console verso l'alto."
							 "\nImpostate la console in modo che utilizzi uno sfondo"
							 " nero e premete F11 per impostarla a tutto schermo.\n\n"
							 "Mettetevi comodi, rilassatevi e buon divertimento!");
    Terminal::waitForUserInput();

    //******************************* Schermata 1 ******************************
    Terminal::displayCaption("In questa schermata possiamo vedere quattro colonne "
							  "ottenute con un INNER JOIN tra la tabella country "
							  "e la tabella city.\nDa notare le varie condizioni "
							  "nella clausola WHERE. Stiamo chiedendo di vedere "
							  "quattro colonne\nspecifiche da due differenti tabelle "
							  "combinando le righe di entrambe le tabelle\nche" 
							  " soddisfano ogni parte della clausola WHERE."
							  "\n\n"
							  "La tabella country non ha una colonna nella quale "
							  "trovare il nome della città capitale. Infatti,\n"
							  "la colonna capital ospita il numero identificativo "
							  "(ID) della capitale. Per questo dobbiamo collegare\n"
							  "la tabella country con la tabella city per poter "
							  "leggere il nome della capitale.\n"
							  "La colonna ID è la chiave primaria della tabella city.\n\n\n");

    string sSelectStmt = "SELECT country.name, city.name, "
                         "country.HeadOfState, country.Population\n"
                         "FROM country INNER JOIN city\n"
                         "WHERE country.Continent = 'North America' "
                         "AND country.capital = city.ID AND "
                         "country.Population >= 1000000\n"
                         "ORDER BY country.name";

	sql::ResultSet *pRS = pDB->executeQuery(sSelectStmt);
	Terminal::displayLabel("Continente", "America del Nord");
    Place::display(pRS);
    pDB->deleteResultSet();
    Terminal::displayCaption("\n\nNB: Potete modificare la query SQL "
                             "che vedete qui sopra utilizzando la notazione"
							 "\n\"SELECT ... FROM country, city WHERE ...\""
							 "e il risultato sarebbe lo stesso.\n\n"
							 "Come mai abbiamo ottenuto così pochi risultati?\n"
							 "Perché stiamo cercando soltanto i paesi con "
							 "popolazione maggiore di 1 milione.");
    Terminal::waitForUserInput();

    //******************************* Schermata 2 ******************************
    Terminal::displayCaption("Ora stiamo chiedendo al database se la "
                             "tabella country\n contiene almeno una riga "
							 "nella quale la colonna HeadOfState sia uguale "
							 "a George W. Bush.\n\nDa notare l'uso "
							 "del carattere jolly '%'. Esso corrisponde a "
							 "un qualsiasi numero di caratteri.\n La wildcard "
							 "'_' corrisponde a un carattere qualunque.\n"
							 "Quando si utilizzano dei caratteri jolly bisogna "
							 "utilizzare 'LIKE' al posto di '='.\n\n\n");

    string sTestHeadOfState = "SELECT COUNT(HeadOfState) FROM country\nWHERE "
                              "HeadOfState LIKE 'George%Bush'";
    long nCount = pDB->executeCountQuery(sTestHeadOfState);
    if (nCount) // ramo condizionale in base ai risultati dell'ultima query di COUNT
    {
      utility::StrStrmBuf ssb("\n\n\nSecondo il database, "
                              "George Bush è il capo di stato di ");
      ssb << nCount << " paesi.\nQuesto database non è molto aggiornato, "
                       "per non rimanere ancorati al passato.\nAndremo ora "
					   "a eseguire un'istruzione di update.\n\n\n";
      Terminal::displayCaption(ssb);
      // esegue un'istruzione di UPDATE
      string sStmt = "UPDATE country "
                     "SET HeadOfState = 'Donald Trump'\n"
                     "WHERE HeadOfState LIKE 'George%Bush'";
      pDB->execute(sStmt);
    }
    else
    {
      Terminal::displayCaption("\n\n\nNessun record trovato. "
                               "Donald Trump deve essere il presidente "
                               "degli Stati Uniti.\n"
                               "Ripristiniamo ora il contenuto originale "
                               "del database.\nPer farlo bisogna usare "
                               "un'altra istruzione di UPDATE e riportare "
                               "il campo HeadOfState al valore originale.\n\n");
      // esegue un'istruzione di UPDATE
      string sStmt = "UPDATE country "
                     "SET HeadOfState = 'George W. Bush'\n"
                     "WHERE HeadOfState = 'Donald Trump'";
      pDB->execute(sStmt);
    }
    Terminal::waitForUserInput();

    //******************************* Schermata 3 ******************************
    Terminal::displayCaption("Ora viene eseguita la stessa query dell'ultima volta\n"
                             "ma il contenuto del database è cambiato.\n\n"
                             "Utilizzeremo la classe Place per mostrare i risultati."
							 "\n\n\n");
    // rieseguiamo l'istruzione di SELECT usata prima
    pRS = pDB->executeQuery(sSelectStmt);
    Terminal::displayLabel("Continente", "America del nord");
    Place::display(pRS);
    pDB->deleteResultSet();
    Terminal::waitForUserInput();

    //******************************* Schermata 4 ******************************
    Terminal::displayCaption("Un altro paio di query di count.\n"
                             "Le query di count ritornano un ResultSet "
                             "che contiene un singolo elemento.\n"
                             "L'elemento contiene un numero intero "
                             "che indica il numero\ndi righe trovate.\n\n\n");
    // eseguiamo una SELECT COUNT
    string sCountQuery = "SELECT COUNT(HeadOfState) FROM country";
    pDB->executeCountQuery(sCountQuery);

    Terminal::displayNewLines(3);
    // eseguiamo una SELECT COUNT
    sCountQuery = "SELECT COUNT(DISTINCT HeadOfState) FROM country";
    pDB->executeCountQuery(sCountQuery);

    Terminal::displayCaption("\n\nDa notare che il numero di capiti di stato ottenuto "
							 "utilizzando il DISTINCT (che ritorna soltanto "
							 "i dati univoci)\nè inferiore al conteggio normale.\n"
							 "Questo perché alcuni capi di stato sono a capo di più\n"
							 "nazioni. Il DISTINCT rimuove i duplicati.\n\n");
    sCountQuery = "SELECT COUNT(HeadOfState) FROM country\n"
                  "WHERE HeadOfState = 'Elisabeth II'";
    pDB->executeCountQuery(sCountQuery);

    Terminal::waitForUserInput();

    //******************************* Schermata 5 ******************************
    Terminal::displayCaption("Possiamo anche aggiungere o rimuovere elementi da un "
	                         "database.\nPossiamo eseguire un'istruzione di INSERT "
							 "con diverse righe.\nOppure ottenere lo stesso risultato "
							 "eseguendo diverse istruzioni di INSERT.\n\n"
							 "La tabella city ha una colonna ID, ma non la impostiamo "
							 "nell'istruzione di INSERT.\nQuesto perché questa colonna "
							 "è la chiave primaria. Essa è impostata come\n auto-increment "
							 "quindi il suo valore viene generato automaticamente.\n\n");

    // eseguiamo l'istruzione di INSERT con diverse righe
    string sStmt = "INSERT INTO city (name, countrycode, district, population) "
                   "VALUES\n"
                   "('Columbia',      'USA', 'Maryland', 100000),\n"
                   "('Ellicott City', 'USA', 'Maryland',  85000)";

    pDB->execute(sStmt);

    Terminal::displayCaption("\n\nOra eseguiamo un'istruzione SELECT per vedere \n"
                             "le righe che abbiamo inserito nella tabella city.\n\n");

    // eseguiamo un'istruzione SELECT per vedere le righe appena inserite
    sStmt = "SELECT name, district, countrycode, population FROM city\n"
            "WHERE district = 'Maryland'";
    pRS = pDB->executeQuery(sStmt);
    Terminal::displayLabel("USA", "Città nel Maryland");
    Place::display(pRS);
    pDB->deleteResultSet();
    Terminal::displayCaption("\n\nEseguiamo un'istruzione DELETE per rimuovere\n"
                             "le righe che abbiamo appena inserito nella tabella "
							 "city.\nDobbiamo assicurarci di essere abbastanza "
							 "chiari per evitare di cancellare il record Columbia "
							 "che appartiene al distretto di North Caroline\n"
							 "se presente nel database. Per questo dobbiamo "
							 "aggiungere anche district = 'Marylan' nella clausola "
							 "where.\n\n");

    // eseguiamo un'istruzione di DELETE per invertire l'inserimento fatto prima
    sStmt = "DELETE FROM city WHERE district = 'Maryland' AND\n"
            "(name = 'Columbia' OR name = 'Ellicott City')";
    pDB->execute(sStmt);

    // eseguiamo un'istruzione di select per verificare la corretta rimozione
    Terminal::displayCaption("\n\nUn'altra istruzione di select in modo "
                             "da verificare di aver \n cancellato le "
                             "righe dalla tabella city.\n\n");
    sStmt = "SELECT name, district, countrycode, population FROM city\n"
            "WHERE district = 'Maryland'";
    pRS = pDB->executeQuery(sStmt);
    Terminal::displayLabel("USA", "Città nel Maryland");
    Place::display(pRS);
    pDB->deleteResultSet();
    Terminal::displayCaption("\n\nAbbiamo cancellato le righe aggiunte "
							  "prima e la tabella city è tornata allo "
							  "stato originale.\n");
    Terminal::waitForUserInput();
    
    //******************************* Schermata 6 ******************************
    Terminal::displayCaption("Un'altra istruzione di select con quattro colonne.\n"
							  "Da notare le diverse condizioni nella clausola Where "
							  "notate anche l'uso delle\nparentesi. La query si "
							  "comporterebbe in modo molto diverso senza le parentesi!\n\n\n");

    sStmt       = "SELECT country.name, city.name, "
                  "country.HeadOfState, country.Population\n"
                  "FROM country, city\n"
                  "WHERE country.Continent = 'Europe' "
                  "AND country.capital = city.id "
                  "AND (country.name < 'D' OR country.name > 'T')"
                  "\nORDER BY country.name DESC";
    pRS = pDB->executeQuery(sStmt);
    Terminal::displayLabel("Continente", "Europa");
    Place::display(pRS);
    Terminal::waitForUserInput();

    //******************************* Schermata 7 ******************************
    Terminal::displayCaption("Utilizziamo ora la tabella countrylanguage per scoprire "
							  "la percentuale di abitanti per nazione che parla inglese."
							  "\nQuesta query SQL produce un nome e un numero double. "
							  "La classe Language viene utlizzata\n"
							  "per mostrare il risultato della query.\n\n\n");

    sStmt =  "SELECT name, percentage FROM country, countrylanguage WHERE\n"
             "country.code=countrylanguage.countrycode "
             "AND language='English' AND percentage >= 1.0\n"
             "ORDER BY percentage DESC";

    pRS = pDB->executeQuery(sStmt);
    Terminal::displayLabel("Percentuale di persone che parlano inglese per nazione");
    Language::display(pRS);
    Terminal::displayCaption("\n\nOra conoscete abbastanza su SQL. "
                            "Modificate le istruzioni\n"
                            "SQL di questo tutorial.\n"
							"Sperimentate e divertitevi!\n\n\n");
  }
  catch(const sql::SQLException &e)
  {
    std::cerr << "SQL EXCEPTION:\n";
    std::cerr << "code:  " << e.getErrorCode() << std::endl;
    std::cerr << "state: " << e.getSQLState() << std::endl;
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch (const std::exception &e)
  {
    std::cerr << "EXCEPTION:\n";
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}