#pragma once
#include <cassert>
#include "service.h"

void testDomain() {
    Produs p{ 1, "Mar", "Fruct", 2.5 };
    assert(p.getId() == 1);
    assert(p.getNume() == "Mar");
    assert(p.getTip() == "Fruct");
    assert(p.getPret() == 2.5);
}

void testAll() {
    testDomain();
}