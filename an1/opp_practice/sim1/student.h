#pragma once
#include <string>

using namespace std;

class Student {
private:
	int nrMatricol;
	string nume;
	int varsta;
	string facultate;
public:
	Student(int nrMatricol, string nume, int varsta, string facultate) : nrMatricol{ nrMatricol }, nume{ nume }, varsta{ varsta },
		facultate{ facultate } {
	};

	int getNrMatrcol() const {
		return nrMatricol;
	}

	string getNume() const {
		return nume;
	}
	
	int getVarsta() const {
		return varsta;
	}

	string getFacultate() const {
		return facultate;
	}

	void setVarsta(int value) {
		varsta = value;
	}
};