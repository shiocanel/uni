#pragma once
#include <cassert>

#include "Service.h"

void testApartament() {
	Apartament apartament(10, "strada", 100, 2);
	assert(apartament.getCodApartament() == 10);
	assert(apartament.getStrada() == "strada");
	assert(apartament.getSuprafata() == 100);
	assert(apartament.getPret() == 2);
}

void testServiceRepo() {
	try {
		Repository repo("inexistent.txt");
	}
	catch (runtime_error& e) {

	}

	Repository repo("apartamente.txt");
	Service service{ repo };

	assert(service.getAll().size() == 10);

	service.stergeApartament(1);
	assert(service.getAll().size() == 9);
	//2
	vector<Apartament> res = service.filtreazaPretSuprafata(100, 150, 50, 55);
	assert(res.size() == 1);

}

void testAll() {
	testApartament();
	testServiceRepo();
}