#pragma once
#include "service.h"
#include <cassert>

void testDomain() {
    Produs p{ 1, "iPhone 12", "telefon", 2020, 3200 };
    assert(p.getCodProdus() == 1);
    assert(p.getDenumire() == "iPhone 12");
    assert(p.getCategorie() == "telefon");
    assert(p.getAnFabricatie() == 2020);
    assert(p.getPret() == 3200);
}

void testRepoGetAll() {
    Repository repo("testProduse.txt");
    auto all = repo.getAll();
    assert(all.size() == 3);
    assert(all[0].getCodProdus() == 1);
    assert(all[1].getCodProdus() == 2);
    assert(all[2].getCodProdus() == 3);
}

void testServiceGetAll() {
    Repository repo("testProduse.txt");
    Service service{ repo };
    assert(service.getAll().size() == 3);
}

void testServiceCategories() {
    Repository repo("testProduse.txt");
    Service service{ repo };
    auto cats = service.getCategorii();
    assert(cats.size() == 2);
}

void testServiceFilterByCategory() {
    Repository repo("testProduse.txt");
    Service service{ repo };
    auto list = service.filtrareCategorie("laptop");
    assert(list.size() == 1);
    assert(list[0].getDenumire() == "Dell Inspiron");
}

void testServiceSearch() {
    Repository repo("testProduse.txt");
    Service service{ repo };
    auto list = service.cautaDenumire("iphone", service.getAll());
    assert(list.size() == 1);
    assert(list[0].getCodProdus() == 1);
}

void testServiceFilterAndSearch() {
    Repository repo("testProduse.txt");
    Service service{ repo };
    auto list = service.cautaSiFiltreaza("telefon", "samsung");
    assert(list.size() == 1);
    assert(list[0].getCodProdus() == 3);
}

void testAll() {
    testDomain();
    testRepoGetAll();
    testServiceGetAll();
    testServiceCategories();
    testServiceFilterByCategory();
    testServiceSearch();
    testServiceFilterAndSearch();
}