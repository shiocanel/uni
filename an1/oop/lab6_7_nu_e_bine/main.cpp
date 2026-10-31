#include "UI.h"
#include "service.h"
#include "tests.h"
#include <iostream>

int main() {
    runAllTests();

    Repository repo;
    Service srv(repo);

    srv.addMovie("Inception", "Sci-Fi", 2010, "Leonardo DiCaprio");
    srv.addMovie("The Dark Knight", "Action", 2008, "Christian Bale");
    srv.addMovie("Interstellar", "Drama", 2014, "Matthew McConaughey");
    srv.addMovie("The Matrix", "Sci-Fi", 1999, "Keanu Reeves");
    srv.addMovie("Pulp Fiction", "Crime", 1994, "John Travolta");

    UI ui(srv);

    // core guideline checkers (un int x)
    // constructor de copiere practic 0 (un cout)

    //ui.run();

    //int x;

    return 0;
}