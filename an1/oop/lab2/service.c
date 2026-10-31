#include "service.h"
#include "validator.h"

/*
 * initializeaza structura de service si repository-ul aferent.
 * pre: -
 * post: returneaza o instanta de service gata pentru procesarea datelor.
 */
Service createService() {
	Service service;
	service.repo = createRepository();
	return service;
}

/*
 * elibereaza resursele pentru service si repository.
 * pre: service - pointer valid catre un service.
 * post: memoria este eliberata complet si resursele sunt distruse.
 */
void destroyService(Service* service) {
	destroyRepository(&(service->repo));
}

/*
 * valideaza datele si adauga un produs nou in sistem prin intermediul repository-ului.
 * pre: service - pointer valid, id > 0, price > 0, quantity > 0, siruri de caractere valide.
 * post: returneaza 1 daca produsul a fost adaugat, 0 daca id-ul exista deja sau datele sunt invalide.
 */
int addProduct(Service* service, int id, char* name, char* model, char* producer, double price, int quantity) {
	if (validateProduct(id, name, model, producer, price, quantity) == -1)
		return -1;

	if (getIndexOf(&(service->repo), id) != -1)
		return -1;

	Product product = createProduct(id, name, model, producer, price, quantity);
	addProductRepo(&(service->repo), product);

	return 1;
}

/*
 * sterge un produs existent din sistem pe baza id-ului.
 * pre: service - pointer valid, id - numar intreg.
 * post: returneaza 1 daca stergerea a reusit, 0 daca produsul nu a fost gasit.
 */
int deleteProduct(Service* service, int id) {
	return deleteProductRepo(&(service->repo), id);
}

/*
 * actualizeaza datele unui produs existent identificat prin id.
 * pre: service - pointer valid, id existent, date noi valide (pret, cantitate > 0).
 * post: returneaza 1 daca actualizarea a reusit, 0 in caz contrar.
 */
int updateProduct(Service* service, int id, char* name, char* model, char* producer, double price, int quantity) {
	if (validateProduct(id, name, model, producer, price, quantity) == -1)
		return -1;
	
	Product product = createProduct(id, name, model, producer, price, quantity);
	return updateProductRepo(&(service->repo), id, product);
}

/*
 * returneaza lista completa de produse din repository.
 * pre: service - pointer valid.
 * post: returneaza un pointer catre vectorul ce contine toate produsele curente.
 */
Vector* getAllProducts(Service* service) {
	return getAllProductsRepo(&(service->repo));
}

Vector copyVector(Vector* v) {
	Vector result = createVector();

	for (int i = 0; i < v->size; i++) {
		Product p = v->elements[i];
		Product copy = createProduct(p.id, p.name, p.model, p.producer, p.price, p.quantity);

		add(&result, copy);
	}

	return result;
}

typedef int (*CompareFunction)(Product a, Product b);

int cmpPriceAsc(Product a, Product b) {
	return (a.price > b.price);
}

int cmpPriceDesc(Product a, Product b) {
	return (a.price < b.price);
}

int cmpQuantityAsc(Product a, Product b) {
	return (a.quantity > b.quantity);
}

int cmpQuantityDesc(Product a, Product b) {
	return (a.quantity < b.quantity);
}

void sort(Vector* v, CompareFunction cmpF) {
	for (int i = 0; i < v->size - 1; i++) {
		for (int j = i + 1; j < v->size; j++) {
			if (cmpF(v->elements[i], v->elements[j]) > 0) {
				Product aux = v->elements[i];
				v->elements[i] = v->elements[j];
				v->elements[j] = aux;
			}
		}
	}
}

/*
 * sorteaza produsele din sistem in functie de pret.
 * pre: service - pointer valid, ascending - 1 pentru crescator, 0 pentru descrescator.
 * post: returneaza un vector nou cu produsele ordonate dupa pret.
 */
Vector sortByPrice(Service* service, int ascending) {
	Vector v = copyVector(getAllProducts(service));

	if (ascending)
		sort(&v, cmpPriceAsc);
	else
		sort(&v, cmpPriceDesc);

	return v;
}

/*
 * sorteaza produsele din sistem in functie de cantitatea disponibila.
 * pre: service - pointer valid, ascending - 1 pentru crescator, 0 pentru descrescator.
 * post: returneaza un vector nou cu produsele ordonate dupa cantitate.
 */
Vector sortByQuantity(Service* service, int ascending) {
	Vector v = copyVector(getAllProducts(service));

	if (ascending)
		sort(&v, cmpQuantityAsc);
	else
		sort(&v, cmpQuantityDesc);

	return v;
}

/*
 * filtreaza produsele care apartin unui anumit producator.
 * pre: service - pointer valid, producer - sir de caractere valid (nu null).
 * post: returneaza un vector ce contine doar produsele de la producatorul dat.
 */
Vector filterByProducer(Service* service, char* producer) {
	Vector result = createVector();
	Vector* all = getAllProducts(service);

	for (int i = 0; i < all->size; i++) {
		if (strcmp(all->elements[i].producer, producer) == 0) {
			Product p = all->elements[i];
			Product copy = createProduct(p.id, p.name, p.model, p.producer, p.price, p.quantity);

			add(&result, copy);
		}
	}

	return result;
}

/*
 * filtreaza produsele care au un pret specificat.
 * pre: service - pointer valid, price - numar real pozitiv.
 * post: returneaza un vector cu produsele care au pretul egal cu cel dat.
 */
Vector filterByPrice(Service* service, double price) {
	Vector result = createVector();
	Vector* all = getAllProducts(service);

	for (int i = 0; i < all->size; i++) {
		if (all->elements[i].price <= price) {
			Product p = all->elements[i];
			Product copy = createProduct(p.id, p.name, p.model, p.producer, p.price, p.quantity);

			add(&result, copy);
		}
	}

	return result;
}

/*
 * filtreaza produsele in functie de o cantitate specifica.
 * pre: service - pointer valid, quantity - numar intreg pozitiv.
 * post: returneaza un vector cu produsele care au cantitatea respectiva.
 */
Vector filterByQuantity(Service* service, int quantity) {
	Vector result = createVector();
	Vector* all = getAllProducts(service);

	for (int i = 0; i < all->size; i++) {
		if (all->elements[i].quantity <= quantity) {
			Product p = all->elements[i];
			Product copy = createProduct(p.id, p.name, p.model, p.producer, p.price, p.quantity);

			add(&result, copy);
		}
	}

	return result;
}
