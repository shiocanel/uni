#include "UI.h"
#include <iostream>
#include <string>
#include <stdexcept>

void UI::afiseazaFilm(const Film& film) {
    std::cout << film << '\n';
}

void UI::afiseazaFilme(const std::vector<Film>& filme) {
    if (filme.empty()) {
        std::cout << "Nu exista filme.\n";
        return;
    }

    for (const auto& film : filme) {
        std::cout << film << '\n';
    }
}

void UI::afiseazaFilme(const Service::FilmView& filme) {
    if (filme.empty()) {
        std::cout << "Nu exista filme.\n";
        return;
    }

    for (const auto& filmRef : filme) {
        std::cout << filmRef.get() << '\n';
    }
}

std::string UI::citesteText(const std::string& mesaj) {
    std::cout << mesaj;
    std::string text;
    std::getline(std::cin, text);
    return text;
}

int UI::citesteInt(const std::string& mesaj) {
    while (true) {
        std::cout << mesaj;
        std::string line;
        std::getline(std::cin, line);

        try {
            size_t pos = 0;
            int value = std::stoi(line, &pos);
            if (pos != line.size()) {
                throw std::invalid_argument("Caractere suplimentare.");
            }
            return value;
        }
        catch (...) {
            std::cout << "Valoare invalida. Incercati din nou.\n";
        }
    }
}

void UI::afiseazaMeniu() {
    std::cout << "\n=== MENIU ===\n";
    std::cout << "1. Adauga film\n";
    std::cout << "2. Sterge film\n";
    std::cout << "3. Modifica film\n";
    std::cout << "4. Afiseaza toate filmele\n";
    std::cout << "5. Cauta film dupa titlu\n";
    std::cout << "6. Filtreaza filme dupa titlu\n";
    std::cout << "7. Filtreaza filme dupa an\n";
    std::cout << "8. Sorteaza dupa titlu\n";
    std::cout << "9. Sorteaza dupa actor\n";
    std::cout << "10. Sorteaza dupa an si gen\n";
    std::cout << "11. Undo\n";
    std::cout << "0. Iesire\n";
    std::cout << "Optiunea ta: ";
}

void UI::run() {
    bool ruleaza = true;

    while (ruleaza) {
        afiseazaMeniu();

        std::string optiuneText;
        std::getline(std::cin, optiuneText);

        int optiune = -1;
        try {
            size_t pos = 0;
            optiune = std::stoi(optiuneText, &pos);
            if (pos != optiuneText.size()) {
                throw std::invalid_argument("Input invalid.");
            }
        }
        catch (...) {
            std::cout << "Optiune invalida.\n";
            continue;
        }

        try {
            switch (optiune) {
            case 1: {
                const auto titlu = citesteText("Titlu: ");
                const auto gen = citesteText("Gen: ");
                const int an = citesteInt("An aparitie: ");
                const auto actor = citesteText("Actor principal: ");
                service.adaugaFilm(titlu, gen, an, actor);
                std::cout << "Film adaugat cu succes.\n";
                break;
            }
            case 2: {
                const auto titlu = citesteText("Titlu film de sters: ");
                service.stergeFilm(titlu);
                std::cout << "Film sters cu succes.\n";
                break;
            }
            case 3: {
                const auto titluVechi = citesteText("Titlu film de modificat: ");
                const auto titluNou = citesteText("Titlu nou: ");
                const auto genNou = citesteText("Gen nou: ");
                const int anNou = citesteInt("An nou: ");
                const auto actorNou = citesteText("Actor principal nou: ");
                service.modificaFilm(titluVechi, titluNou, genNou, anNou, actorNou);
                std::cout << "Film modificat cu succes.\n";
                break;
            }
            case 4: {
                afiseazaFilme(service.getAll());
                break;
            }
            case 5: {
                const auto titlu = citesteText("Titlu cautat: ");
                const Film& film = service.cautaFilm(titlu);
                afiseazaFilm(film);
                break;
            }
            case 6: {
                const auto fragment = citesteText("Fragment titlu: ");
                auto rezultate = service.filtreazaDupaTitlu(fragment);
                afiseazaFilme(rezultate);
                break;
            }
            case 7: {
                const int an = citesteInt("An: ");
                auto rezultate = service.filtreazaDupaAn(an);
                afiseazaFilme(rezultate);
                break;
            }
            case 8: {
                auto rezultate = service.sorteazaDupaTitlu();
                afiseazaFilme(rezultate);
                break;
            }
            case 9: {
                auto rezultate = service.sorteazaDupaActor();
                afiseazaFilme(rezultate);
                break;
            }
            case 10: {
                auto rezultate = service.sorteazaDupaAnSiGen();
                afiseazaFilme(rezultate);
                break;
            }
            case 11: {
                service.undo();
                std::cout << "Operatie anulata cu succes.\n";
                break;
            }
            case 0:
                ruleaza = false;
                break;
            default:
                std::cout << "Optiune inexistenta.\n";
                break;
            }
        }
        catch (const std::exception& ex) {
            std::cout << "Eroare: " << ex.what() << '\n';
        }
    }
}