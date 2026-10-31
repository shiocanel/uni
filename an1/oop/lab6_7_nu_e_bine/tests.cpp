#include "tests.h"
#include <cassert>
#include <iostream>

void testVector() {
    VectorDinamic<Movie> v;
    v.push_back(Movie("A", "B", 2000, "C"));
    v.push_back(Movie("X", "Y", 2010, "Z"));
    assert(v.size() == 2);
    assert(v[0].getTitle() == "A");

    VectorDinamic<Movie> v2 = v;
    assert(v2.size() == 2);
    assert(v2[0].getTitle() == "A");

    v.erase(0);
    assert(v.size() == 1);
    assert(v[0].getTitle() == "X");
}

void testDomain() {
    Movie m("Dune", "Sci-Fi", 2021, "Timothee");
    assert(m.getTitle() == "Dune");
    assert(m.getGenre() == "Sci-Fi");
    assert(m.getReleaseYear() == 2021);
    assert(m.getMainActor() == "Timothee");

    Movie mCopy = m;
    assert(mCopy.getTitle() == "Dune");

    m.setTitle("Dune 2");
    assert(m.getTitle() == "Dune 2");
}

void testValidator() {
    try {
        MovieValidator::validate("", "", 1800, "");
        assert(false);
    }
    catch (const ValidationException& ve) {
        assert(ve.getMessage().find("Titlul") != std::string::npos);
        assert(ve.getMessage().find("Anul") != std::string::npos);
    }
}

void testRepository() {
    Repository repo;
    Movie m1("Inception", "Sci-Fi", 2010, "Leo");

    repo.store(m1);
    assert(repo.getAll().size() == 1);

    try {
        repo.store(m1);
        assert(false);
    }
    catch (const RepoException& re) {
        assert(re.getMessage() != "");
    }

    assert(repo.find("Inception") == 0);
    assert(repo.find("Batman") == -1);

    Movie m2("Inception Updated", "Action", 2010, "Leo");
    repo.update("Inception", m2);
    assert(repo.getAll()[0].getTitle() == "Inception Updated");

    try {
        repo.update("NonExistent", m2);
        assert(false);
    }
    catch (const RepoException&) { assert(true); }

    repo.remove("Inception Updated");
    assert(repo.getAll().size() == 0);

    try {
        repo.remove("NonExistent");
        assert(false);
    }
    catch (const RepoException&) { assert(true); }
}

void testService() {
    Repository repo;
    Service srv(repo);

    srv.addMovie("Matrix", "Sci-Fi", 1999, "Keanu");
    srv.addMovie("John Wick", "Action", 2014, "Keanu");
    srv.addMovie("Avatar", "Sci-Fi", 2009, "Sam");

    assert(srv.getAllMovies().size() == 3);

    auto filtered = srv.filterByTitle("Matrix");
    assert(filtered.size() == 1);

    auto filteredYear = srv.filterByYear(2014);
    assert(filteredYear.size() == 1);

    auto sortedByTitle = srv.sortByTitle();
    assert(sortedByTitle[0].getTitle() == "Avatar");

    auto sortedByYear = srv.sortByYearAndGenre();
    assert(sortedByYear[0].getReleaseYear() == 1999);

    try {
        srv.addMovie("", "Action", 2020, "Actor");
        assert(false);
    }
    catch (const ValidationException&) { assert(true); }

    srv.deleteMovie("Avatar");
    assert(srv.getAllMovies().size() == 2);
}

void runAllTests() {
    testVector();
    testDomain();
    testValidator();
    testRepository();
    testService();
    std::cout << ">>> Toate testele din Iteratia 2 au trecut cu succes! <<<\n";
}