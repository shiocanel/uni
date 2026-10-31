#include "product.h"

/*
 * creeaza o instanta noua de tip product si aloca memorie pentru campurile sale de tip text.
 * pre: id > 0, price >= 0, quantity >= 0, name/model/producer - siruri de caractere valide.
 * post: returneaza un obiect product cu atributele setate si memorie alocata pentru nume, model si producator.
 */
Product createProduct(int id, char* name, char* model, char* producer, double price, int quantity) {
	Product product;
	product.id = id;
	
	product.name = (char*)malloc(strlen(name) + 1);
	strcpy(product.name, name);
	product.model = (char*)malloc(strlen(model) + 1);
	strcpy(product.model, model);
	product.producer = (char*)malloc(strlen(producer) + 1);
	strcpy(product.producer, producer);
	product.price = price;
	product.quantity = quantity;
	
	return product;
}

/*
 * elibereaza memoria alocata dinamic pentru campurile interne ale unui produs (name, model, producer).
 * pre: product - pointer catre o structura product valida.
 * post: memoria ocupata de atributele produsului este eliberata.
 */
void destroyProduct(Product* product) {
	if (product == NULL)
		return;

	free(product->name);
	free(product->model);
	free(product->producer);

	product->name = NULL;
	product->model = NULL;
	product->producer = NULL;
}