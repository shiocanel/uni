#pragma once
#include <cassert>
#include "service.h"

void testDomain() {
    Melodie m{ 1, "Titlu", "Artist", "pop" };
    assert(m.getId() == 1);
    assert(m.getTitlu() == "Titlu");
    assert(m.getArtist() == "Artist");
    assert(m.getGen() == "pop");
}

void testAll() {
    testDomain();
}