#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "melodie.h"

class Repository {
private:
    vector<Melodie> melodii;
    string fileName;

    void readFromFile() {
        ifstream fin(fileName);
        if (!fin.is_open()) return;

        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            string id, titlu, artist, gen;
            stringstream ss(line);

            getline(ss, id, ';');
            getline(ss, titlu, ';');
            getline(ss, artist, ';');
            getline(ss, gen, ';');

            melodii.push_back(Melodie(stoi(id), titlu, artist, gen));
        }
    }

    void saveToFile() {
        ofstream fout(fileName);
        for (const auto& m : melodii) {
            fout << m.getId() << ";" << m.getTitlu() << ";"
                << m.getArtist() << ";" << m.getGen() << "\n";
        }
    }

public:
    Repository(const string& fileName) : fileName{ fileName } {
        readFromFile();
    }

    vector<Melodie> getAll() { return melodii; }

    void adauga(const Melodie& m) {
        melodii.push_back(m);
        saveToFile();
    }

    void sterge(int id) {
        auto it = remove_if(melodii.begin(), melodii.end(), [id](const Melodie& m) {
            return m.getId() == id;
            });
        if (it != melodii.end()) {
            melodii.erase(it, melodii.end());
            saveToFile();
        }
    }
};