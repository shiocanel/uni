#pragma once
#include <string>
//#include <utility>

using std::string;

class Rochie {
private:
	int cod;
	string denumire;
	string marime;
	double pret;
	bool disponibilitate;
public:
	Rochie(int cod, string denumire, string marime, double pret, bool disponibilitate) : cod{ cod }, denumire{ move(denumire) }, marime{ move(marime) }, pret{ pret }, disponibilitate{ disponibilitate } {}

	int getCod() const {
		return cod;
	}

	string getDenumire() const {
		return denumire;
	}

	string getMarime() const {
		return marime;
	}

	double getPret() const {
		return pret;
	}

	bool isDisponibila() const {
		return disponibilitate;
	}

	void setDisponibiliate(bool value) {
		disponibilitate = value;
	}
};