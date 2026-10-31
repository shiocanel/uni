#pragma once

#include <string>
#include <vector>

#include "Film.h"
#include "FilmRepository.h"
#include "Observer.h"

class CosFilm {
private:
    FilmRepository& repo;
    std::vector<Film> filme;
    std::vector<CosObserver*> observers;

    void notify();

public:
    explicit CosFilm(FilmRepository& repo);

    void addObserver(CosObserver* obs);
    void removeObserver(CosObserver* obs);

    const std::vector<Film>& getAll() const noexcept;

    void adaugaFilm(const std::string& titlu);
    void stergeFilm(const std::string& titlu);
    void golesteCos();
    void genereaza(int nr);
};