#pragma once
#include "repository.h"
#include "observer.h"
#include <algorithm>
#include <set>
#include <stdexcept>

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

class Service : public Observable {
private:
    Repository& repo;

public:
    Service(Repository& repo) : repo{ repo } {}

    vector<Produs> getProduseSortate() {
        auto produse = repo.getAll();
        sort(produse.begin(), produse.end(), [](const Produs& a, const Produs& b) {
            return a.getPret() < b.getPret();
            });
        return produse;
    }

    set<string> getTipuriDistincte() {
        set<string> tipuri;
        for (const auto& p : repo.getAll()) tipuri.insert(p.getTip());
        return tipuri;
    }

    int getNumarProduseTip(const string& tip) {
        int count = 0;
        for (const auto& p : repo.getAll()) {
            if (p.getTip() == tip) count++;
        }
        return count;
    }

    void adaugaProdus(int id, string nume, string tip, double pret) {
        vector<string> erori;

        if (nume.empty()) erori.push_back("Numele nu poate fi vid!");
        if (pret < 1.0 || pret > 100.0) erori.push_back("Pretul trebuie sa fie intre 1.0 si 100.0!");

        auto produse = repo.getAll();
        auto it = find_if(produse.begin(), produse.end(), [id](const Produs& p) { return p.getId() == id; });
        if (it != produse.end()) erori.push_back("Exista deja un produs cu acest ID!");

        if (!erori.empty()) throw ValidatorException(erori);

        repo.adauga(Produs(id, nume, tip, pret));

        notify();
    }
};