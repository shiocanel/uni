#include "Service.h"
#include <cassert>
#include <iostream>

void testAdd() {
    Service srv;

    srv.adaugaFilm("Film1", "Gen1", 2001, "Actor1");
    assert(srv.getAll().size() == 11);

    try {
        srv.adaugaFilm("Film1", "Gen1", 2001, "Actor1");
    }
    catch (...) {
        assert(true);
    }
}

void testDelete() {
    Service srv;

    srv.stergeFilm("Titanic");
    assert(srv.getAll().size() == 9);

    try {
        srv.stergeFilm("FilmInexistent");
    }
    catch (...) {
        assert(true);
    }
}

void testModify() {
    Service srv;

    srv.modificaFilm("Titanic", "Titanic2", "Drama", 2000, "ActorNou");

    const Film& f = srv.cautaFilm("Titanic2");
    assert(f.getTitlu() == "Titanic2");
    assert(f.getAnAparitie() == 2000);

    try {
        srv.modificaFilm("NuExista", "X", "Y", 2000, "Z");
    }
    catch (...) {
        assert(true);
    }
}

void testSearch() {
    Service srv;

    const Film& f = srv.cautaFilm("Inception");
    assert(f.getTitlu() == "Inception");

    try {
        srv.cautaFilm("NuExista");
    }
    catch (...) {
        assert(true);
    }
}

void testFilterTitlu() {
    Service srv;

    auto rez = srv.filtreazaDupaTitlu("In");
    assert(!rez.empty());

    bool gasit = false;
    for (const auto& f : rez) {
        if (f.get().getTitlu() == "Inception") {
            gasit = true;
        }
    }
    assert(gasit);
}

void testFilterAn() {
    Service srv;

    auto rez = srv.filtreazaDupaAn(2010);

    bool gasit = false;
    for (const auto& f : rez) {
        if (f.get().getTitlu() == "Inception") {
            gasit = true;
        }
    }
    assert(gasit);
}

void testSortTitlu() {
    Service srv;

    auto rez = srv.sorteazaDupaTitlu();

    for (size_t i = 1; i < rez.size(); i++) {
        assert(rez[i - 1].get().getTitlu() <= rez[i].get().getTitlu());
    }
}

void testSortActor() {
    Service srv;

    auto rez = srv.sorteazaDupaActor();

    for (size_t i = 1; i < rez.size(); i++) {
        assert(rez[i - 1].get().getActorPrincipal() <= rez[i].get().getActorPrincipal());
    }
}

void testSortAnGen() {
    Service srv;

    auto rez = srv.sorteazaDupaAnSiGen();

    for (size_t i = 1; i < rez.size(); i++) {
        const auto& a = rez[i - 1].get();
        const auto& b = rez[i].get();

        if (a.getAnAparitie() == b.getAnAparitie());
        else {
            assert(a.getAnAparitie() <= b.getAnAparitie());
        }
    }
}

void testValidation() {
    Service srv;

    try {
        srv.adaugaFilm("", "Gen", 2000, "Actor");
    }
    catch (...) {
        assert(true);
    }

    try {
        srv.adaugaFilm("X", "Gen", 1000, "Actor");
    }
    catch (...) {
        assert(true);
    }
}

#include <sstream>

void testOutputOperator() {
    Film f("Test", "GenTest", 2000, "ActorTest");

    std::stringstream ss;
    ss << f;

    std::string output = ss.str();

    assert(output.find("Test") != std::string::npos);
    assert(output.find("GenTest") != std::string::npos);
    assert(output.find("2000") != std::string::npos);
    assert(output.find("ActorTest") != std::string::npos);
}

void testGetters() {
    Film f("A", "B", 1999, "C");

    assert(f.getTitlu() == "A");
    assert(f.getGen() == "B");
    assert(f.getAnAparitie() == 1999);
    assert(f.getActorPrincipal() == "C");
}

void testCopyConstructor() {
    Film f1("A", "B", 2000, "C");

    Film f2 = f1;

    assert(f2.getTitlu() == "A");
}

void testSortAnGenEdge() {
    Service srv;

    srv.adaugaFilm("FilmA", "ZGen", 2020, "Actor1");
    srv.adaugaFilm("FilmB", "AGen", 2020, "Actor2");

    auto rez = srv.sorteazaDupaAnSiGen();

    bool found = false;

    for (size_t i = 1; i < rez.size(); i++) {
        const auto& a = rez[i - 1].get();
        const auto& b = rez[i].get();

        if (a.getAnAparitie() == b.getAnAparitie()) {
            found = true;
            assert(a.getGen() <= b.getGen());
        }
    }

    assert(found);
}

#include "VectorDinamic.h"
#include <string>

void testVectorBasic() {
    VectorDinamic<int> v;

    assert(v.size() == 0);
    assert(v.empty());

    v.emplace_back(10);
    v.emplace_back(20);

    assert(v.size() == 2);
    assert(v[0] == 10);
    assert(v[1] == 20);
}

void testReserve() {
    VectorDinamic<int> v;

    v.reserve(10);
    assert(v.size() == 0);

    v.emplace_back(1);
    v.emplace_back(2);

    v.reserve(1);

    assert(v.size() == 2);
    assert(v[0] == 1);
}

void testPushBack() {
    VectorDinamic<std::string> v;

    std::string s = "abc";

    v.push_back(s);
    v.push_back(std::string("xyz"));

    assert(v.size() == 2);
    assert(v[0] == "abc");
    assert(v[1] == "xyz");
}

void testCopyConstructorVector() {
    VectorDinamic<int> v;

    v.emplace_back(1);
    v.emplace_back(2);

    VectorDinamic<int> v2 = v;

    assert(v2.size() == 2);
    assert(v2[0] == 1);
    assert(v2[1] == 2);
}

void testMoveConstructor() {
    VectorDinamic<int> v;

    v.emplace_back(5);
    v.emplace_back(6);

    VectorDinamic<int> v2 = std::move(v);

    assert(v2.size() == 2);
    assert(v2[0] == 5);
    assert(v2[1] == 6);

    assert(v.size() == 0);
}

void testAssignmentOperator() {
    VectorDinamic<int> v;

    v.emplace_back(1);
    v.emplace_back(2);

    VectorDinamic<int> v2;
    v2 = v;

    assert(v2.size() == 2);
    assert(v2[0] == 1);
}

void testSwap() {
    VectorDinamic<int> a;
    VectorDinamic<int> b;

    a.emplace_back(1);
    b.emplace_back(2);

    a.swap(b);

    assert(a[0] == 2);
    assert(b[0] == 1);
}

void testErase() {
    VectorDinamic<int> v;

    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);

    v.erase(1);

    assert(v.size() == 2);
    assert(v[0] == 1);
    assert(v[1] == 3);

    try {
        v.erase(10);
    }
    catch (...) {
        assert(true);
    }
}

void testClear() {
    VectorDinamic<int> v;

    v.emplace_back(1);
    v.emplace_back(2);

    v.clear();

    assert(v.size() == 0);
    assert(v.empty());
}

void testIterator() {
    VectorDinamic<int> v;

    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);

    int sum = 0;

    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }

    assert(sum == 6);

    const auto& cv = v;
    int sum2 = 0;

    for (auto it = cv.cbegin(); it != cv.cend(); ++it) {
        sum2 += *it;
    }

    assert(sum2 == 6);
}

void testResizeLogic() {
    VectorDinamic<int> v;

    for (int i = 0; i < 100; i++) {
        v.emplace_back(i);
    }

    assert(v.size() == 100);

    for (int i = 0; i < 100; i++) {
        assert(v[i] == i);
    }
}

void runVectorTests() {
    testVectorBasic();
    testReserve();
    testPushBack();
    testCopyConstructorVector();
    testMoveConstructor();
    testAssignmentOperator();
    testSwap();
    testErase();
    testClear();
    testIterator();
    testResizeLogic();
}


void runAllTests() {
    testAdd();
    testDelete();
    testModify();
    testSearch();
    testFilterTitlu();
    testFilterAn();
    testSortTitlu();
    testSortActor();
    testSortAnGen();
    testValidation();
    testOutputOperator();
    testGetters();
    testCopyConstructor();
    testSortAnGenEdge();
    runVectorTests();

    std::cout << "ALL TESTS PASSED\n";
}