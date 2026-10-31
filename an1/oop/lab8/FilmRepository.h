#pragma once
#include <string>
#include <vector>
#include "Film.h"

class FilmRepository {
private:
    std::vector<Film> filme;

public:
    FilmRepository();

    bool exists(const std::string& titlu) const;

    const Film& getByTitlu(const std::string& titlu) const;
    Film& getByTitlu(const std::string& titlu);

    void addFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor);
    void removeFilm(const std::string& titlu);

    const std::vector<Film>& getAll() const noexcept;
};