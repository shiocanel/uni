#include "vector.h"

Vector createVector() {
	Vector vector;
	vector.size = 0;
	return vector;
}

void destroyVector(Vector* vector) {
	vector->size = 0;
}

void add(Vector* vector, TypeElement product) {
	if (vector->size < CAPACITY) {
		vector->elements[vector->size++] = product;
	}
}