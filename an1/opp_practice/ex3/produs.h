#pragma once
#include <string>

using namespace std;

class Produs {
private:
	int codProdus;
	string denumire;
	string categorie;
	int anFabricatie;
	float pret;

public:
	Produs(int codProdus, string denumire, string categorie, int anFabricatie, float pret) :
		codProdus{ codProdus }, denumire{ denumire }, categorie{ categorie }, anFabricatie{ anFabricatie }, pret{ pret } {
	}

	int getCodProdus() const {
		return codProdus;
	}
	string getDenumire() const {
		return denumire;
	}
	string getCategorie() const {
		return categorie;
	}
	int getAnFabricatie() const {
		return anFabricatie;
	}
	float getPret() const {
		return pret;
	}
};