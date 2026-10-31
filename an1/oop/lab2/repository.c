#include "repository.h"
#include <stdlib.h>

/*
 * initializeaza o structura de tip repository.
 * pre: -
 * post: returneaza un repository valid cu un vector dinamic de produse gol.
 */
Repository createRepository() {
	Repository repo;
	repo.products = createVector();
	
	return repo;
}

/*
 * elibereaza memoria si resursele ocupate de repository.
 * pre: repo - pointer valid catre un repository existent.
 * post: memoria ocupata de vectorul de produse este eliberata.
 */
void destroyRepository(Repository* repo) {
	destroyVector(&(repo->products));
}

/*
 * adauga un obiect de tip product in repository.
 * pre: repo - pointer valid, product - instanta de tip product valida.
 * post: produsul este stocat in vectorul intern al repository-ului.
 */
void addProductRepo(Repository* repo, Product product) {
	add(&(repo->products), product);
}

/*
 * cauta pozitia in vector a unui produs cu un anumit id.
 * pre: repo - pointer valid, id - numar intreg.
 * post: returneaza indexul produsului sau -1 daca id-ul nu este gasit.
 */
int getIndexOf(Repository* repo, int id) {
	for (int i = 0; i < repo->products.size; i++)
		if (repo->products.elements[i].id == id)
			return i;

	return -1;
}

/*
 * sterge un produs din repository pe baza unui id dat.
 * pre: repo - pointer valid, id - numar intreg pozitiv.
 * post: returneaza 1 daca produsul a fost sters, 0 daca id-ul nu exista.
 */
int deleteProductRepo(Repository* repo, int id) {
	int index = getIndexOf(repo, id);
	
	if (index == -1)
		return -1;

	destroyProduct(&(repo->products.elements[index]));
	
	for (int i = index; i < repo->products.size - 1; i++) {
		repo->products.elements[i] = repo->products.elements[i + 1];
	}

	repo->products.size--;

	return 1;
}

/*
 * actualizeaza datele unui produs existent in repository.
 * pre: repo - pointer valid, id - identificatorul produsului, product - datele noi.
 * post: returneaza 1 daca actualizarea a reusit, 0 daca produsul nu a fost gasit.
 */
int updateProductRepo(Repository* repo, int id, Product product) {
	int index = getIndexOf(repo, id);

	if (index == -1)
		return -1;

	destroyProduct(&(repo->products.elements[index]));
	repo->products.elements[index] = product;
	
	return 1;
}

/*
 * returneaza un pointer catre produsul aflat la o anumita pozitie.
 * pre: repo - pointer valid, idx - index valid in interiorul vectorului.
 * post: returneaza adresa produsului de la indexul specificat.
 */
Product* getProductAt(Repository* repo, int idx) {
	if (idx < 0 || idx >= repo->products.size)
		return NULL;
	return &(repo->products.elements[idx]);
}

Vector* getAllProductsRepo(Repository* repo) {
	return &repo->products;
}