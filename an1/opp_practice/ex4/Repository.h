#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Procesor.h"
#include "PlacaDeBaza.h"

using namespace std;

class Repository {
private:
	vector<Procesor> procesoare;
	vector<PlacaDeBaza> placiDeBaza;

	void readProcesoare(string fileName) {
		ifstream fin(fileName);
		if (!fin.is_open())
			throw runtime_error("Eroare Fisier Procesoare");

		string line;
		while (getline(fin, line)) {
			string nume, nrThreaduri, socluProcesor, pret;
			stringstream ss(line);

			getline(ss, nume, ';');
			getline(ss, nrThreaduri, ';');
			getline(ss, socluProcesor, ';');
			getline(ss, pret, ';');

			Procesor procesor(nume, stoi(nrThreaduri), socluProcesor, stoi(pret));
			procesoare.push_back(procesor);
		}
	}

	void readPlaciDeBaza(string fileName) {
		ifstream fin(fileName);
		if (!fin.is_open())
			throw runtime_error("Eroare Fisier Placi De Baza");

		string line;
		while (getline(fin, line)) {
			string nume, socluProcesor, pret;
			stringstream ss(line);

			getline(ss, nume, ';');
			getline(ss, socluProcesor, ';');
			getline(ss, pret, ';');

			PlacaDeBaza placa(nume, socluProcesor, stoi(pret));
			placiDeBaza.push_back(placa);
		}
	}
public:
	Repository(string file1, string file2) {
		readProcesoare(file1);
		readPlaciDeBaza(file2);
	}

	vector<Procesor> getProcesoare() const {
		return procesoare;
	}

	vector<PlacaDeBaza> getPlaciDeBaza() const {
		return placiDeBaza;
	}

	void addPlacaDeBaza(string nume, string socluProcesor, double pret) {
		PlacaDeBaza placa(nume, socluProcesor, pret);
		placiDeBaza.push_back(placa);
	}
};