#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;


/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
DO::DO(Relatie r) {
	prim = nullptr;
	dimensiune = 0;
	rel = r;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
/*
Best: Theta(1);
Worst: Theta(n);
Average: O(n);
*/
TValoare DO::adauga(TCheie c, TValoare v) {
	Nod* p = prim;
	Nod* ant = nullptr;

	while (p != nullptr && rel(p->e.first, c)) {
		if (p->e.first == c) {
			TValoare vechi = p->e.second;
			p->e.second = v;
			return vechi;
		}

		ant = p;
		p = p->urm;
	}

	Nod* nou = new Nod{ {c, v}, p };

	if (ant == nullptr)
		prim = nou;
	else
		ant->urm = nou;

	dimensiune++;
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
/*
Best: Theta(1);
Worst: Theta(n);
Average: O(n);
*/
TValoare DO::cauta(TCheie c) const {
	Nod* p = prim;

	while (p != nullptr) {
		if (p->e.first == c)
			return p->e.second;

		p = p->urm;
	}

	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
/*
Best: Theta(1);
Worst: Theta(n);
Average: O(n);
*/
TValoare DO::sterge(TCheie c) {
	Nod* p = prim;
	Nod* ant = nullptr;

	while (p != nullptr) {
		if (p->e.first == c) {
			TValoare val = p->e.second;

			if (ant == nullptr)
				prim = p->urm;
			else
				ant->urm = p->urm;

			delete p;
			dimensiune--;

			return val;
		}

		ant = p;
		p = p->urm;
	}

	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
int DO::dim() const {
	return dimensiune;
}

//verifica daca dictionarul e vid
/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
bool DO::vid() const {
	return dimensiune == 0;
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
Iterator DO::iterator() const {
	return  Iterator(*this);
}

/*
Best: Theta(n);
Worst: Theta(n);
Average: Theta(n);
*/
DO::~DO() {
	Nod* p = prim;
	while (p != nullptr) {
		Nod* aux = p;
		p = p->urm;
		delete aux;
	}
}
