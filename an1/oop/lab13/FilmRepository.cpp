#include "FilmRepository.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

FilmRepository::FilmRepository(std::string filename)
    : filename(std::move(filename)) {
    loadFromFile();

    if (filme.empty()) {
        seedDefaults();
        saveToFile();
    }
}

void FilmRepository::seedDefaults() {
    filme = {
        {"Inception", "SF", 2010, "Leonardo DiCaprio"},
        {"Titanic", "Drama", 1997, "Leonardo DiCaprio"},
        {"The Dark Knight", "Action", 2008, "Christian Bale"},
        {"Interstellar", "SF", 2014, "Matthew McConaughey"},
        {"Gladiator", "Action", 2000, "Russell Crowe"},
        {"Joker", "Drama", 2019, "Joaquin Phoenix"},
        {"Avengers", "Action", 2012, "Robert Downey Jr."},
        {"Matrix", "SF", 1999, "Keanu Reeves"},
        {"Forrest Gump", "Drama", 1994, "Tom Hanks"},
        {"The Godfather", "Crime", 1972, "Al Pacino"}
    };
}

void FilmRepository::loadFromFile() {
    filme.clear();

    std::ifstream in(filename);
    if (!in.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string titlu, gen, anText, actor;

        if (!std::getline(ss, titlu, ';')) continue;
        if (!std::getline(ss, gen, ';')) continue;
        if (!std::getline(ss, anText, ';')) continue;
        if (!std::getline(ss, actor)) continue;

        try {
            int an = std::stoi(anText);
            filme.emplace_back(titlu, gen, an, actor);
        }
        catch (...) {
        }
    }
}

void FilmRepository::saveToFile() const {
    std::ofstream out(filename, std::ios::trunc);

    for (const auto& film : filme) {
        out << film.getTitlu() << ';'
            << film.getGen() << ';'
            << film.getAnAparitie() << ';'
            << film.getActorPrincipal() << '\n';
    }
}

bool FilmRepository::exists(const std::string& titlu) const {
    return std::any_of(filme.begin(), filme.end(),
        [&titlu](const Film& film) {
            return film.getTitlu() == titlu;
        });
}

const Film& FilmRepository::getByTitlu(const std::string& titlu) const {
    auto it = std::find_if(filme.begin(), filme.end(),
        [&titlu](const Film& film) {
            return film.getTitlu() == titlu;
        });

    if (it == filme.end()) {
        throw std::runtime_error("Film inexistent.");
    }

    return *it;
}

Film& FilmRepository::getByTitlu(const std::string& titlu) {
    auto it = std::find_if(filme.begin(), filme.end(),
        [&titlu](const Film& film) {
            return film.getTitlu() == titlu;
        });

    if (it == filme.end()) {
        throw std::runtime_error("Film inexistent.");
    }

    return *it;
}

void FilmRepository::addFilm(const Film& film) {
    if (exists(film.getTitlu())) {
        throw std::runtime_error("Exista deja un film cu acest titlu.");
    }

    filme.push_back(film);
    saveToFile();
}

void FilmRepository::addFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor) {
    addFilm(Film{ titlu, gen, an, actor });
}

void FilmRepository::removeFilm(const std::string& titlu) {
    auto it = std::find_if(filme.begin(), filme.end(),
        [&titlu](const Film& film) {
            return film.getTitlu() == titlu;
        });

    if (it == filme.end()) {
        //throw std::runtime_error("Film inexistent.");
    }

    filme.erase(it);
    saveToFile();
}

void FilmRepository::updateFilm(const std::string& titluCurent, const Film& filmNou) {
    auto it = std::find_if(filme.begin(), filme.end(),
        [&titluCurent](const Film& film) {
            return film.getTitlu() == titluCurent;
        });

    if (it == filme.end()) {
        //throw std::runtime_error("Film inexistent.");
    }

    if (titluCurent != filmNou.getTitlu() && exists(filmNou.getTitlu())) {
        //throw std::runtime_error("Exista deja un film cu acest titlu.");
    }

    *it = filmNou;
    saveToFile();
}

const std::vector<Film>& FilmRepository::getAll() const noexcept {
    return filme;
}