#ifndef SERVICE_H
#define SERVICE_H

#include "repository.h"

typedef struct {
	Repository repo;
} Service;

Service createService();
void destroyService(Service* service);

int addProduct(Service* service, int id, char* name, char* model, char* producer, double price, int quantity);
int deleteProduct(Service* service, int id);
int updateProduct(Service* service, int id, char* name, char* model, char* producer, double price, int quantity);

Vector* getAllProducts(Service* service);

Vector sortByPrice(Service* service, int ascending);
Vector sortByQuantity(Service* service, int ascending);

Vector filterByProducer(Service* service, char* producer);
Vector filterByPrice(Service* service, double price);
Vector filterByQuantity(Service* service, int quantity);

#endif // !SERVICE_H