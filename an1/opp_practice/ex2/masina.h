#pragma once
#include <string>

using namespace std;

class Masina {
private:
	int nrMatricol;
	string model;
	string culoare;
	int kmRulati;


public:
	Masina(int nrMatricol, string model, string culoare, int kmRulati) :
		nrMatricol{ nrMatricol }, model{ model }, culoare{ culoare }, kmRulati{ kmRulati } {
	};

	int getNrMatricol() const {
		return nrMatricol;
	}
	string getModel() const {
		return model;
	}
	string getCuloare() const {
		return culoare;
	}
	int getKmRulati() const {
		return kmRulati;
	}
};