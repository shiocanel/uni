#include "UI.h"
#include <iostream>

using namespace std;

UI::UI(Service& srv) : srv(srv) {}

void UI::printMenu() const {
    cout << "\n1. Add Movie\n";
    cout << "2. Print All\n";
    cout << "3. Delete Movie\n";
    cout << "4. Filter By Title\n";
    cout << "5. Filter By Year\n";
    cout << "6. Sort by Title\n";
    cout << "7. Sort by Actor\n";
    cout << "8. Sort by Year And Genre\n";
    cout << "0. Exit\n";
    cout << "Option: ";
}

void UI::uiPrint(const std::vector<Movie>& movies) const {
    cout << "==Movies==\n\n";
    for (const auto& m : movies)
        cout << m.getTitle() << " | " << m.getGenre() << " | " << m.getReleaseYear() << " | " << m.getMainActor() << "\n";
    
    cout << "\n==Movies==\n";
}

void UI::run() {
    int cmd = -1;

    while (cmd != 0) {
        printMenu();
        cin >> cmd;

        try {
            if (cmd == 1) {
                string title, genre, actor;
                int year;
                cout << "Title: ";
                cin >> title;
                cout << "Genre: ";
                cin >> genre;
                cout << "Year: ";
                cin >> year;
                cout << "Main Actor: ";
                cin >> actor;

                if (srv.addMovie(title, genre, year, actor))
                    cout << "Movie added successfully\n";
                else
                    cout << "Failed to add :(\n";
            }
            else if (cmd == 2)
                uiPrint(srv.getAllMovies());
            else if (cmd == 3) {
                cout << "Movie to delete (Title): ";
                string title;
                cin >> title;

                if (srv.deleteMovie(title))
                    cout << "Removed successfully!!\n";
                else
                    cout << "Failed to remove :(\n";
            }
            else if (cmd == 4) {
                string title;
                cout << "Title to filter: ";
                cin >> title;

                uiPrint(srv.filterByTitle(title));
            }
            else if (cmd == 5) {
                int year;
                cout << "Year to filter: ";
                cin >> year;

                uiPrint(srv.filterByYear(year));
            }
            else if (cmd == 6)
                uiPrint(srv.sortByTitle());
            else if (cmd == 7)
                uiPrint(srv.sortByActor());
            else if (cmd == 8)
                uiPrint(srv.sortByYearAndGenre());
            else if (cmd == 0)
                cout << "Sa fie cu sanatate!!\n";
            else
                cout << "Invalid command.\n";
        }
        catch (const RepoException& re) {
            cout << "Eroare Repository: " << re.getMessage() << "\n";
        }
        catch (const ValidationException& ve) {
            cout << "Eroare Validare: \n" << ve.getMessage() << "\n";
        }
    }
}