#pragma once
#include <cassert>
#include "service.h"

void testDomain() {
    Task t{ 1, "Descriere", "open", {"Ion", "Vasile"} };
    assert(t.getId() == 1);
    assert(t.getDescriere() == "Descriere");
    assert(t.getStare() == "open");
    assert(t.getProgramatori().size() == 2);

    t.setStare("closed");
    assert(t.getStare() == "closed");
}

void testAll() {
    testDomain();
}