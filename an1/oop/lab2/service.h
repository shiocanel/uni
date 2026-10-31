#ifndef SERVICE_H
#define SERVICE_H

#include "repository.h"

typedef struct {
	Repository repo;
} Service;

/*
 * initializeaza structura de service si repository-ul aferent.
 * pre: -
 * post: returneaza o instanta de service gata pentru procesarea datelor.
 */
Service createService();

/*
 * elibereaza resursele pentru service si repository.
 * pre: service - pointer valid catre un service.
 * post: memoria este eliberata complet si resursele sunt distruse.
 */
void destroyService(Service* service);

/*
 * valideaza datele si adauga un produs nou in sistem prin intermediul repository-ului.
 * pre: service - pointer valid, id > 0, price > 0, quantity > 0, siruri de caractere valide.
 * post: returneaza 1 daca produsul a fost adaugat, 0 daca id-ul exista deja sau datele sunt invalide.
 */
int addProduct(Service* service, int id, char* name, char* model, char* producer, double price, int quantity);

/*
 * sterge un produs existent din sistem pe baza id-ului.
 * pre: service - pointer valid, id - numar intreg.
 * post: returneaza 1 daca stergerea a reusit, 0 daca produsul nu a fost gasit.
 */
int deleteProduct(Service* service, int id);

/*
 * actualizeaza datele unui produs existent identificat prin id.
 * pre: service - pointer valid, id existent, date noi valide (pret, cantitate > 0).
 * post: returneaza 1 daca actualizarea a reusit, 0 in caz contrar.
 */
int updateProduct(Service* service, int id, char* name, char* model, char* producer, double price, int quantity);

/*
 * returneaza lista completa de produse din repository.
 * pre: service - pointer valid.
 * post: returneaza un pointer catre vectorul ce contine toate produsele curente.
 */
Vector* getAllProducts(Service* service);

/*
 * sorteaza produsele din sistem in functie de pret.
 * pre: service - pointer valid, ascending - 1 pentru crescator, 0 pentru descrescator.
 * post: returneaza un vector nou cu produsele ordonate dupa pret.
 */
Vector sortByPrice(Service* service, int ascending);

/*
 * sorteaza produsele din sistem in functie de cantitatea disponibila.
 * pre: service - pointer valid, ascending - 1 pentru crescator, 0 pentru descrescator.
 * post: returneaza un vector nou cu produsele ordonate dupa cantitate.
 */
Vector sortByQuantity(Service* service, int ascending);

/*
 * filtreaza produsele care apartin unui anumit producator.
 * pre: service - pointer valid, producer - sir de caractere valid (nu null).
 * post: returneaza un vector ce contine doar produsele de la producatorul dat.
 */
Vector filterByProducer(Service* service, char* producer);

/*
 * filtreaza produsele care au un pret specificat.
 * pre: service - pointer valid, price - numar real pozitiv.
 * post: returneaza un vector cu produsele care au pretul egal cu cel dat.
 */
Vector filterByPrice(Service* service, double price);

/*
 * filtreaza produsele in functie de o cantitate specifica.
 * pre: service - pointer valid, quantity - numar intreg pozitiv.
 * post: returneaza un vector cu produsele care au cantitatea respectiva.
 */
Vector filterByQuantity(Service* service, int quantity);


#endif // !SERVICE_H
