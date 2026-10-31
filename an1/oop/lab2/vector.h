#ifndef VECTOR_H
#define VECTOR_H

#include "product.h"

typedef Product TypeElement;
typedef struct {
	TypeElement* elements;

	int size;
	int capacity;
} Vector;

/*
 * initializeaza un vector dinamic nou.
 * pre: -
 * post: returneaza o structura vector cu elementele alocate, size 0 si capacitate initiala.
 */
Vector createVector();

/*
 * elibereaza memoria alocata pentru elementele vectorului dinamic.
 * pre: vector - pointer valid catre o structura vector.
 * post: memoria ocupata de elemente este eliberata si resursele sunt distruse.
 */
void destroyVector(Vector* vector);

/*
 * adauga un element nou de tip product in vectorul dinamic.
 * pre: vector - pointer valid, product - instanta valida de tip typeelement.
 * post: elementul este adaugat la finalul listei, iar capacitatea este marita daca este plin.
 */
void add(Vector* vector, TypeElement product);

#endif // !VECTOR_H
