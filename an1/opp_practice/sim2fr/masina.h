#pragma once
#include <string>

using namespace std;

class Masina {
private:
    string nrInmatriculare;
    string denumire;
    int anFabricatie;
    string tip;

public:
    Masina(string nrInmatriculare, string denumire, int anFabricatie, string tip) :
        nrInmatriculare{ nrInmatriculare }, denumire{ denumire },
        anFabricatie{ anFabricatie }, tip{ tip } {
    }

    string getNrInmatriculare() const { return nrInmatriculare; }
    string getDenumire() const { return denumire; }
    int getAnFabricatie() const { return anFabricatie; }
    string getTip() const { return tip; }

    void setAnFabricatie(int anNou) { anFabricatie = anNou; }
};