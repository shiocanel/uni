#include "CosFilm.h"

#include <algorithm>
#include <random>
#include <stdexcept>

CosFilm::CosFilm(FilmRepository& repo)
    : repo(repo) {
}

void CosFilm::addObserver(CosObserver* obs) {
    if (!obs) {
        return;
    }

    if (std::find(observers.begin(), observers.end(), obs) == observers.end()) {
        observers.push_back(obs);
    }
}

void CosFilm::removeObserver(CosObserver* obs) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), obs),
        observers.end()
    );
}

void CosFilm::notify() {
    for (auto* obs : observers) {
        if (obs) {
            obs->updateCos();
        }
    }
}

const std::vector<Film>& CosFilm::getAll() const noexcept {
    return filme;
}

void CosFilm::adaugaFilm(const std::string& titlu) {
    const Film& film = repo.getByTitlu(titlu);

    auto it = std::find_if(filme.begin(), filme.end(),
        [&titlu](const Film& f) {
            return f.getTitlu() == titlu;
        });

    if (it != filme.end()) {
        throw std::runtime_error("Film deja existent in cos.");
    }

    filme.push_back(film);
    notify();
}

void CosFilm::stergeFilm(const std::string& titlu) {
    auto it = std::find_if(filme.begin(), filme.end(),
        [&titlu](const Film& f) {
            return f.getTitlu() == titlu;
        });

    if (it == filme.end()) {
        throw std::runtime_error("Film inexistent in cos.");
    }

    filme.erase(it);
    notify();
}

void CosFilm::golesteCos() {
    filme.clear();
    notify();
}

void CosFilm::genereaza(int nr) {
    if (nr < 0) {
        throw std::runtime_error("Numarul de filme trebuie sa fie pozitiv.");
    }

    const auto& all = repo.getAll();
    if (all.empty()) {
        throw std::runtime_error("Nu exista filme in repository.");
    }

    if (static_cast<size_t>(nr) > all.size()) {
        throw std::runtime_error("Nu exista suficiente filme pentru generare.");
    }

    filme.clear();

    std::vector<int> poz(all.size());
    for (int i = 0; i < static_cast<int>(all.size()); ++i) {
        poz[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(poz.begin(), poz.end(), gen);

    for (int i = 0; i < nr; ++i) {
        filme.push_back(all[poz[i]]);
    }

    notify();
}