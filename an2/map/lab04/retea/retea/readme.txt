MAP - Retea de socializare - Laboratorul 3

CUM PORNESC PROIECTUL IN INTELLIJ IDEA
-------------------------------------
Proiectul este o aplicatie Java simpla si nu are nevoie de Gradle sau de un script separat.
Deschide folderul lab03_social_network in IntelliJ IDEA si seteaza un Project SDK instalat pe calculator.
Clasa de pornire este src/main/java/Main.java. In mod normal, configuratia inclusa marcheaza deja:
- src/main/java ca Sources Root;
- src/main/resources ca Resources Root.

Ruleaza metoda main din clasa Main. Working directory trebuie sa fie folderul proiectului, deoarece
caile din config.properties sunt relative (data/...). Daca IntelliJ nu recunoaste automat configuratia,
seteaza manual Working directory la radacina proiectului.
Codul este compatibil cu Java 8 si nu foloseste lambda, method references sau stream-uri.

CONFIGURARE SI PERSISTENTA
--------------------------
Configuratia se afla in src/main/resources/config.properties. Pentru modul normal de lucru:
    repository.type=FILE

Datele sunt fisiere text UTF-8, fara antet, cu un obiect pe linie si campurile separate prin punct si virgula:
- data/utilizatori.txt: id;prenume;nume
- data/prietenii.txt: idUtilizator1;idUtilizator2;dataPrieteniei

Data prieteniei foloseste formatul ISO, de exemplu 2026-10-19T10:30. Am pastrat valorile din exemplul initial si am mai adaugat cativa utilizatori pentru a se putea testa mai usor reteaua.
ID-urile sunt afisate in liste,
dar cand se adauga sau se sterge o prietenie se introduc numele persoanelor, nu ID-urile.

Daca un fisier nu exista, repository-ul porneste gol. Fisierul se creeaza la prima salvare reusita.
La incarcarea datelor, fiecare linie este parsata si trece prin validator. O linie invalida este raportata
pe stderr cu fisierul, numarul liniei si motivul, apoi este ignorata. Am ales varianta aceasta pentru ca o
singura linie stricata sa nu opreasca toata aplicatia, iar celelalte date valide sa poata fi folosite.
La urmatoarea salvare reusita, fisierul este rescris cu entitatile valide care au fost incarcate.

Pentru a testa liniile corupte, opreste aplicatia si modifica temporar in config.properties proprietatile:
    file.users=test-data/utilizatori-corupt.txt
    file.friendships=test-data/prietenii-corupte.txt
Pastreaza repository.type=FILE si reporneste aplicatia. Dupa test, pune inapoi caile din folderul data/.
Fisierele din test-data/ sunt separate ca sa nu fie nevoie sa strici datele folosite normal.

FACTORY SI TIPURI DE REPOSITORY
-------------------------------
RepositoryFactory este singurul loc care decide ce clase concrete sunt folosite. Ambele repository-uri
sunt create pentru acelasi tip de persistenta, citit din config.properties:
- MEMORY: datele sunt tinute doar in memorie si se pierd la inchidere;
- FILE: datele sunt citite si scrise in fisierele text;
- DATABASE: factory-ul creeaza clasele UtilizatorDbRepository si PrietenieDbRepository.

Repository-urile DATABASE sunt doar schelete pentru laboratorul 4. Metodele lor arunca
UnsupportedOperationException, pentru ca implementarea JDBC nu face parte din laboratorul 3. Pentru a
verifica selectarea tipului, schimba repository.type in DATABASE si reporneste aplicatia; operatiile de
stocare nu vor functiona pana la implementarea de la laboratorul urmator.

Pentru trecerea la baza de date se implementeaza metodele repository-urilor DB si se actualizeaza
parametrii db.url, db.user si db.password. Service-ul, UI-ul si Main folosesc interfetele repository si nu
au nevoie sa stie ce implementare concreta este selectata.

STRUCTURA PROIECTULUI
---------------------
domain.model       - clasele User, Friendship, FriendshipId, Community si Entity.
repository         - interfetele Repository, UserRepository, FriendshipRepository, repository-ul generic
                     InMemoryRepository, enum-ul RepositoryType si RepositoryFactory.
repository.memory  - implementari pentru modul MEMORY.
repository.file    - AbstractFileRepository si conversiile pentru fisierele text.
repository.database- clase schelet pentru laboratorul 4; nu contin cod JDBC.
service            - SocialNetworkService contine operatiile aplicatiei si analiza comunitatilor.
ui                 - ConsoleUI afiseaza meniul si citeste datele introduse.
validation         - validatoarele pentru utilizatori si prietenii.
exception          - exceptii proprii pentru validare, lipsa entitatii si persistenta.

Am pastrat un singur service: SocialNetworkService. Analiza comunitatilor (BFS si calculul diametrului)
este in aceeasi clasa, astfel incat nu mai exista un al doilea service separat.

INTERFATA CU UTILIZATORUL
-------------------------
- Lista utilizatorilor arata numarul din lista, numele complet si ID-ul.
- Lista prieteniilor arata ambele persoane, ID-urile si data prieteniei.
- Pentru adaugarea si stergerea unei prietenii se pot introduce prenumele (de exemplu Antonio si Alexandra)
  sau numele complet. Nu se cer ID-uri.
- Daca acelasi prenume apare la mai multi utilizatori, aplicatia cere numele complet, ca sa nu aleaga gresit.
- Stergerea unui utilizator se face dupa nume si elimina si prieteniile asociate.

PRINCIPII SOLID SI SABLOANE
---------------------------
SRP: ConsoleUI se ocupa de interactiunea cu utilizatorul, SocialNetworkService de operatiile aplicatiei,
repository-urile de persistenta, iar validatorii de regulile datelor.
DIP: service-ul si UI-ul depind de interfetele repository, nu de clasele concrete pentru FILE/MEMORY/DATABASE.
OCP: se pot adauga implementari noi de repository fara schimbari in UI si service. Simple Factory cu switch
este usor de urmarit, dar trebuie modificata cand se adauga un tip nou. O varianta Abstract Factory ar avea
cate o fabrica pentru fiecare familie de repository-uri si ar evita modificarea switch-ului central, dar ar
adauga clase si cod suplimentar.
LSP: implementarea in memorie si cea in fisier respecta contractul interfetelor repository pentru operatiile
implementate. Repository-urile DB sunt intentionat incomplete in laboratorul 3.

Factory: RepositoryFactory selecteaza implementarile dupa repository.type.
Template Method: AbstractFileRepository contine logica comuna de citire, validare si scriere; clasele concrete
implementeaza extractEntity si createEntityAsString.
Strategy: ValidationStrategy este interfata pentru validarea utilizatorilor si a prieteniilor.
Decorator: BufferedReader si BufferedWriter sunt folosite peste fluxurile de caractere create cu NIO.2.

VALIDARE SI CONSISTENTA
-----------------------
Datele citite din fisiere trec prin aceiasi validatori ca datele noi. Prieteniile sunt permise doar intre doi
utilizatori existenti; nu sunt permise prietenii cu sine sau duplicate. FriendshipId normalizeaza perechea,
astfel incat (1, 2) si (2, 1) desemneaza aceeasi prietenie. La stergerea unui utilizator se sterg si prieteniile
lui, ca fisierele sa nu ramana cu referinte catre utilizatori inexistenti.
