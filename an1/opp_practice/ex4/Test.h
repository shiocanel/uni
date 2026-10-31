#pragma once
#include <cassert>

#include "Service.h"

void testProcesor() {
	Procesor procesor("nume", 10, "soclu", 123);
	assert(procesor.getNume() == "nume");
	assert(procesor.getNrThreaduri() == 10);
	assert(procesor.getSocluProcesor() == "soclu");
	assert(procesor.getPret() == 123);
}

void testPlaca() {
	PlacaDeBaza placa("nume", "soclu", 123);
	assert(placa.getNume() == "nume");
	assert(placa.getSocluProcesor() == "soclu");
	assert(placa.getPret() == 123);
}

void testServiceAndRepo() {
	try {
		Repository repo("inexistent.txt", "inexistent.txt");
	}
	catch (runtime_error e) {
	}
	try {
		Repository repo("procesoare.txt", "inexistent.txt");
	}
	catch (runtime_error e) {
	}

	Repository repo("procesoare.txt", "placiDeBaza.txt");
	Service service{ repo };

	try {
		service.addPlacaDeBaza("", "soclu", 123);
	}
	catch (runtime_error e) {
	}
	try {
		service.addPlacaDeBaza("nume", "", 123);
	}
	catch (runtime_error e) {
	}
	try {
		service.addPlacaDeBaza("nume", "soclu", -123);
	}
	catch (runtime_error e) {
	}

	vector<Procesor> p = service.getProcesoare();
	assert(p[0].getNume() == "Ryzen");

	vector<PlacaDeBaza> placi = service.getPlaciDeBaza();
	assert(placi[0].getNume() == "Mazda");

	vector<PlacaDeBaza> filtrat = service.filtrareSoclu("Mata");
	assert(filtrat.size() == 2);

	service.addPlacaDeBaza("nume", "soclu", 123);
	vector<PlacaDeBaza> placa = service.getPlaciDeBaza();

	int n = placa.size() - 1;
	assert(placa[n].getNume() == "nume");
	assert(placa[n].getSocluProcesor() == "soclu");
	assert(placa[n].getPret() == 123);
}

void testAll() {
	testProcesor();
	testPlaca();
	testServiceAndRepo();
}