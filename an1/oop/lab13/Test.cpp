#include "Service.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>

template <typename Func>
static void expectThrow(Func&& f) {
    try {
        f();
        assert(false);
    }
    catch (...) {
        assert(true);
    }
}

static Service makeTestService(const std::string& fileName) {
    std::remove(fileName.c_str());
    return Service(fileName);
}

void testAdd() {
    Service srv = makeTestService("test_add.txt");

    srv.adaugaFilm("Film1", "Gen1", 2001, "Actor1");
    assert(srv.getAll().size() == 11);
    assert(srv.cautaFilm("Film1").getTitlu() == "Film1");

    expectThrow([&]() {
        srv.adaugaFilm("Film1", "Gen1", 2001, "Actor1");
        });
}

void testDelete() {
    Service srv = makeTestService("test_delete.txt");

    srv.stergeFilm("Titanic");
    assert(srv.getAll().size() == 9);

    expectThrow([&]() {
        srv.stergeFilm("FilmInexistent");
        });

    expectThrow([&]() {
        srv.cautaFilm("Titanic");
        });
}

void testModify() {
    Service srv = makeTestService("test_modify.txt");

    srv.modificaFilm("Titanic", "Titanic2", "Drama", 2000, "ActorNou");

    const Film& f = srv.cautaFilm("Titanic2");
    assert(f.getTitlu() == "Titanic2");
    assert(f.getGen() == "Drama");
    assert(f.getAnAparitie() == 2000);
    assert(f.getActorPrincipal() == "ActorNou");

    expectThrow([&]() {
        srv.cautaFilm("Titanic");
        });

    expectThrow([&]() {
        srv.modificaFilm("NuExista", "X", "Y", 2000, "Z");
        });
}

void testSearch() {
    Service srv = makeTestService("test_search.txt");

    const Film& f = srv.cautaFilm("Inception");
    assert(f.getTitlu() == "Inception");

    expectThrow([&]() {
        srv.cautaFilm("NuExista");
        });
}

void testFilterTitlu() {
    Service srv = makeTestService("test_filter_titlu.txt");

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
    Service srv = makeTestService("test_filter_an.txt");

    auto rez = srv.filtreazaDupaAn(2010);
    assert(!rez.empty());

    bool gasit = false;
    for (const auto& f : rez) {
        if (f.get().getTitlu() == "Inception") {
            gasit = true;
        }
    }
    assert(gasit);
}

void testSetters() {
    Film f("Initial", "Drama", 2000, "ActorInitial");

    f.setTitlu("TitluNou");
    assert(f.getTitlu() == "TitluNou");

    f.setGen("Comedie");
    assert(f.getGen() == "Comedie");

    f.setAnAparitie(2024);
    assert(f.getAnAparitie() == 2024);

    f.setActorPrincipal("ActorNou");
    assert(f.getActorPrincipal() == "ActorNou");
}

void testSortTitlu() {
    Service srv = makeTestService("test_sort_titlu.txt");

    auto rez = srv.sorteazaDupaTitlu();

    for (size_t i = 1; i < rez.size(); i++) {
        assert(rez[i - 1].get().getTitlu() <= rez[i].get().getTitlu());
    }
}

void testSortActor() {
    Service srv = makeTestService("test_sort_actor.txt");

    auto rez = srv.sorteazaDupaActor();

    for (size_t i = 1; i < rez.size(); i++) {
        assert(rez[i - 1].get().getActorPrincipal() <= rez[i].get().getActorPrincipal());
    }
}

void testSortAnGen() {
    Service srv = makeTestService("test_sort_an_gen.txt");

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
    Service srv = makeTestService("test_validation.txt");

    expectThrow([&]() {
        srv.adaugaFilm("", "Gen", 2000, "Actor");
        });

    expectThrow([&]() {
        srv.adaugaFilm("X", "Gen", 1000, "Actor");
        });

    expectThrow([&]() {
        srv.adaugaFilm("X", "", 2000, "Actor");
        });

    expectThrow([&]() {
        srv.adaugaFilm("X", "Gen", 2000, "");
        });
}

void testOutputOperator() {
    Film f("Test", "GenTest", 2000, "ActorTest");

    std::stringstream ss;
    ss << f;

    const std::string output = ss.str();

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
    assert(f2.getGen() == "B");
    assert(f2.getAnAparitie() == 2000);
    assert(f2.getActorPrincipal() == "C");
}

void testSortAnGenEdge() {
    Service srv = makeTestService("test_sort_edge.txt");

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

void testUndoAdd() {
    Service srv = makeTestService("test_undo_add.txt");

    srv.adaugaFilm("FilmX", "GenX", 2001, "ActorX");
    assert(srv.cautaFilm("FilmX").getTitlu() == "FilmX");

    srv.undo();

    expectThrow([&]() {
        srv.cautaFilm("FilmX");
        });
}

void testUndoDelete() {
    Service srv = makeTestService("test_undo_delete.txt");

    srv.stergeFilm("Titanic");
    expectThrow([&]() {
        srv.cautaFilm("Titanic");
        });

    srv.undo();
    assert(srv.cautaFilm("Titanic").getTitlu() == "Titanic");
}

void testUndoModify() {
    Service srv = makeTestService("test_undo_modify.txt");

    srv.modificaFilm("Titanic", "Titanic2", "DramaNoua", 2000, "ActorNou");
    assert(srv.cautaFilm("Titanic2").getAnAparitie() == 2000);

    srv.undo();

    const Film& f = srv.cautaFilm("Titanic");
    assert(f.getTitlu() == "Titanic");
    assert(f.getAnAparitie() == 1997);
    assert(f.getGen() == "Drama");
    assert(f.getActorPrincipal() == "Leonardo DiCaprio");
}

void testPersistence() {
    const std::string fileName = "test_persistence.txt";
    std::remove(fileName.c_str());

    {
        Service srv(fileName);
        srv.adaugaFilm("PersistFilm", "Drama", 2024, "ActorP");
        assert(srv.cautaFilm("PersistFilm").getTitlu() == "PersistFilm");
    }

    {
        Service srv(fileName);
        assert(srv.cautaFilm("PersistFilm").getTitlu() == "PersistFilm");
    }
}

void testCosAddRemove() {
    Service srv = makeTestService("test_cos.txt");

    srv.adaugaInCos("Titanic");
    assert(srv.getCos().getAll().size() == 1);

    srv.stergeDinCos("Titanic");
    assert(srv.getCos().getAll().empty());
}

void testCosGenerate() {
    Service srv = makeTestService("test_cos_generate.txt");

    srv.genereazaCos(3);
    assert(srv.getCos().getAll().size() == 3);
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
    testSetters();
    testCopyConstructor();
    testSortAnGenEdge();
    testUndoAdd();
    testUndoDelete();
    testUndoModify();
    testPersistence();
    testCosGenerate();
    testCosAddRemove();

    std::cout << "ALL TESTS PASSED\n";
}