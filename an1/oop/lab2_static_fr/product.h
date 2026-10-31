#ifndef PRODUCT_H
#define PRODUCT_H

#include <string.h>
#include <stdlib.h>

typedef struct {
	int id;
	char name[100];
	char model[100];
	char producer[100];
	double price;
	int quantity;
} Product;

Product createProduct(int id, char* name, char* model, char* producer, double price, int quantity);
void destroyProduct(Product* product);

#endif // !PRODUCT_H