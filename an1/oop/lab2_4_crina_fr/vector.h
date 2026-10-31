#ifndef VECTOR_H
#define VECTOR_H

typedef void* TElement;

typedef struct {
	TElement* elements;
	int capacity;
	int size;
} Vector;

Vector* createVector();

void destroyVector(Vector* vector);

void add(Vector* vector, TElement el);

TElement get(Vector* vector, int idx);

void set(Vector* vector, int idx, TElement el);

TElement deleteElement(Vector* vector, int idx);

int size(Vector* vector);

#endif