#pragma once
#include <algorithm>

#include "repository.h"

class Service {
private:
    Repository& repo;
public:
    /*
    constructor penntru service
    */
    Service(Repository& repo) : repo{ repo } {}

    vector<Melodie> getMelodiiSortateDupaRank() {
        /*
        functie care returneaza melodiile sortate dupa rank
        pre:
        post: melodii (vector<Melodie>)
        */

        auto melodii = repo.getAll();
        sort(melodii.begin(), melodii.end(), [](const Melodie& a, const Melodie& b) {
            return a.getRank() > b.getRank();
            });

        return melodii;
    }

    void modificaMelodie(int id, const string& titluNou, int rankNou) {
        /*
        functie care modifica o melodie dupa id si seteaza titluNou si rankNou
        pre: id (int), titluNou != "", 0 <= rankNou <= 10
        post: modifica titlu si rank pentru melodia cu id
        */

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
        /*
        functie care sterge o melodie dupa id
        daca artistul are ramas numai o singura piesa, ea nu v-a fi stearsa
        pre: id (int)
        post: sterge melodia daca artistul mai are si alte piese in repo
        */

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
        /*
        functie care returneaza un vector de frecventa pentru rank
        numara cate piese sunt de fiecare rank
        pre: 
        post: frecvente (vector<int>)
        */

        vector<int> frecvente(11, 0);
        for (const auto& m : repo.getAll()) {
            frecvente[m.getRank()]++;
        }
        return frecvente;
    }
};