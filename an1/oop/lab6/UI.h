#pragma once
#include "Service.h"

class UI {
private:
    Service service;

    static void afiseazaFilm(const Film& film);
    static void afiseazaFilme(const std::vector<Film>& filme);
    static void afiseazaFilme(const Service::FilmView& filme);

    static std::string citesteText(const std::string& mesaj);
    static int citesteInt(const std::string& mesaj);

    static void afiseazaMeniu();

public:
    void run();
};
