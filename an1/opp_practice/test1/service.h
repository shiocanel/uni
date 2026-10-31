#pragma once
#include <string>

#include "repository.h"
#include <algorithm>

using namespace std;

class Service {
private:
    Repository& repo;

    static int marimeRank(string m) {
        if (m == "XS") return 0;
        if (m == "S")  return 1;
        if (m == "M")  return 2;
        if (m == "L")  return 3;
        if (m == "XL") return 4;
        if (m == "XXL") return 5;

        return 100;
    }
public:
    Service(Repository& repo) : repo{ repo } {};

    vector<Rochie> getAll() const {
        return repo.getAll();
    }

    void inchiriazaRochie(int id) {
        Rochie& rochie = repo.findByCod(id);
        if (!rochie.isDisponibila())
            throw runtime_error("Rochie indisponibila!");

        rochie.setDisponibiliate(false);
    }

    vector<Rochie> sortByPret() {
        vector<Rochie> ans = repo.getAll();

        sort(ans.begin(), ans.end(), [](const Rochie& a, const Rochie& b) {
            return a.getPret() < b.getPret();
            });

        return ans;
    }

    vector<Rochie> sortByMarime() {
        vector<Rochie> ans = repo.getAll();

        sort(ans.begin(), ans.end(), [](const Rochie& a, const Rochie& b) {
            return Service::marimeRank(a.getMarime()) < 
                   Service::marimeRank(b.getMarime());
            });

        return ans;
    }
};