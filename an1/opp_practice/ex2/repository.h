#pragma once
#include <vector>
#include <fstream>
#include <sstream>

#include "masina.h"
#include <algorithm>

class Repository {
private:
	vector<Masina> masini;
	string fileName;

	void readFromFile() {
		ifstream fin(fileName);
		if (!fin.is_open())
			throw runtime_error("Nu s-a putut deschide fisierul");

		string line;
		while (getline(fin, line)) {
			if (line.empty())
				continue;

			string nrMatricol, model, culoare, kmRulati;
			stringstream ss(line);

			getline(ss, nrMatricol, ';');
			getline(ss, model, ';');
			getline(ss, culoare, ';');
			getline(ss, kmRulati, ';');

			Masina masina(stoi(nrMatricol), model, culoare, stoi(kmRulati));
			masini.push_back(masina);
		}
	}

public:
	Repository(const string& fileName) : fileName{fileName} {
		readFromFile();
	}

	vector<Masina> getAll() {
		return masini;
	}

	Masina& getByNr(int nr) {
		auto res = find_if(masini.begin(), masini.end(), [nr](Masina& masina) {
			return masina.getNrMatricol() == nr;
			});
		
		if (res == masini.end())
			throw runtime_error("Invalid Numar Matricol");
		return *res;
	}
};