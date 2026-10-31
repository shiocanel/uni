#include "Matrice.h"

#include <exception>

using namespace std;


//Best: Theta(1)
//Worst: Theta(1);
//Average: Theta(1);
int Matrice::aloca() {
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

//Best: Theta(1)
//Worst: Theta(1);
//Average: Theta(1);
void Matrice::dealoca(int i) {
	urm[i] = primLiber;
	primLiber = i;
}

//Best: Theta(cp)
//Worst: Theta(cp);
//Average: Theta(cp);
void Matrice::redimensioneaza() {
	int cpNou = cp * 2;
	Triplet* eNou = new Triplet[cpNou];
	int* urmNou = new int[cpNou];
	int* precNou = new int[cpNou];

	for (int i = 0; i < cp; i++) {
		eNou[i] = e[i];
		urmNou[i] = urm[i];
		precNou[i] = prec[i];
	}

	for (int i = cp; i < cpNou - 1; i++)
		urmNou[i] = i + 1;

	urmNou[cpNou - 1] = -1;
	primLiber = cp;

	delete[] e;
	delete[] urm;
	delete[] prec;

	e = eNou;
	urm = urmNou;
	prec = precNou;
	cp = cpNou;
}

//Best: Theta(cp)
//Worst: Theta(cp);
//Average: Theta(cp);
Matrice::Matrice(int m, int n) {
	if (m <= 0 || n <= 0) {
		throw exception();
	}
	linii = m;
	coloane = n;
	cp = 8;

	e = new Triplet[cp];
	urm = new int[cp];
	prec = new int[cp];

	prim = -1;
	ultim = -1;

	for (int i = 0; i < cp - 1; i++)
		urm[i] = i + 1;

	urm[cp - 1] = -1;
	primLiber = 0;
}

//Best: Theta(1)
//Worst: Theta(1);
//Average: Theta(1);
int Matrice::nrLinii() const {
	return linii;
}

//Best: Theta(1)
//Worst: Theta(1);
//Average: Theta(1);
int Matrice::nrColoane() const {
	return coloane;
}

//Best: Theta(1)
//Worst: Theta(n);
//Average: O(n);
TElem Matrice::element(int i, int j) const {
	if (i < 0 || i >= linii || j < 0 || j >= coloane) {
		throw exception();
	}

	int curent = prim;
	while (curent != -1) {
		if (e[curent].l == i && e[curent].c == j)
			return e[curent].v;

		if (e[curent].l > i || (e[curent].l == i && e[curent].c > j))
			break;

		curent = urm[curent];
	}

	return NULL_TELEMENT;
}

//Best: Theta(1)
//Worst: Theta(n) amortizat sau n + cp
//Average: O(n);
TElem Matrice::modifica(int i, int j, TElem val) {
	if (i < 0 || i >= linii || j < 0 || j >= coloane) {
		throw exception();
	}

	int curent = prim;
	int precedent = -1;

	while (curent != -1 && (e[curent].l < i || (e[curent].l == i && e[curent].c < j))) {
		precedent = curent;
		curent = urm[curent];
	}

	if (curent != -1 && e[curent].l == i && e[curent].c == j) {
		TElem valoareVeche = e[curent].v;

		if (val == NULL_TELEMENT) {
			if (curent == prim) {
				prim = urm[curent];
				if (prim != -1) 
					prec[prim] = -1;
				else
					ultim = -1;
			}
			else if (curent == ultim) {
				ultim = prec[curent];
				if (ultim != -1) 
					urm[ultim] = -1;
				else 
					prim = -1;
			}
			else {
				urm[prec[curent]] = urm[curent];
				prec[urm[curent]] = prec[curent];
			}
			dealoca(curent);
		}
		else {
			e[curent].v = val;
		}
		return valoareVeche;
	}

	if (val != NULL_TELEMENT) {
		if (primLiber == -1)
			redimensioneaza();

		int nou = aloca();
		e[nou].l = i;
		e[nou].c = j;
		e[nou].v = val;

		if (precedent == -1) {
			urm[nou] = prim;
			prec[nou] = -1;

			if (prim != -1) 
				prec[prim] = nou;
			else 
				ultim = nou;
			prim = nou;
		}
		else if (curent == -1) {
			urm[nou] = -1;
			prec[nou] = precedent;
			urm[precedent] = nou;
			ultim = nou;
		}
		else {
			urm[nou] = curent;
			prec[nou] = precedent;
			urm[precedent] = nou;
			prec[curent] = nou;
		}
	}

	return NULL_TELEMENT;
}

//Best: Theta(1)
//Worst: Theta(1);
//Average: Theta(1);
Matrice::~Matrice() {
	delete[] e;
	delete[] urm;
	delete[] prec;
}