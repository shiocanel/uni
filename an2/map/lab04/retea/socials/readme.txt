RETEA DE SOCIALIZARE

DESCRIERE

Acesta este un proiect Java pentru administrarea unei retele de socializare. Aplicatia ruleaza in consola si permite gestionarea utilizatorilor si a relatiilor de prietenie dintre acestia. Pe baza prieteniilor sunt calculate comunitatile din retea si este identificata cea mai sociabila comunitate.

FUNCTIONALITATI

1. Afisarea tuturor utilizatorilor.
2. Adaugarea unui utilizator cu prenume, nume, email, data nasterii si descriere. Datele de profil suplimentare sunt optionale.
3. Stergerea unui utilizator impreuna cu toate prieteniile asociate acestuia.
4. Adaugarea unei prietenii intre doi utilizatori existenti.
5. Stergerea unei prietenii.
6. Afisarea tuturor prieteniilor.
7. Calcularea numarului de comunitati.
8. Afisarea tuturor comunitatilor.
9. Afisarea celei mai sociabile comunitati.

Utilizatorii pot fi cautati dupa prenume, nume sau numele complet. Cautarea nu tine cont de litere mari si mici. Daca numele introdus corespunde mai multor utilizatori, aplicatia solicita folosirea unui nume mai precis.

ORGANIZAREA PROIECTULUI

Proiectul este impartit in mai multe pachete, fiecare avand un rol separat.

1. domain.model contine clasele User, Friendship, FriendshipId, Community si Entity. Aceste clase reprezinta datele folosite in aplicatie.
2. validation contine regulile de validare pentru utilizatori si prietenii.
3. repository contine interfetele si implementarea generica pentru accesul la date.
4. repository.memory contine repository-urile care pastreaza datele in memorie.
5. repository.file contine repository-urile care citesc si scriu date in fisiere.
6. repository.database contine clasele pregatite pentru varianta cu baza de date. Implementarea JDBC urmeaza sa fie facuta intr-un laborator ulterior.
7. service contine logica aplicatiei, operatiile pentru utilizatori si prietenii, precum si calculul comunitatilor.
8. ui contine meniul si interactiunea cu utilizatorul prin consola.
9. exception contine exceptiile folosite pentru erorile aplicatiei.

Main este punctul de pornire al aplicatiei. Aici sunt incarcate configurarile, create repository-urile si pornita interfata din consola.

STOCAREA DATELOR

Tipul de stocare este ales din fisierul config.properties prin proprietatea repository.type. Sunt prevazute trei variante:

1. MEMORY pastreaza datele doar in memorie. Datele se pierd la inchiderea aplicatiei.
2. FILE citeste si salveaza datele in fisiere text. Pentru aceasta varianta sunt folosite proprietatile file.users si file.friendships.
3. DATABASE este pregatita ca structura, dar operatiile JDBC nu sunt implementate in acest laborator. Clasele repository.database arunca UnsupportedOperationException, deoarece partea de baza de date este rezervata laboratorului urmator. Pentru configurare sunt prevazute proprietatile db.url, db.user si db.password.

FORMATUL FISIERELOR

Fisierul utilizatorilor accepta linii cu 3 campuri sau cu 6 campuri, separate prin punct si virgula. Formatul cu 3 campuri este id, prenume si nume. Formatul cu 6 campuri este id, prenume, nume, email, data nasterii si descriere. La salvare, utilizatorii sunt scrisi cu toate cele 6 campuri.

Fisierul prieteniilor foloseste 3 campuri: primul ID de utilizator, al doilea ID de utilizator si data prieteniei. Data este salvata in formatul an-luna-zi, urmata de ora si minut.

Daca un fisier nu exista, repository-ul il trateaza ca fiind gol. Liniile invalide sunt ignorate si sunt raportate in consola impreuna cu numarul liniei si motivul erorii.

VALIDARI

Pentru utilizatori se verifica ID-ul pozitiv, prenumele si numele obligatorii, lungimea numelor, adresa de email, formatul datei de nastere si continutul descrierii. Data nasterii este verificata si printr-o regula suplimentara adaugata cu lambda in Main. Aceasta regula verifica daca data este reala si nu este in viitor.

Pentru prietenii se verifica daca cei doi utilizatori exista si daca nu se incearca adaugarea unei prietenii intre un utilizator si el insusi. Aplicatia nu permite adaugarea aceleiasi prietenii de doua ori.

CERINTE JAVA FOLOSITE

Proiectul foloseste functionalitati din Java 8.

1. ValidationStrategy este o interfata functionala si are metoda default andThen pentru combinarea validatorilor.
2. Repository are metoda findAll cu Predicate, care permite filtrarea entitatilor.
3. UserCriteria contine criterii de cautare pentru utilizatori. Criteriile pot fi combinate cu and, or si negate.
4. RepositoryFactory foloseste doua map-uri cu Function pentru crearea repository-urilor de utilizatori si de prietenii, fara switch pentru alegerea tipului de stocare.
5. AbstractFileRepository pastreaza logica comuna de citire si scriere. Clasele UserFileRepository si FriendshipFileRepository implementeaza conversia dintre linii si obiecte. Este folosit sablonul Template Method.
6. Operatiile pe colectii folosesc Stream API, de exemplu filter, map, flatMap, distinct, sorted, count, max, anyMatch, allMatch, noneMatch si collect.
7. Pentru construirea colectiilor sunt folositi colectori precum toList, toSet, groupingBy, counting si joining.
8. Pentru sortare sunt folositi Comparator.comparing si thenComparing.
9. In proiect sunt folosite lambda-uri si referinte la metode, inclusiv referinte la metode statice, metode ale unor instante, metode ale unor instante de tip arbitrar si constructori.
10. Optional este folosit pentru rezultatele care pot lipsi, de exemplu la cautarea dupa ID si la gasirea celei mai sociabile comunitati.
11. Pentru fisiere sunt folosite Files.lines si Files.write. Citirea foloseste try-with-resources pentru inchiderea stream-ului.

CALCULAREA COMUNITATILOR

Reteaua este tratata ca un graf neorientat. Fiecare utilizator reprezinta un nod, iar fiecare prietenie reprezinta o muchie. Metoda getCommunities foloseste structura Union-Find pentru gruparea utilizatorilor in componente conexe. Sunt incluse si comunitatile formate dintr-un singur utilizator, chiar daca acesta nu are prieteni.

Diametrul unei comunitati este cea mai mare distanta minima dintre doi membri ai acesteia. Pentru calcularea distantelor este folosita parcurgerea BFS. Cea mai sociabila comunitate este aleasa in functie de diametru, apoi de numarul de membri. In caz de egalitate se pastreaza comunitatea cu cel mai mic ID minim.

RULAREA APLICATIEI

Proiectul poate fi deschis in IntelliJ IDEA ca proiect Java. Este necesar un JDK compatibil cu Java 8. Fisierul config.properties trebuie sa fie in src/main/resources si sa contina cel putin proprietatea repository.type, impreuna cu proprietatile necesare tipului de stocare ales.

Pentru pornire se ruleaza clasa Main. Dupa pornire apare meniul din consola, iar operatiile se aleg prin introducerea numarului corespunzator.

Proiectul foloseste doar biblioteca standard Java si nu necesita biblioteci externe.
