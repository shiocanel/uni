#pragma once
#include "repository.h"
#include <algorithm>
#include <set>

class ValidatorException : public exception {
private:
    vector<string> erori;
    string mesajComplet;
public:
    ValidatorException(const vector<string>& erori) : erori{ erori } {
        for (const auto& err : erori) mesajComplet += err + "\n";
    }
    const char* what() const noexcept override { return mesajComplet.c_str(); }
};

class Service {
private:
    Repository& repo;

public:
    Service(Repository& repo) : repo{ repo } {}

    vector<Tractor> getTractoareSortate() {
        auto tractoare = repo.getAll();
        sort(tractoare.begin(), tractoare.end(), [](const Tractor& a, const Tractor& b) {
            return a.getDenumire() < b.getDenumire();
            });
        return tractoare;
    }

    set<string> getTipuriDistincte() {
        set<string> tipuri;
        for (const auto& t : repo.getAll()) tipuri.insert(t.getTip());
        return tipuri;
    }

    void adaugaTractor(int id, string denumire, string tip, int numarRoti) {
        vector<string> erori;

        auto toate = repo.getAll();
        auto it = find_if(toate.begin(), toate.end(), [id](const Tractor& t) { return t.getId() == id; });
        if (it != toate.end()) erori.push_back("Id-ul exista deja!");

        if (denumire.empty()) erori.push_back("Denumirea nu poate fi vida!");
        if (tip.empty()) erori.push_back("Tipul nu poate fi vid!");

        if (numarRoti < 2 || numarRoti > 16 || numarRoti % 2 != 0) {
            erori.push_back("Numarul de roti trebuie sa fie par, intre 2 si 16!");
        }

        if (!erori.empty()) throw ValidatorException(erori);

        repo.adauga(Tractor(id, denumire, tip, numarRoti));
    }

    void decrementRoti(int id) {
        Tractor t = repo.getById(id);
        if (t.getNumarRoti() >= 2) {
            t.setNumarRoti(t.getNumarRoti() - 2);
            repo.update(t);
        }
    }
};