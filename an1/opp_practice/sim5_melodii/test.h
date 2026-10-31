#pragma once
#include <cassert>
#include <stdexcept>
#include "service.h"

void testDomain() {
    Melodie m{ 1, "Piesa", "Artist 1", 5 };
    assert(m.getId() == 1);
    assert(m.getTitlu() == "Piesa");
    assert(m.getRank() == 5);

    m.setRank(10);
    assert(m.getRank() == 10);
}

void testAll() {
    testDomain();
}