#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "masina.h"

class Repository {
private:
    vector<Masina> masini;
    string fileName;

    void readFromFile() {
        ifstream fin(fileName);
        if (!fin.is_open())
            throw runtime_error("Nu s-a putut deschide fisierul: " + fileName);

        string line;
        while (getline(fin, line)) {
            if (line.empty())
                continue;

            string nrInmatriculare, denumire, anFabricatie, tip;
            stringstream ss(line);

            getline(ss, nrInmatriculare, ';');
            getline(ss, denumire, ';');
            getline(ss, anFabricatie, ';');
            getline(ss, tip, ';');

            Masina masina(nrInmatriculare, denumire, stoi(anFabricatie), tip);
            masini.push_back(masina);
        }
    }

    void saveToFile() {
        ofstream fout(fileName);
        for (const auto& m : masini) {
            fout << m.getNrInmatriculare() << ";" << m.getDenumire() << ";"
                << m.getAnFabricatie() << ";" << m.getTip() << "\n";
        }
    }

public:
    Repository(const string& fileName) : fileName{ fileName } {
        readFromFile();
    }

    vector<Masina> getAll() {
        return masini;
    }

    Masina getByNrInmatriculare(const string& nr) {
        auto res = find_if(masini.begin(), masini.end(), [&nr](const Masina& m) {
            return m.getNrInmatriculare() == nr;
            });
        if (res == masini.end())
            throw runtime_error("Masina nu exista!");
        return *res;
    }

    void adauga(const Masina& m) {
        masini.push_back(m);
        saveToFile();
    }

    void sterge(const string& nr) {
        auto it = remove_if(masini.begin(), masini.end(), [&nr](const Masina& m) {
            return m.getNrInmatriculare() == nr;
            });
        masini.erase(it, masini.end());
        saveToFile();
    }

    void modificaAnTuturor(int delta) {
        for (auto& m : masini) {
            m.setAnFabricatie(m.getAnFabricatie() + delta);
        }
        saveToFile();
    }
};