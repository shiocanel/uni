#pragma once
#include "repository.h"
#include <algorithm>
#include <stdexcept>

class Service {
private:
    Repository& repo;

    void validare(int dim, string tabla, string jucator, string stare) {
        if (dim != 3 && dim != 4 && dim != 5)
            throw runtime_error("Dimensiunea poate fi doar 3, 4 sau 5!");
        if (tabla.length() != static_cast<size_t>(dim * dim))
            throw runtime_error("Tabla trebuie sa aiba exact dim x dim caractere!");
        for (char c : tabla) {
            if (c != 'X' && c != 'O' && c != '-')
                throw runtime_error("Tabla poate contine doar X, O sau -");
        }
        if (jucator != "X" && jucator != "O")
            throw runtime_error("Jucatorul trebuie sa fie X sau O!");
        if (stare != "Neinceput" && stare != "In derulare" && stare != "Terminat")
            throw runtime_error("Stare invalida!");
    }

    bool verificaCastigator(string tabla, int dim) {
        // Linii
        for (int i = 0; i < dim; ++i) {
            char first = tabla[i * dim];
            if (first == '-') continue;
            bool win = true;
            for (int j = 1; j < dim; ++j)
                if (tabla[i * dim + j] != first) win = false;
            if (win) return true;
        }
        // Coloane
        for (int j = 0; j < dim; ++j) {
            char first = tabla[j];
            if (first == '-') continue;
            bool win = true;
            for (int i = 1; i < dim; ++i)
                if (tabla[i * dim + j] != first) win = false;
            if (win) return true;
        }
        // Diagonala principala
        char dp = tabla[0];
        if (dp != '-') {
            bool win = true;
            for (int i = 1; i < dim; ++i)
                if (tabla[i * dim + i] != dp) win = false;
            if (win) return true;
        }
        // Diagonala secundara
        char ds = tabla[dim - 1];
        if (ds != '-') {
            bool win = true;
            for (int i = 1; i < dim; ++i)
                if (tabla[i * dim + (dim - 1 - i)] != ds) win = false;
            if (win) return true;
        }
        return false;
    }

public:
    Service(Repository& repo) : repo{ repo } {}

    vector<Joc> getJocuriSortate() {
        auto jocuri = repo.getAll();
        sort(jocuri.begin(), jocuri.end(), [](const Joc& a, const Joc& b) {
            return a.getStare() < b.getStare(); // Sorteaza alfabetic dupa stare
            });
        return jocuri;
    }

    void adaugaJoc(int id, int dim, string tabla, string jucator) {
        // Exista deja id?
        auto toate = repo.getAll();
        for (const auto& j : toate) if (j.getId() == id) throw runtime_error("ID existent!");

        validare(dim, tabla, jucator, "Neinceput");
        repo.adauga(Joc(id, dim, tabla, jucator, "Neinceput"));
    }

    void modificaJoc(int id, int dim, string tabla, string jucator, string stare) {
        validare(dim, tabla, jucator, stare);
        repo.update(Joc(id, dim, tabla, jucator, stare));
    }

    void joacaMutare(int id, int indexCeluala) {
        Joc j = repo.getById(id);
        if (j.getStare() == "Terminat")
            throw runtime_error("Jocul s-a terminat deja!");

        string tabla = j.getTabla();
        if (tabla[indexCeluala] != '-')
            throw runtime_error("Celua este deja ocupata!");

        tabla[indexCeluala] = j.getJucator()[0];

        string urmatorulJucator = (j.getJucator() == "X") ? "O" : "X";

        string stare = "In derulare";
        if (verificaCastigator(tabla, j.getDim()) || tabla.find('-') == string::npos) {
            stare = "Terminat";
        }

        repo.update(Joc(id, j.getDim(), tabla, urmatorulJucator, stare));
    }

    Joc getJoc(int id) {
        return repo.getById(id);
    }
};