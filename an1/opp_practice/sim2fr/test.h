#pragma once
#include <cassert>
#include <fstream>
#include "service.h"

void testDomain() {
    Masina m{ "B123XYZ", "BMW X5", 2020, "suv" };
    assert(m.getNrInmatriculare() == "B123XYZ");
    assert(m.getDenumire() == "BMW X5");
    assert(m.getAnFabricatie() == 2020);
    assert(m.getTip() == "suv");

    m.setAnFabricatie(2021);
    assert(m.getAnFabricatie() == 2021);
}

void testAll() {
    testDomain();
    // Aici se pot scrie rapid apeluri catre Repository / Service
    // daca profesorul insista, recomandat fiind crearea unui fisier text "test.txt" temporar.
}