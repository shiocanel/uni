#pragma once
#include <vector>
#include <fstream>
#include <sstream>

#include "Apartament.h"

using namespace std;

class Repository {
private:
	vector<Apartament> apartamente;

	void readFromFile(string fileName) {
		ifstream fin(fileName);
		if (!fin.is_open())
			throw runtime_error("Nu s-a deschis fisierul");

		string line;
		while (getline(fin, line)) {
			string codApartament, strada, suprafata, pret;
			stringstream ss(line);

			getline(ss, codApartament, ';');
			getline(ss, strada, ';');
			getline(ss, suprafata, ';');
			getline(ss, pret, ';');

			Apartament apartament(stoi(codApartament), strada, stoi(suprafata), stoi(pret));

			apartamente.push_back(apartament);
		}
	}
public:
	Repository(string fileName) {
		readFromFile(fileName);
	}

	vector<Apartament> getAll() {
		return apartamente;
	}

	void stergeApartament(int cod) {
		vector<Apartament> res;
		for (Apartament apartament : apartamente)
			if (apartament.getCodApartament() != cod)
				res.push_back(apartament);
		
		apartamente = res;
	}
};
