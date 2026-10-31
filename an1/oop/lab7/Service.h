#pragma once
#include <functional>
#include <string>
#include "FilmRepository.h"
#include "VectorDinamic.h"

class Service {
public:
    using FilmView = VectorDinamic<std::reference_wrapper<const Film>>;

private:
    FilmRepository repo;

    static std::string trim(const std::string& text);
    static void validateText(const std::string& value, const std::string& fieldName);
    static void validateYear(int year);

public:
    void adaugaFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor);
    void stergeFilm(const std::string& titlu);
    void modificaFilm(const std::string& titluVechi,
        const std::string& titluNou,
        const std::string& genNou,
        int anNou,
        const std::string& actorNou);

    const Film& cautaFilm(const std::string& titlu) const;
    const VectorDinamic<Film>& getAll() const noexcept;

    FilmView filtreazaDupaTitlu(const std::string& fragment) const;
    FilmView filtreazaDupaAn(int an) const;

    FilmView sorteazaDupaTitlu() const;
    FilmView sorteazaDupaActor() const;
    FilmView sorteazaDupaAnSiGen() const;
};
