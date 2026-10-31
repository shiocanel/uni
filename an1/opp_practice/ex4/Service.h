#pragma once

#include "Repository.h"

class Service {
private:
	Repository& repo;



public:
	Service(Repository& repo) : repo{ repo } {

	}

	void addPlacaDeBaza(string nume, string socluProcesor, double pret) {
		if (nume == "")
			throw runtime_error("Invalid Nume");
		if (socluProcesor == "")
			throw runtime_error("Invalid Soclu");
		if (pret < 0)
			throw runtime_error("Invalid Pret");

		repo.addPlacaDeBaza(nume, socluProcesor, pret);
	}

	vector<Procesor> getProcesoare() const {
		return repo.getProcesoare();
	}

	vector<PlacaDeBaza> getPlaciDeBaza() const {
		return repo.getPlaciDeBaza();
	}

	vector<PlacaDeBaza> filtrareSoclu(string soclu) const {
		vector<PlacaDeBaza> res;
		for (PlacaDeBaza placa : getPlaciDeBaza())
			if (placa.getSocluProcesor() == soclu)
				res.push_back(placa);
		return res;
	}
};