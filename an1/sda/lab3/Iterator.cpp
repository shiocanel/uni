#include "Iterator.h"
#include "DO.h"

using namespace std;

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
Iterator::Iterator(const DO& d) : dict(d) {
	curent = d.prim;
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
void Iterator::prim() {
	curent = dict.prim;
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
void Iterator::urmator() {
	if (!valid())
		throw exception();
	
	curent = curent->urm;
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
bool Iterator::valid() const {
	return curent != nullptr;
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
TElem Iterator::element() const {
	if (!valid())
		throw exception();

	return curent->e;
}


