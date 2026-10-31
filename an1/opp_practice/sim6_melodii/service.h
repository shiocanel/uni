#pragma once
#include "repository.h"
#include <algorithm>
#include <map>

class Service {
private:
    Repository& repo;

public:
    Service(Repository& repo) : repo{ repo } {}

    vector<Melodie> getMelodiiSortateDupaArtist() {
        auto melodii = repo.getAll();
        sort(melodii.begin(), melodii.end(), [](const Melodie& a, const Melodie& b) {
            return a.getArtist() < b.getArtist();
            });
        return melodii;
    }

    void adaugaMelodie(string titlu, string artist, string gen) {
        if (titlu.empty() || artist.empty())
            throw runtime_error("Titlul si artistul nu pot fi vide!");
        if (gen != "pop" && gen != "rock" && gen != "folk" && gen != "disco")
            throw runtime_error("Genul trebuie sa fie pop, rock, folk sau disco!");

        int newId = 1;
        for (const auto& m : repo.getAll()) {
            if (m.getId() >= newId) newId = m.getId() + 1;
        }

        repo.adauga(Melodie(newId, titlu, artist, gen));
    }

    void stergeMelodie(int id) {
        repo.sterge(id);
    }

    map<string, int> getContorArtisti() {
        map<string, int> countArtist;
        for (const auto& m : repo.getAll()) countArtist[m.getArtist()]++;
        return countArtist;
    }

    map<string, int> getContorGenuri() {
        map<string, int> countGen;
        for (const auto& m : repo.getAll()) countGen[m.getGen()]++;
        return countGen;
    }
};