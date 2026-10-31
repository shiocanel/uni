#ifndef PRODUCT_H
#define PRODUCT_H

#include <string.h>
#include <stdlib.h>

typedef struct {
	int id;
	char* name;
	char* model;
	char* producer;
	double price;
	int quantity;
} Product;

/*
 * creeaza o instanta noua de tip product si aloca memorie pentru campurile sale de tip text.
 * pre: id > 0, price >= 0, quantity >= 0, name/model/producer - siruri de caractere valide.
 * post: returneaza un obiect product cu atributele setate si memorie alocata pentru nume, model si producator.
 */
Product createProduct(int id, char* name, char* model, char* producer, double price, int quantity);

/*
 * elibereaza memoria alocata dinamic pentru campurile interne ale unui produs (name, model, producer).
 * pre: product - pointer catre o structura product valida.
 * post: memoria ocupata de atributele produsului este eliberata.
 */
void destroyProduct(Product* product);


#endif // !PRODUCT_H
