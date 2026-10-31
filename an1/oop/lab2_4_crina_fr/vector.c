#include "vector.h"
#include <stdlib.h>

Vector* createVector() {
	Vector* v = (Vector*)malloc(sizeof(Vector));
	if (v == NULL) return NULL;

	v->capacity = 2;
	v->size = 0;
	v->elements = (TElement*)malloc(v->capacity * sizeof(TElement));

	return v;
}

void destroyVector(Vector* vector) {
	if (vector == NULL) return;
	free(vector->elements);
	free(vector);
}

void add(Vector* vector, TElement el) {
	if (vector->size == vector->capacity) {
		int newCapacity = vector->capacity * 2;
		TElement* temp = (TElement*)realloc(vector->elements, newCapacity * sizeof(TElement));

		if (temp != NULL) {
			vector->elements = temp;
			vector->capacity = newCapacity;
		}
	}
	vector->elements[vector->size++] = el;
}

TElement get(Vector* vector, int idx) {
	if (idx < 0 || idx >= vector->size) return NULL;
	return vector->elements[idx];
}

void set(Vector* vector, int idx, TElement el) {
	if (idx >= 0 && idx < vector->size) {
		vector->elements[idx] = el;
	}
}

TElement deleteElement(Vector* vector, int idx) {
	if (idx < 0 || idx >= vector->size) return NULL;

	TElement el = vector->elements[idx];
	for (int i = idx; i < vector->size - 1; i++) {
		vector->elements[i] = vector->elements[i + 1];
	}
	vector->size--;
	return el;
}

int size(Vector* vector) {
	if (vector == NULL) return 0;
	return vector->size;
}