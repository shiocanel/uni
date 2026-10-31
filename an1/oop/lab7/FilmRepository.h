#pragma once
#include <string>
#include "Film.h"
#include "VectorDinamic.h"

class FilmRepository {
private:
    VectorDinamic<Film> filme;

public:
    FilmRepository();

    bool exists(const std::string& titlu) const;

    const Film& getByTitlu(const std::string& titlu) const;
    Film& getByTitlu(const std::string& titlu);

    void addFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor);
    void removeFilm(const std::string& titlu);

    const VectorDinamic<Film>& getAll() const noexcept;
};
