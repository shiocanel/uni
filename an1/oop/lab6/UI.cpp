#include "UI.h"
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

using namespace std;

void UI::afiseazaFilm(const Film& film) {
    cout << film << '\n';
}

void UI::afiseazaFilme(const vector<Film>& filme) {
    if (filme.empty()) {
        cout << "Nu exista filme.\n";
        return;
    }

    for (const auto& film : filme) {
        cout << film << '\n';
    }
}

void UI::afiseazaFilme(const Service::FilmView& filme) {
    if (filme.empty()) {
        cout << "Nu exista filme.\n";
        return;
    }

    for (const auto& filmRef : filme) {
        cout << filmRef.get() << '\n';
    }
}

string UI::citesteText(const string& mesaj) {
    cout << mesaj;
    string text;
    getline(cin, text);
    return text;
}

int UI::citesteInt(const string& mesaj) {
    while (true) {
        cout << mesaj;
        string line;
        getline(cin, line);

        try {
            size_t pos = 0;
            int value = stoi(line, &pos);
            if (pos != line.size()) {
                throw invalid_argument("Caractere suplimentare.");
            }
            return value;
        }
        catch (...) {
            cout << "Valoare invalida. Incercati din nou.\n";
        }
    }
}

void UI::afiseazaMeniu() {
    cout << "\n=== MENIU ===\n";
    cout << "1. Adauga film\n";
    cout << "2. Sterge film\n";
    cout << "3. Modifica film\n";
    cout << "4. Afiseaza toate filmele\n";
    cout << "5. Cauta film dupa titlu\n";
    cout << "6. Filtreaza filme dupa titlu\n";
    cout << "7. Filtreaza filme dupa an\n";
    cout << "8. Sorteaza dupa titlu\n";
    cout << "9. Sorteaza dupa actor\n";
    cout << "10. Sorteaza dupa an si gen\n";
    cout << "0. Iesire\n";
    cout << "Optiunea ta: ";
}

void UI::run() {
    bool ruleaza = true;

    while (ruleaza) {
        afiseazaMeniu();

        string optiuneText;
        getline(cin, optiuneText);

        int optiune = -1;
        try {
            size_t pos = 0;
            optiune = stoi(optiuneText, &pos);
            if (pos != optiuneText.size()) {
                throw invalid_argument("Input invalid.");
            }
        }
        catch (...) {
            cout << "Optiune invalida.\n";
            continue;
        }

        try {
            if (optiune == 1) {
                const auto titlu = citesteText("Titlu: ");
                const auto gen = citesteText("Gen: ");
                const int an = citesteInt("An aparitie: ");
                const auto actor = citesteText("Actor principal: ");
                service.adaugaFilm(titlu, gen, an, actor);
                cout << "Film adaugat cu succes.\n";
            }
            else if (optiune == 2) {
                const auto titlu = citesteText("Titlu film de sters: ");
                service.stergeFilm(titlu);
                cout << "Film sters cu succes.\n";
            }
            else if (optiune == 3) {
                const auto titluVechi = citesteText("Titlu film de modificat: ");
                const auto titluNou = citesteText("Titlu nou: ");
                const auto genNou = citesteText("Gen nou: ");
                const int anNou = citesteInt("An nou: ");
                const auto actorNou = citesteText("Actor principal nou: ");
                service.modificaFilm(titluVechi, titluNou, genNou, anNou, actorNou);
                cout << "Film modificat cu succes.\n";
            }
            else if (optiune == 4) {
                afiseazaFilme(service.getAll());
            }
            else if (optiune == 5) {
                const auto titlu = citesteText("Titlu cautat: ");
                const Film& film = service.cautaFilm(titlu);
                afiseazaFilm(film);
            }
            else if (optiune == 6) {
                const auto fragment = citesteText("Fragment titlu: ");
                auto rezultate = service.filtreazaDupaTitlu(fragment);
                afiseazaFilme(rezultate);
            }
            else if (optiune == 7) {
                const int an = citesteInt("An: ");
                auto rezultate = service.filtreazaDupaAn(an);
                afiseazaFilme(rezultate);
            }
            else if (optiune == 8) {
                auto rezultate = service.sorteazaDupaTitlu();
                afiseazaFilme(rezultate);
            }
            else if (optiune == 9) {
                auto rezultate = service.sorteazaDupaActor();
                afiseazaFilme(rezultate);
            }
            else if (optiune == 10) {
                auto rezultate = service.sorteazaDupaAnSiGen();
                afiseazaFilme(rezultate);
            }
            else if (optiune == 0) {
                ruleaza = false;
            }
            else {
                cout << "Optiune inexistenta.\n";
            }
        }
        catch (const exception& ex) {
            cout << "Eroare: " << ex.what() << '\n';
        }
    }
}
