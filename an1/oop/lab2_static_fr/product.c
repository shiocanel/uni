#include "product.h"

Product createProduct(int id, char* name, char* model, char* producer, double price, int quantity) {
	Product product;
	product.id = id;

	strcpy(product.name, name);
	strcpy(product.model, model);
	strcpy(product.producer, producer);

	product.price = price;
	product.quantity = quantity;

	return product;
}

void destroyProduct(Product* product) {
	if (product == NULL)
		return;
}