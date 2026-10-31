#pragma once
#include <vector>
#include <fstream>
#include <sstream>

#include "produs.h"

using namespace std;

class Repository {
private:
	vector<Produs> produse;
	string fileName;

	void readFromFile() {
		ifstream fin(fileName);
		if (!fin.is_open())
			throw runtime_error("Nu este deschis fisierul!");

		string line;
		while (getline(fin ,line)) {
			if (line.empty())
				continue;

			string codProdus, denumire, categorie, anFabricatie, pret;
			stringstream ss(line);

			getline(ss, codProdus, ';');
			getline(ss, denumire, ';');
			getline(ss, categorie, ';');
			getline(ss, anFabricatie, ';');
			getline(ss, pret, ';');

			Produs produs(stoi(codProdus), denumire, categorie, stoi(anFabricatie), stoi(pret));
			produse.push_back(produs);
		}
	}

public:
	Repository(string fileName) : fileName{ fileName } {
		readFromFile();
	}

	vector<Produs> getAll() {
		return produse;
	}
};