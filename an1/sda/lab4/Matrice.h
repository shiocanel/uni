#pragma once

typedef int TElem;

#define NULL_TELEMENT 0

struct Triplet {
	int l;
	int c;
	TElem v;
};

class Matrice {

private:
	int linii;
	int coloane;

	int cp;
	Triplet* e;
	int* urm;
	int* prec;

	int prim;
	int ultim;
	int primLiber;

	int aloca();
	void dealoca(int i);
	void redimensioneaza();

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice();

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

};







