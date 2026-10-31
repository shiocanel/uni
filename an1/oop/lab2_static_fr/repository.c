#include "repository.h"

Repository createRepository() {
	Repository repo;
	repo.products = createVector();

	return repo;
}

void destroyRepository(Repository* repo) {
	destroyVector(&(repo->products));
}

void addProductRepo(Repository* repo, Product product) {
	add(&(repo->products), product);
}

int getIndexOf(Repository* repo, int id) {
	for (int i = 0; i < repo->products.size; i++)
		if (repo->products.elements[i].id == id)
			return i;

	return -1;
}

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

int updateProductRepo(Repository* repo, int id, Product product) {
	int index = getIndexOf(repo, id);

	if (index == -1)
		return -1;

	destroyProduct(&(repo->products.elements[index]));
	repo->products.elements[index] = product;

	return 1;
}

Product* getProductAt(Repository* repo, int idx) {
	if (idx < 0 || idx >= repo->products.size)
		return NULL;
	return &(repo->products.elements[idx]);
}

Vector* getAllProductsRepo(Repository* repo) {
	return &repo->products;
}