#pragma once
#include "repository.h"
#include <algorithm>

class Service {
private:
    Repository& repo;

public:
    Service(Repository& repo) : repo{ repo } {}

    vector<Melodie> getMelodiiSortateDupaRank() {
        auto melodii = repo.getAll();
        sort(melodii.begin(), melodii.end(), [](const Melodie& a, const Melodie& b) {
            return a.getRank() > b.getRank(); // Descrescator dupa rank
            });
        return melodii;
    }

    void modificaMelodie(int id, const string& titluNou, int rankNou) {
        if (titluNou.empty()) 
            throw runtime_error("Titlul nu poate fi vid!");
        if (rankNou < 0 || rankNou > 10) 
            throw runtime_error("Rank-ul trebuie sa fie intre 0 si 10!");

        Melodie m = repo.getById(id);
        m.setTitlu(titluNou);
        m.setRank(rankNou);

        repo.update(m);
    }

    void stergeMelodie(int id) {
        Melodie m = repo.getById(id);
        string artist = m.getArtist();

        auto toate = repo.getAll();
        int count = count_if(toate.begin(), toate.end(), [&](const Melodie& x) {
            return x.getArtist() == artist;
            });

        if (count == 1) {
            throw runtime_error("Nu se poate sterge! Este ultima melodie a artistului: " + artist);
        }

        repo.sterge(id);
    }

    vector<int> getFrecventeRank() {
        vector<int> frecvente(11, 0);
        for (const auto& m : repo.getAll()) {
            frecvente[m.getRank()]++;
        }
        return frecvente;
    }
};