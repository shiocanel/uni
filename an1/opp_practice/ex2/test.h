#pragma once
#include <cassert>
#include <iostream>

#include "service.h"

void testMasina() {
	Masina masina(10, "model", "culoare", 10);
	assert(masina.getNrMatricol() == 10);
	assert(masina.getModel() == "model");
	assert(masina.getCuloare() == "culoare");
	assert(masina.getKmRulati() == 10);
}

void testRepo() {
	Repository repo("masini.txt");

	try {
		Repository repo1("inexistent.txt");
	}
	catch (const runtime_error e) {
		assert(true);
	}

	vector<Masina> masini = repo.getAll();
	assert(masini[0].getNrMatricol() == 101);
	assert(masini[0].getModel() == "bmw");
	assert(masini[0].getCuloare() == "galben");
	assert(masini[0].getKmRulati() == 1000);

	Masina& masina = repo.getByNr(101);
	assert(masina.getKmRulati() == 1000);
	try {
		Masina& masina1 = repo.getByNr(1);
	}
	catch (const runtime_error e) {
		assert(true);
	}
}

void testService() {
	Repository repo("masini.txt");
	Service service{ repo };
	vector<Masina> masini = service.getAll();
	assert(masini[0].getNrMatricol() == 101);
	assert(masini[0].getModel() == "bmw");
	assert(masini[0].getCuloare() == "galben");
	assert(masini[0].getKmRulati() == 1000);

	masini = service.sorteazaByModel();
	assert(masini[0].getNrMatricol() == 107);
	assert(masini[0].getModel() == "Creative");
	assert(masini[0].getCuloare() == "albastru");
	assert(masini[0].getKmRulati() == 342234);

	masini = service.sorteazaByNrMatricol();
	assert(masini[0].getNrMatricol() == 101);
	assert(masini[0].getModel() == "bmw");
	assert(masini[0].getCuloare() == "galben");
	assert(masini[0].getKmRulati() == 1000);
}

void testAll() {
	testMasina();
	testRepo();
	testService();
}