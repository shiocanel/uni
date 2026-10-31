#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
// Theta(1);
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) 
		return true;
	else
		return false;
}

// Theta(n);
void Multime::redim() {
	this->capacitate *= 2;
	TElem* elementeNoi = new TElem[this->capacitate];
	for (int i = 0; i < this->dimensiune; i++)
		elementeNoi[i] = this->elemente[i];

	delete[] this->elemente;
	this->elemente = elementeNoi;
}

// Theta(1)
Multime::Multime() {
	this->capacitate = 2;
	this->dimensiune = 0;
	this->elemente = new TElem[this->capacitate];
}

// O(n)
bool Multime::adauga(TElem elem) {
	if (cauta(elem))
		return false;

	if (this->dimensiune == this->capacitate)
		redim();

	int i = 0;
	while (i < this->dimensiune && rel(this->elemente[i], elem))
		i++;

	for (int j = this->dimensiune; j > i; j--)
		this->elemente[j] = this->elemente[j - 1];

	this->elemente[i] = elem;
	this->dimensiune++;

	return true;
}

// O(n)
bool Multime::sterge(TElem elem) {
	int poz = -1;
	for (int i = 0; i < this->dimensiune; i++)
		if (this->elemente[i] == elem) {
			poz = i;
			break;
		}

	if (poz == -1)
		return false;

	for (int i = poz; i < this->dimensiune - 1; i++)
		this->elemente[i] = this->elemente[i + 1];

	this->dimensiune--;

	return true;
}

// O(n)
bool Multime::cauta(TElem elem) const {
	for (int i = 0; i < this->dimensiune; i++)
		if (this->elemente[i] == elem)
			return true;

	return false;
}

// Theta(1)
int Multime::dim() const {
	return this->dimensiune;
}

// Theta(1)
bool Multime::vida() const {
	return this->dimensiune == 0;
}

// Theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

// Theta(1)
Multime::~Multime() {
	delete[] this->elemente;
}






