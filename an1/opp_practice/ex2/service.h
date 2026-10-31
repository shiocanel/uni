#pragma once

#include "repository.h"

class Service {
private:
	Repository& repo;

public:
	Service(Repository& repo) : repo{repo} {
	}

	vector<Masina> getAll() {
		return repo.getAll();
	}

	vector<Masina> sorteazaByModel() {
		auto ans = getAll();
		sort(ans.begin(), ans.end(), [&](const Masina& a, const Masina& b) {
			return a.getModel() < b.getModel();
			});

		return ans;
	}

	vector<Masina> sorteazaByNrMatricol() {
		auto ans = getAll();
		sort(ans.begin(), ans.end(), [&](const Masina& a, const Masina& b) {
			return a.getNrMatricol() < b.getNrMatricol();
			});

		return ans;
	}
};