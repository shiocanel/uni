#include "FilmRepository.h"
#include <algorithm>
#include <stdexcept>

FilmRepository::FilmRepository() {
    filme.emplace_back("Inception", "SF", 2010, "Leonardo DiCaprio");
    filme.emplace_back("Titanic", "Drama", 1997, "Leonardo DiCaprio");
    filme.emplace_back("The Dark Knight", "Action", 2008, "Christian Bale");
    filme.emplace_back("Interstellar", "SF", 2014, "Matthew McConaughey");
    filme.emplace_back("Gladiator", "Action", 2000, "Russell Crowe");
    filme.emplace_back("Joker", "Drama", 2019, "Joaquin Phoenix");
    filme.emplace_back("Avengers", "Action", 2012, "Robert Downey Jr.");
    filme.emplace_back("Matrix", "SF", 1999, "Keanu Reeves");
    filme.emplace_back("Forrest Gump", "Drama", 1994, "Tom Hanks");
    filme.emplace_back("The Godfather", "Crime", 1972, "Al Pacino");
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

void FilmRepository::addFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor) {
    if (exists(titlu)) {
        throw std::runtime_error("Exista deja un film cu acest titlu.");
    }

    filme.emplace_back(titlu, gen, an, actor);
}

void FilmRepository::removeFilm(const std::string& titlu) {
    auto it = std::find_if(filme.begin(), filme.end(),
        [&titlu](const Film& film) {
            return film.getTitlu() == titlu;
        });

    if (it == filme.end()) {
        throw std::runtime_error("Film inexistent.");
    }

    filme.erase(it);
}

const std::vector<Film>& FilmRepository::getAll() const noexcept {
    return filme;
}
