#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "tractor.h"

class Repository {
private:
    vector<Tractor> tractoare;
    string fileName;

    void incarcaDinFisier() {
        ifstream fin(fileName);
        if (!fin.is_open()) return;

        string linie;
        while (getline(fin, linie)) {
            if (linie.empty()) continue;
            stringstream ss(linie);
            string id, denumire, tip, numarRoti;

            getline(ss, id, ';');
            getline(ss, denumire, ';');
            getline(ss, tip, ';');
            getline(ss, numarRoti, ';');

            tractoare.push_back(Tractor(stoi(id), denumire, tip, stoi(numarRoti)));
        }
    }

    void salveazaInFisier() {
        ofstream fout(fileName);
        for (const auto& t : tractoare) {
            fout << t.getId() << ";" << t.getDenumire() << ";"
                << t.getTip() << ";" << t.getNumarRoti() << "\n";
        }
    }

public:
    Repository(const string& fileName) : fileName{ fileName } {
        incarcaDinFisier();
    }

    vector<Tractor> getAll() { return tractoare; }

    Tractor& getById(int id) {
        auto it = find_if(tractoare.begin(), tractoare.end(), [id](const Tractor& t) { return t.getId() == id; });
        if (it == tractoare.end()) throw runtime_error("Tractorul nu exista!");
        return *it;
    }

    void adauga(const Tractor& t) {
        tractoare.push_back(t);
        salveazaInFisier();
    }

    void update(const Tractor& t) {
        Tractor& existent = getById(t.getId());
        existent = t;
        salveazaInFisier();
    }
};