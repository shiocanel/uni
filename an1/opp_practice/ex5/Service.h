#pragma once

#include "Repository.h"

class Service {
private:
	Repository& repo;

public:
	Service(Repository& repo) : repo{ repo } {

	}
	
	void stergeApartament(int cod) {
		repo.stergeApartament(cod);
	}

	vector<Apartament> getAll() {
		return repo.getAll();
	}

	vector<Apartament> filtreazaSuprafata(int left, int right, vector<Apartament> aux) {
		if (left == -1)
			return getAll();

		vector<Apartament> res;
		for (Apartament apartament : aux)
			if (apartament.getSuprafata() >= left && apartament.getSuprafata() <= right)
				res.push_back(apartament);

		return res;
	}

	vector<Apartament> filtreazaPret(double left, double right, vector<Apartament> aux) {
		if (left == -1)
			return getAll();

		vector<Apartament> res;
		for (Apartament apartament : aux)
			if (apartament.getPret() >= left && apartament.getPret() <= right)
				res.push_back(apartament);

		return res;
	}

	vector<Apartament> filtreazaPretSuprafata(double pretSt, double pretDr, int suprafataSt, int suprafataDr) {
		vector<Apartament> res = filtreazaPret(pretSt, pretDr, getAll());
		return filtreazaSuprafata(suprafataSt, suprafataDr, res);
	}
};