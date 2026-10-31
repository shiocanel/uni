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
        /*
        funcie care citeste melodiile din fisierul fileName
        pre: fileName fisier existent
        post: incarca toate melodiile in melodii (vector<>)
        */

        ifstream fin(fileName);
        string line;
        while (getline(fin, line)) {
            string id, titlu, artist, rank;
            stringstream ss(line);

            getline(ss, id, ';');
            getline(ss, titlu, ';');
            getline(ss, artist, ';');
            getline(ss, rank, ';');

            melodii.push_back(Melodie(stoi(id), titlu, artist, stoi(rank)));
        }
    }

    void saveToFile() {
        /*
        fucntie care incarca in fisierul fileName datele din vectorul melodii
        pre:
        post: fisierul fileName este incarcat cu date din melodii(vector<>)
        */
        ofstream fout(fileName);
        for (const auto& m : melodii) {
            fout << m.getId() << ";" << m.getTitlu() << ";" << m.getArtist() << ";" << m.getRank() << "\n";
        }
    }

public:
    Repository(const string& fileName) : fileName{ fileName } {
        /*
        constrcutor pentru repository care incarca din fisier date direct din instantiere
        pre:
        post: 
        */

        readFromFile();
    }

    vector<Melodie> getAll() { 
        /*
        functie get pentru a returna un vector cu toate melodiile (vector<Melodie>)
        pre:
        post: melodii (vector<Melodie>) 
        */

        return melodii; 
    }

    Melodie& getById(int id) {
        /*
        functie care returneaza o Melodie pentru un id dat ca parametru
        pre: id (int)
        post: *it (Melodie* ) melodia cu this->id = id
        */

        auto it = find_if(melodii.begin(), melodii.end(), [id](const Melodie& m) { 
            return m.getId() == id; 
            });

        if (it == melodii.end())
            throw runtime_error("Melodia nu exista!");

        return *it;
    }

    void sterge(int id) {
        /*
        functie care sterge melodia din repo dupa un id dat ca parametru
        pre: id (int)
        post: se sterge Melodia daca exista in repo
        */

        auto it = remove_if(melodii.begin(), melodii.end(), [id](const Melodie& m) { 
            return m.getId() == id; 
            });

        melodii.erase(it, melodii.end());
        saveToFile();
    }

    void add(Melodie m) {
        /*
        functie care adauga o melodie dat ca parametru
        pre: m (Melodie)
        post: se adauga in repo si in fisier
        */

        melodii.push_back(m);
        saveToFile();
    }

    void update(const Melodie& m) {
        /*
        functie care modifica o melodie cu m.getId() cu toate atributele lui m
        pre: m (Melodie)
        post: se modifica melodia cu id = m.getId();
        */

        Melodie& existenta = getById(m.getId());
        existenta = m;
        saveToFile();
    }
};