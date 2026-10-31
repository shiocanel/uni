#pragma once
#include <cassert>
#include <stdexcept>
#include "service.h"

void testDomain() {
    /*
    functie de test pentru domain
    */

    Melodie m{ 1, "Piesa", "Artist", 5 };
    assert(m.getId() == 1);
    assert(m.getArtist() == "Artist");
    assert(m.getTitlu() == "Piesa");
    assert(m.getRank() == 5);

    m.setRank(10);
    assert(m.getRank() == 10);
    m.setTitlu("alt");
    assert(m.getTitlu() == "alt");
}

void testRepo() {
    /*
    functie de test pentru Repository
    */

    Repository repo("melodii.txt");
    vector<Melodie> melodii = repo.getAll();

    assert(melodii[0].getId() == 1);
    assert(melodii[0].getTitlu() == "Die");
    assert(melodii[0].getArtist() == "Violent Viora");
    assert(melodii[0].getRank() == 7);

    Melodie m = repo.getById(2);
    assert(m.getId() == 2);
    assert(m.getTitlu() == "Smells like Teens Spirits");
    assert(m.getArtist() == "Nirvana");
    assert(m.getRank() == 8);

    try {
        m = repo.getById(20);
    }
    catch (...) {

    }

    repo.sterge(10);
    melodii = repo.getAll();
    assert(melodii.size() == 9);

    repo.update(Melodie(9, "buuu", "anto", 8));
    melodii = repo.getAll();
    assert(melodii[8].getTitlu() == "buuu");

    Melodie m1{10, "Shape of You", "Ed Sheeran", 9};
    repo.add(m1);
    melodii = repo.getAll();
    assert(melodii.size() == 10);
}

void testService() {
    /*
    functie de test pentru Service
    */
    
    Repository repo("melodii.txt");
    Service service{ repo };

    vector<Melodie> melodii = service.getMelodiiSortateDupaRank();

    assert(melodii[0].getId() == 3);

    service.modificaMelodie(9, "buuu", 8);

    try {
        service.modificaMelodie(9, "", 8);
    }
    catch (...) {

    }

    try {
        service.modificaMelodie(9, "buuu", 20);
    }
    catch (...) {

    }

    service.stergeMelodie(10);
    try {
        service.stergeMelodie(7);
    }
    catch (...) {

    }

    Melodie m1{ 10, "Shape of You", "Ed Sheeran", 9 };
    repo.add(m1);
    melodii = repo.getAll();
    assert(melodii.size() == 10);

    vector<int> f = service.getFrecventeRank();
    assert(f[10] == 1);
}

void testAll() {
    /*
    functie care testeaza intreaga arhitectura mai putin UI
    */

    testDomain();
    testRepo();
    testService();
}