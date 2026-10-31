#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "joc.h"

class Repository {
private:
    vector<Joc> jocuri;
    string fileName;

    void readFromFile() {
        ifstream fin(fileName);
        if (!fin.is_open()) return;

        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            string id, dim, tabla, jucator, stare;
            stringstream ss(line);

            getline(ss, id, ';');
            getline(ss, dim, ';');
            getline(ss, tabla, ';');
            getline(ss, jucator, ';');
            getline(ss, stare, ';');

            jocuri.push_back(Joc(stoi(id), stoi(dim), tabla, jucator, stare));
        }
    }

    void saveToFile() {
        ofstream fout(fileName);
        for (const auto& j : jocuri) {
            fout << j.getId() << ";" << j.getDim() << ";" << j.getTabla() << ";"
                << j.getJucator() << ";" << j.getStare() << "\n";
        }
    }

public:
    Repository(const string& fileName) : fileName{ fileName } {
        readFromFile();
    }

    vector<Joc> getAll() { return jocuri; }

    Joc& getById(int id) {
        auto it = find_if(jocuri.begin(), jocuri.end(), [id](const Joc& j) { return j.getId() == id; });
        if (it == jocuri.end()) throw runtime_error("Jocul nu a fost gasit!");
        return *it;
    }

    void adauga(const Joc& j) {
        jocuri.push_back(j);
        saveToFile();
    }

    void update(const Joc& j) {
        Joc& existent = getById(j.getId());
        existent = j;
        saveToFile();
    }
};