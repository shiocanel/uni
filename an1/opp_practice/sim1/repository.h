#pragma once
#include <vector>
#include <fstream>
#include <sstream>

#include "student.h"

using namespace std;

class Repository {
private:
	vector<Student> studenti;
	string fileName;

	void readFromFile() {
		ifstream fin(fileName);

		string line;
		while (getline(fin, line)) {
			if (line.empty())
				continue;

			string nrMatricol, nume, varsta, facultate;
			stringstream ss(line);
			
			getline(ss, nrMatricol, ';');
			getline(ss, nume, ';');
			getline(ss, varsta, ';');
			getline(ss, facultate, ';');

			Student student(stoi(nrMatricol), nume, stoi(varsta), facultate);
			studenti.push_back(student);
		}
	}

	void saveToFile() {
		ofstream fout(fileName);

		for (const auto& s : studenti) {
			fout << s.getNrMatrcol() << ";" << s.getNume() << ";" << s.getVarsta() << ";" << s.getFacultate() << '\n';
		}
	}

public:
	Repository(const string& fileName) : fileName{ fileName } {
		readFromFile();
	}

	vector<Student> getAll() {
		return studenti;
	}

	Student getByNr(int nr) {
		auto res = find_if(studenti.begin(), studenti.end(), [&](const Student& s) {
			return s.getNrMatrcol() == nr;
			});

		if (res == studenti.end())
			throw runtime_error("Studentul nu exista");
		
		return *res;
	}

	void adauga(const Student& s) {
		studenti.push_back(s);
		saveToFile();
	}

	void sterge(int nr) {
		auto res = remove_if(studenti.begin(), studenti.end(), [&](const Student& s) {
			return s.getNrMatrcol() == nr;
			});

		studenti.erase(res, studenti.end());
		saveToFile();
	}

	void modificaVarstaTuturor(int delta) {
		for (auto& s : studenti) {
			s.setVarsta(s.getVarsta() + delta);
		}

		saveToFile();
	}
};