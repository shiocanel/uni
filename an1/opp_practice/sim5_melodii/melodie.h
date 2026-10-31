#pragma once
#include <string>

using namespace std;

class Melodie {
private:
    int id;
    string titlu;
    string artist;
    int rank;

public:
    Melodie(int id, string titlu, string artist, int rank) :
        id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {
    }

    int getId() const { return id; }
    string getTitlu() const { return titlu; }
    string getArtist() const { return artist; }
    int getRank() const { return rank; }

    void setTitlu(const string& titluNou) { titlu = titluNou; }
    void setRank(int rankNou) { rank = rankNou; }
};