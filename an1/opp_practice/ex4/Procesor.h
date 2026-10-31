#pragma once

#include <string>

using namespace std;

class Procesor {
private:
	string nume;
	int nrThreaduri;
	string socluProcesor;
	double pret;
public:
	Procesor(string nume, int nrThreaduri, string socluProcesor, double pret) :
		nume{ nume }, nrThreaduri{ nrThreaduri }, socluProcesor{ socluProcesor }, pret{ pret } {

	}

	string getNume() const {
		return nume;
	}
	int getNrThreaduri() const {
		return nrThreaduri;
	}
	string getSocluProcesor() const {
		return socluProcesor;
	}
	double getPret() const {
		return pret;
	}
};