#pragma once
#include <string>
#include <vector>

using namespace std;

class Task {
private:
    int id;
    string descriere;
    string stare;
    vector<string> programatori;

public:
    Task(int id, string desc, string stare, vector<string> prog) :
        id{ id }, descriere{ desc }, stare{ stare }, programatori{ prog } {
    }

    int getId() const { return id; }
    string getDescriere() const { return descriere; }
    string getStare() const { return stare; }
    vector<string> getProgramatori() const { return programatori; }

    void setStare(const string& nouaStare) { stare = nouaStare; }
};