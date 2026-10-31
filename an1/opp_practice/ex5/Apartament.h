#pragma once
#include <string>

using namespace std;

class Apartament {
private:
	int codApartament;
	string strada;
	int suprafata;
	double pret;
public:
	Apartament(int codApartament, string strada, int suprafata, double pret) :
		codApartament{ codApartament }, strada{ strada }, suprafata{ suprafata }, pret{ pret } {
	}

	int getCodApartament() const {
		return codApartament;
	}
	string getStrada() const {
		return strada;
	}
	int getSuprafata() const {
		return suprafata;
	}
	double getPret() const {
		return pret;
	}
};