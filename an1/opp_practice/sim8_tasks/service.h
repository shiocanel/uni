#pragma once
#include "repository.h"
#include "observer.h"
#include <stdexcept>

class ValidatorException : public exception {
    string msg;
public:
    ValidatorException(string m) : msg{ m } {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class Service : public Observable {
private:
    Repository& repo;

public:
    Service(Repository& r) : repo{ r } {}

    vector<Task> getTasksFilteredAndSorted(const string& filterProg = "") {
        auto taskuri = repo.getAll();

        if (!filterProg.empty()) {
            vector<Task> filtrate;
            copy_if(taskuri.begin(), taskuri.end(), back_inserter(filtrate), [&](const Task& t) {
                for (const auto& p : t.getProgramatori()) {
                    if (p.find(filterProg) != string::npos) return true;
                }
                return false;
                });
            taskuri = filtrate;
        }

        sort(taskuri.begin(), taskuri.end(), [](const Task& a, const Task& b) {
            return a.getStare() < b.getStare();
            });

        return taskuri;
    }

    void adaugaTask(int id, string desc, string stare, const vector<string>& progs) {
        string err = "";
        for (const auto& t : repo.getAll()) {
            if (t.getId() == id) err += "ID-ul exista deja!\n";
        }
        if (desc.empty()) err += "Descrierea nu poate fi vida!\n";
        if (stare != "open" && stare != "inprogress" && stare != "closed")
            err += "Starea trebuie sa fie open, inprogress sau closed!\n";
        if (progs.size() < 1 || progs.size() > 4)
            err += "Trebuie sa introduci intre 1 si 4 programatori!\n";

        if (!err.empty()) throw ValidatorException(err);

        repo.adauga(Task(id, desc, stare, progs));
        notify();
    }

    void schimbaStareTask(int id, const string& stareNoua) {
        repo.updateStare(id, stareNoua);
        notify();
    }
};