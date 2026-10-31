#pragma once
#include <cassert>
#include "joc.h"
#include "service.h"

void testDomain() {
    Joc j{ 1, 3, "---------", "X", "Neinceput" };
    assert(j.getId() == 1);
    assert(j.getDim() == 3);
    assert(j.getTabla() == "---------");
    assert(j.getJucator() == "X");
    assert(j.getStare() == "Neinceput");
}

void testAll() {
    testDomain();
}