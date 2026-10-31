#ifndef VECTOR_H
#define VECTOR_H

#include "product.h"

#define CAPACITY 100

typedef Product TypeElement;
typedef struct {
	TypeElement elements[CAPACITY];
	int size;
} Vector;

Vector createVector();
void destroyVector(Vector* vector);
void add(Vector* vector, TypeElement product);

#endif // !VECTOR_H