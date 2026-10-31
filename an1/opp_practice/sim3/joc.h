#pragma once
#include <string>

using namespace std;

class Joc {
private:
    int id;
    int dim;
    string tabla;
    string jucator;
    string stare;

public:
    Joc(int id, int dim, string tabla, string jucator, string stare) :
        id{ id }, dim{ dim }, tabla{ tabla }, jucator{ jucator }, stare{ stare } {
    }

    int getId() const { return id; }
    int getDim() const { return dim; }
    string getTabla() const { return tabla; }
    string getJucator() const { return jucator; }
    string getStare() const { return stare; }

    void setTabla(const string& nouaTabla) { tabla = nouaTabla; }
    void setJucator(const string& jucatorNou) { jucator = jucatorNou; }
    void setStare(const string& stareNoua) { stare = stareNoua; }
};