#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "task.h"

class Repository {
private:
    vector<Task> taskuri;
    string fileName;

    vector<string> parseProgramatori(const string& str) {
        vector<string> rez;
        stringstream ss(str);
        string nume;
        while (getline(ss, nume, ',')) {
            if (!nume.empty()) rez.push_back(nume);
        }
        return rez;
    }

    string joinProgramatori(const vector<string>& progs) {
        string rez = "";
        for (size_t i = 0; i < progs.size(); ++i) {
            rez += progs[i];
            if (i < progs.size() - 1) rez += ",";
        }
        return rez;
    }

    void loadFromFile() {
        ifstream fin(fileName);
        if (!fin.is_open()) return;
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string id, desc, stare, progs;

            getline(ss, id, ';');
            getline(ss, desc, ';');
            getline(ss, stare, ';');
            getline(ss, progs, ';');

            taskuri.push_back(Task(stoi(id), desc, stare, parseProgramatori(progs)));
        }
    }

    void saveToFile() {
        ofstream fout(fileName);
        for (const auto& t : taskuri) {
            fout << t.getId() << ";" << t.getDescriere() << ";"
                << t.getStare() << ";" << joinProgramatori(t.getProgramatori()) << "\n";
        }
    }

public:
    Repository(const string& fName) : fileName{ fName } {
        loadFromFile();
    }

    vector<Task> getAll() { return taskuri; }

    void adauga(const Task& t) {
        taskuri.push_back(t);
        saveToFile();
    }

    void updateStare(int id, const string& stareNoua) {
        for (auto& t : taskuri) {
            if (t.getId() == id) {
                t.setStare(stareNoua);
                break;
            }
        }
        saveToFile();
    }
};