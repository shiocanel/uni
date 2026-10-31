#include "vector.h"

#include <stdlib.h>

/*
 * initializeaza un vector dinamic nou.
 * pre: -
 * post: returneaza o structura vector cu elementele alocate, size 0 si capacitate initiala.
 */
Vector createVector() {
	Vector vector;
	vector.capacity = 5;
	vector.size = 0;
	vector.elements = malloc(sizeof(Product) * vector.capacity);

	return vector;
}

/*
 * elibereaza memoria alocata pentru elementele vectorului dinamic.
 * pre: vector - pointer valid catre o structura vector.
 * post: memoria ocupata de elemente este eliberata si resursele sunt distruse.
 */
void destroyVector(Vector* vector) {
	for (int i = 0; i < vector->size; i++) {
		destroyProduct(&(vector->elements[i]));
	}

	free(vector->elements);

	vector->size = 0;
	vector->elements = NULL;
	vector->capacity = 0;
}

/*
 * adauga un element nou de tip product in vectorul dinamic.
 * pre: vector - pointer valid, product - instanta valida de tip typeelement.
 * post: elementul este adaugat la finalul listei, iar capacitatea este marita daca este plin.
 */
void add(Vector* vector, TypeElement product) {
	if (vector->size == vector->capacity) {
		TypeElement* aux = malloc(sizeof(Product) * (vector->capacity * 2));
		
		for (int i = 0; i < vector->size; i++)
			aux[i] = vector->elements[i];
		
		free(vector->elements);
		vector->elements = aux;
		vector->capacity *= 2;
	}

	vector->elements[vector->size++] = product;
}