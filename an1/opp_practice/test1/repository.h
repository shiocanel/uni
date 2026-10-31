#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "rochie.h"

using namespace std;

class Repository {
private:
	vector<Rochie> elements;
	string fileName;

	void readFromFile() {
		ifstream fin(fileName);
		if (!fin.is_open()) {
			throw runtime_error("Fisierul nu a putut fi deschis: " + fileName);
		}

		string line;
		while (getline(fin, line)) {
			if (line.empty())
				continue;

			string cod, denumire, marime, pret, disponibilitate;
			stringstream ss(line);

			getline(ss, cod, ';');
			getline(ss, denumire, ';');
			getline(ss, marime, ';');
			getline(ss, pret, ';');
			getline(ss, disponibilitate, ';');

			bool disp = disponibilitate == "True" ? true : false;

			Rochie rochie(stoi(cod), denumire, marime, stoi(pret), disp);

			this->elements.push_back(rochie);
		}
	}

public:
	Repository(const string& fileName) : fileName{ fileName } {
		readFromFile();
	};

	vector<Rochie> getAll() const {
		return elements;
	}

	Rochie& findByCod(int id) {
		auto res = find_if(elements.begin(), elements.end(), [id](Rochie& curr) {
			return curr.getCod() == id;
			});

		if (res == elements.end())
			throw runtime_error("Element not found for id: " + to_string(id));

		return *res;
	}
};