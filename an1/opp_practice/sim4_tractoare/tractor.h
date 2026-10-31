#pragma once
#include <string>

using namespace std;

class Tractor {
private:
    int id;
    string denumire;
    string tip;
    int numarRoti;

public:
    Tractor(int id, string denumire, string tip, int numarRoti) :
        id{ id }, denumire{ denumire }, tip{ tip }, numarRoti{ numarRoti } {
    }

    int getId() const { return id; }
    string getDenumire() const { return denumire; }
    string getTip() const { return tip; }
    int getNumarRoti() const { return numarRoti; }

    void setNumarRoti(int nrNou) { numarRoti = nrNou; }
};