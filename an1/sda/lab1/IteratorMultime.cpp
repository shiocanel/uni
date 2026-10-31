#include "IteratorMultime.h"
#include "Multime.h"

// Theta(1)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	this->curent = 0;
}

// Theta(1)
TElem IteratorMultime::element() const {
	return mult.elemente[this->curent];
}

// Theta(1)
bool IteratorMultime::valid() const {
	return this->curent < mult.dim();
}

// Theta(1)
void IteratorMultime::urmator() {
	this->curent++;
}

// Theta(1)
void IteratorMultime::prim() {
	this->curent = 0;
}

