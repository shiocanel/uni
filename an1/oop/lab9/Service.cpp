#include "Service.h"
#include "UndoAdauga.h"
#include "UndoSterge.h"
#include "UndoModifica.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

Service::Service(std::string filename)
    : repo(std::move(filename)) {
}

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
    undoActions.push_back(std::make_unique<UndoAdauga>(repo, titluCurat));
}

void Service::stergeFilm(const std::string& titlu) {
    const std::string titluCurat = trim(titlu);
    validateText(titluCurat, "Titlul");

    Film filmSters = repo.getByTitlu(titluCurat);
    repo.removeFilm(titluCurat);
    undoActions.push_back(std::make_unique<UndoSterge>(repo, filmSters));
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

    Film filmVechi = repo.getByTitlu(titluVechiCurat);
    Film filmNou(titluNouCurat, genNouCurat, anNou, actorNouCurat);

    repo.updateFilm(titluVechiCurat, filmNou);
    undoActions.push_back(std::make_unique<UndoModifica>(repo, titluNouCurat, filmVechi));
}

void Service::undo() {
    if (undoActions.empty()) {
        throw std::runtime_error("Nu mai exista operatii de anulat.");
    }

    undoActions.back()->doUndo();
    undoActions.pop_back();
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

    std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rezultat),
        [&fragmentCurat](const Film& film) {
            return film.getTitlu().find(fragmentCurat) != std::string::npos;
        });

    return rezultat;
}

Service::FilmView Service::filtreazaDupaAn(int an) const {
    validateYear(an);

    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rezultat),
        [an](const Film& film) {
            return film.getAnAparitie() == an;
        });

    return rezultat;
}

Service::FilmView Service::sorteazaDupaTitlu() const {
    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    std::transform(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rezultat),
        [](const Film& film) {
            return std::cref(film);
        });

    std::sort(rezultat.begin(), rezultat.end(),
        [](const std::reference_wrapper<const Film>& a, const std::reference_wrapper<const Film>& b) {
            return a.get().getTitlu() < b.get().getTitlu();
        });

    return rezultat;
}

Service::FilmView Service::sorteazaDupaActor() const {
    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    std::transform(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rezultat),
        [](const Film& film) {
            return std::cref(film);
        });

    std::sort(rezultat.begin(), rezultat.end(),
        [](const std::reference_wrapper<const Film>& a, const std::reference_wrapper<const Film>& b) {
            return a.get().getActorPrincipal() < b.get().getActorPrincipal();
        });

    return rezultat;
}

Service::FilmView Service::sorteazaDupaAnSiGen() const {
    FilmView rezultat;
    rezultat.reserve(repo.getAll().size());

    std::transform(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rezultat),
        [](const Film& film) {
            return std::cref(film);
        });

    std::sort(rezultat.begin(), rezultat.end(),
        [](const std::reference_wrapper<const Film>& a, const std::reference_wrapper<const Film>& b) {
            if (a.get().getAnAparitie() != b.get().getAnAparitie()) {
                return a.get().getAnAparitie() < b.get().getAnAparitie();
            }
            return a.get().getGen() < b.get().getGen();
        });

    return rezultat;
}