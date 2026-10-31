#include "Service.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

std::string Service::trim(const std::string& text) {
    const auto start = text.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }

    const auto end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

void Service::validateText(const std::string& value, const std::string& fieldName) {
    if (trim(value).empty()) {
        throw std::runtime_error(fieldName + " nu poate fi gol.");
    }
}

void Service::validateYear(int year) {
    if (year < 1888 || year > 2100) {
        throw std::runtime_error("Anul aparitiei este invalid.");
    }
}

void Service::adaugaFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor) {
    const std::string titluCurat = trim(titlu);
    const std::string genCurat = trim(gen);
    const std::string actorCurat = trim(actor);

    validateText(titluCurat, "Titlul");
    validateText(genCurat, "Genul");
    validateText(actorCurat, "Actorul principal");
    validateYear(an);

    repo.addFilm(titluCurat, genCurat, an, actorCurat);
}

void Service::stergeFilm(const std::string& titlu) {
    const std::string titluCurat = trim(titlu);
    validateText(titluCurat, "Titlul");

    repo.removeFilm(titluCurat);
}

void Service::modificaFilm(const std::string& titluVechi,
    const std::string& titluNou,
    const std::string& genNou,
    int anNou,
    const std::string& actorNou) {
    const std::string titluVechiCurat = trim(titluVechi);
    const std::string titluNouCurat = trim(titluNou);
    const std::string genNouCurat = trim(genNou);
    const std::string actorNouCurat = trim(actorNou);

    validateText(titluVechiCurat, "Titlul vechi");
    validateText(titluNouCurat, "Titlul nou");
    validateText(genNouCurat, "Genul nou");
    validateText(actorNouCurat, "Actorul principal nou");
    validateYear(anNou);

    Film& film = repo.getByTitlu(titluVechiCurat);

    if (titluNouCurat != titluVechiCurat && repo.exists(titluNouCurat)) {
        throw std::runtime_error("Exista deja un film cu noul titlu.");
    }

    film.setTitlu(titluNouCurat);
    film.setGen(genNouCurat);
    film.setAnAparitie(anNou);
    film.setActorPrincipal(actorNouCurat);
}

const Film& Service::cautaFilm(const std::string& titlu) const {
    const std::string titluCurat = trim(titlu);
    validateText(titluCurat, "Titlul");

    return repo.getByTitlu(titluCurat);
}

const std::vector<Film>& Service::getAll() const noexcept {
    return repo.getAll();
}

Service::FilmView Service::filtreazaDupaTitlu(const std::string& fragment) const {
    const std::string fragmentCurat = trim(fragment);
    validateText(fragmentCurat, "Fragmentul pentru titlu");

    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    for (const auto& film : repo.getAll()) {
        if (film.getTitlu().find(fragmentCurat) != std::string::npos) {
            rezultat.emplace_back(std::cref(film));
        }
    }

    return rezultat;
}

Service::FilmView Service::filtreazaDupaAn(int an) const {
    validateYear(an);

    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    for (const auto& film : repo.getAll()) {
        if (film.getAnAparitie() == an) {
            rezultat.emplace_back(std::cref(film));
        }
    }

    return rezultat;
}

Service::FilmView Service::sorteazaDupaTitlu() const {
    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    for (const auto& film : repo.getAll()) {
        rezultat.emplace_back(std::cref(film));
    }

    std::sort(rezultat.begin(), rezultat.end(),
        [](const std::reference_wrapper<const Film>& a, const std::reference_wrapper<const Film>& b) {
            return a.get().getTitlu() < b.get().getTitlu();
        });

    return rezultat;
}

Service::FilmView Service::sorteazaDupaActor() const {
    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    for (const auto& film : repo.getAll()) {
        rezultat.emplace_back(std::cref(film));
    }

    std::sort(rezultat.begin(), rezultat.end(),
        [](const std::reference_wrapper<const Film>& a, const std::reference_wrapper<const Film>& b) {
            return a.get().getActorPrincipal() < b.get().getActorPrincipal();
        });

    return rezultat;
}

Service::FilmView Service::sorteazaDupaAnSiGen() const {
    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    for (const auto& film : repo.getAll()) {
        rezultat.emplace_back(std::cref(film));
    }

    std::sort(rezultat.begin(), rezultat.end(),
        [](const std::reference_wrapper<const Film>& a, const std::reference_wrapper<const Film>& b) {
            if (a.get().getAnAparitie() != b.get().getAnAparitie()) {
                return a.get().getAnAparitie() < b.get().getAnAparitie();
            }
            return a.get().getGen() < b.get().getGen();
        });

    return rezultat;
}
