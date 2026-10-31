#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "vector.h"

typedef struct {
	Vector products;
} Repository;

Repository createRepository();
void destroyRepository(Repository* repo);

void addProductRepo(Repository* repo, Product product);
int deleteProductRepo(Repository* repo, int id);
int updateProductRepo(Repository* repo, int id, Product product);
Product* getProductAt(Repository* repo, int idx);
int getIndexOf(Repository* repo, int id);

Vector* getAllProductsRepo(Repository* repo);

#endif // !REPOSITORY_H