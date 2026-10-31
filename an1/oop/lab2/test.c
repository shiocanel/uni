#include "test.h"

/*
 * verifica daca crearea si distrugerea unui obiect de tip product functioneaza corect.
 * pre: -
 * post: testul trece daca toate atributele sunt setate corect, altfel se opreste in assert.
 */
void testProduct() {
	Product p = createProduct(1, "Laptop", "XPS", "Dell", 5000, 3);

	assert(p.id == 1);
	assert(strcmp(p.name, "Laptop") == 0);
	assert(strcmp(p.model, "XPS") == 0);
	assert(strcmp(p.producer, "Dell") == 0);
	assert(p.price == 5000);
	assert(p.quantity == 3);

	destroyProduct(&p);
	destroyProduct(NULL);
}

/*
 * verifica functionalitatile de baza ale vectorului dinamic (creare, adaugare, distrugere).
 * pre: -
 * post: testul confirma daca dimensiunea si elementele sunt gestionate corect in memorie.
 */
void testVector() {
	Vector v = createVector();

	Product p1 = createProduct(1, "A", "A", "A", 10, 1);
	Product p2 = createProduct(2, "B", "B", "B", 20, 2);

	add(&v, p1);
	add(&v, p2);

	assert(v.size == 2);

	assert(v.elements[0].id == 1);
	assert(v.elements[1].id == 2);

	destroyVector(&v);
}

/*
 * testeaza operatiile de stocare, cautare, actualizare si stergere din repository.
 * pre: -
 * post: se asigura ca schimbarile asupra datelor sunt persistente in vectorul intern.
 */
void testRepository() {
	Repository repo = createRepository();

	Product p1 = createProduct(1, "A", "A", "A", 10, 1);
	Product p2 = createProduct(2, "B", "B", "B", 20, 2);

	addProductRepo(&repo, p1);
	addProductRepo(&repo, p2);

	assert(getIndexOf(&repo, 1) == 0);
	assert(getIndexOf(&repo, 2) == 1);
	assert(getIndexOf(&repo, 3) == -1);

	Product newP = createProduct(1, "X", "X", "X", 100, 5);
	assert(updateProductRepo(&repo, 1, newP) == 1);
	assert(updateProductRepo(&repo, 20, newP) == -1);

	Product* p = getProductAt(&repo, 0);
	assert(strcmp(p->name, "X") == 0);

	assert(getProductAt(&repo, 20) == NULL);

	assert(deleteProductRepo(&repo, 1) == 1);
	assert(deleteProductRepo(&repo, 10) == -1);
	assert(getIndexOf(&repo, 1) == -1);


	destroyRepository(&repo);
}

/*
 * verifica logica de business pentru operatiile de tip creare, citire, actualizare si stergere.
 * pre: -
 * post: confirma integrarea corecta intre service si repository, inclusiv validarea unicitatii.
 */
void testServiceCRUD() {
	Service s = createService();

	assert(addProduct(&s, 1, "A", "A", "A", 10, 1) == 1);
	assert(addProduct(&s, 1, "A", "A", "A", 10, 1) == -1);
	assert(addProduct(&s, 1, "", "", "", 10, 1) == -1);

	Vector* v = getAllProducts(&s);
	assert(v->size == 1);
	assert(updateProduct(&s, 1, "B", "B", "B", 20, 2) == 1);
	assert(updateProduct(&s, -1, "B", "B", "B", 20, 2) == -1);
	assert(strcmp(v->elements[0].name, "B") == 0);
	assert(deleteProduct(&s, 1) == 1);
	assert(v->size == 0);

	destroyService(&s);
}

/*
 * testeaza toate cazurile de eroare si de succes pentru datele de intrare ale unui produs.
 * pre: -
 * post: se asigura ca datele invalide sunt respinse si cele valide sunt acceptate.
 */
void testValidator() {
	assert(validateProduct(10, "A", "A", "A", (double)10, 1) == 1);
	assert(validateProduct(-1, "A", "A", "A", (double)10, 1) == -1);
	assert(validateProduct(1, "", "A", "A", (double)10, 1) == -1);
	assert(validateProduct(1, "A", "", "A", (double)10, 1) == -1);
	assert(validateProduct(1, "A", "A", "", (double)10, 1) == -1);
	assert(validateProduct(1, "A", "A", "A", (double)-10, 1) == -1);
	assert(validateProduct(1, "A", "A", "A", (double)10, -1) == -1);
}

/*
 * verifica corectitudinea algoritmilor de sortare dupa pret si cantitate.
 * pre: -
 * post: confirma ordinea elementelor atat in mod crescator, cat si descrescator.
 */
void testSort() {
	Service s = createService();

	addProduct(&s, 1, "A", "A", "A", 30, 5);
	addProduct(&s, 2, "B", "B", "B", 10, 2);
	addProduct(&s, 3, "C", "C", "C", 20, 8);

	Vector v = sortByPrice(&s, 1);
	assert(v.elements[0].price == 10);
	assert(v.elements[1].price == 20);
	assert(v.elements[2].price == 30);
	destroyVector(&v);

	v = sortByPrice(&s, 0);
	assert(v.elements[0].price == 30);
	assert(v.elements[2].price == 10);
	destroyVector(&v);

	v = sortByQuantity(&s, 1);
	assert(v.elements[0].quantity == 2);
	destroyVector(&v);

	v = sortByQuantity(&s, 0);
	assert(v.elements[0].quantity == 8);
	destroyVector(&v);

	destroyService(&s);
}

/*
 * verifica functionalitatea de filtrare dupa producator, pret si cantitate.
 * pre: -
 * post: confirma ca vectorul rezultat contine doar elementele care indeplinesc criteriul.
 */
void testFilter() {
	Service s = createService();

	addProduct(&s, 1, "A", "A", "Dell", 100, 5);
	addProduct(&s, 2, "B", "B", "HP", 200, 3);
	addProduct(&s, 3, "C", "C", "Dell", 50, 10);

	Vector v = filterByProducer(&s, "Dell");
	assert(v.size == 2);
	destroyVector(&v);

	v = filterByPrice(&s, 100);
	assert(v.size == 2);
	destroyVector(&v);

	v = filterByQuantity(&s, 5);
	assert(v.size == 2);
	destroyVector(&v);

	destroyService(&s);
}

/*
 * apeleaza succesiv toate suitele de teste unitare definite in program.
 * pre: -
 * post: afiseaza un mesaj de succes daca toate testele au trecut cu bine.
 */
void runAllTests() {
	testProduct();
	testVector();
	testRepository();
	testServiceCRUD();
	testValidator();
	testSort();
	testFilter();

	printf("All tests passed!\n");
}
