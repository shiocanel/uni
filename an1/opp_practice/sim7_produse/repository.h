#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "produs.h"

class Repository {
private:
    vector<Produs> produse;
    string fileName;

    void incarcaDinFisier() {
        ifstream fin(fileName);
        if (!fin.is_open()) return;

        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            string id, nume, tip, pret;
            stringstream ss(line);

            getline(ss, id, ';');
            getline(ss, nume, ';');
            getline(ss, tip, ';');
            getline(ss, pret, ';');

            produse.push_back(Produs(stoi(id), nume, tip, stod(pret)));
        }
    }

    void salveazaInFisier() {
        ofstream fout(fileName);
        for (const auto& p : produse) {
            fout << p.getId() << ";" << p.getNume() << ";"
                << p.getTip() << ";" << p.getPret() << "\n";
        }
    }

public:
    Repository(const string& fileName) : fileName{ fileName } {
        incarcaDinFisier();
    }

    vector<Produs> getAll() { return produse; }

    void adauga(const Produs& p) {
        produse.push_back(p);
        salveazaInFisier();
    }
};