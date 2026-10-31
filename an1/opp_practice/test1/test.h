#pragma once
#include "service.h"
#include <cassert>

void testDomain() {
    Rochie r{ 1, "GUCCI WOOL DRESS", "S", 9000, true };
    assert(r.getCod() == 1);
    assert(r.getDenumire() == "GUCCI WOOL DRESS");
    assert(r.getMarime() == "S");
    assert(r.getPret() == 9000);
    assert(r.isDisponibila());
}

void testRepoGetAll() {
    Repository repo("testRochii.txt");
    auto all = repo.getAll();
    assert(all.size() == 3);
    assert(all[0].getCod() == 1);
    assert(all[1].getCod() == 2);
    assert(all[2].getCod() == 3);
}

void testRepoFindByCod() {
    Repository repo("testRochii.txt");
    auto& r = repo.findByCod(2);
    assert(r.getDenumire() == "DIOR EVENING DRESS");
}

void testServiceGetAll() {
    Repository repo("testRochii.txt");
    Service service{ repo };
    auto all = service.getAll();
    assert(all.size() == 3);
}

void testServiceInchiriere() {
    Repository repo("testRochii.txt");
    Service service{ repo };

    service.inchiriazaRochie(1);
    assert(!repo.findByCod(1).isDisponibila());

    bool thrown = false;
    try {
        service.inchiriazaRochie(2);
        service.inchiriazaRochie(2);
    }
    catch (const std::runtime_error&) {
        thrown = true;
    }
    assert(thrown);
}

void testServiceSortari() {
    Repository repo("testRochii.txt");
    Service service{ repo };

    auto byPret = service.sortByPret();
    assert(byPret.front().getCod() == 3);

    auto byMarime = service.sortByMarime();
    assert(byMarime.front().getMarime() == "XS");
}

void testAll() {
    testDomain();
    testRepoGetAll();
    testRepoFindByCod();
    testServiceGetAll();
    testServiceInchiriere();
    testServiceSortari();
}