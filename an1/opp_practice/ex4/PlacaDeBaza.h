#pragma once

#include <string>

using namespace std;

class PlacaDeBaza {
private:
	string nume;
	string socluProcesor;
	double pret;
public:
	PlacaDeBaza(string nume, string socluProcesor, double pret) : nume{ nume }, socluProcesor{ socluProcesor }, pret{ pret } {

	}

	string getNume() const {
		return nume;
	}
	string getSocluProcesor() const {
		return socluProcesor;
	}
	double getPret() const {
		return pret;
	}
};