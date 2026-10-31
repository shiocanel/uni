#pragma once
#include <string>
#include <vector>
#include "Film.h"

class FilmRepository {
private:
    std::vector<Film> filme;
    std::string filename;

    void loadFromFile();
    void saveToFile() const;
    void seedDefaults();

public:
    explicit FilmRepository(std::string filename = "filme.txt");

    bool exists(const std::string& titlu) const;

    const Film& getByTitlu(const std::string& titlu) const;
    Film& getByTitlu(const std::string& titlu);

    void addFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor);
    void addFilm(const Film& film);

    void removeFilm(const std::string& titlu);
    void updateFilm(const std::string& titluCurent, const Film& filmNou);

    const std::vector<Film>& getAll() const noexcept;
};