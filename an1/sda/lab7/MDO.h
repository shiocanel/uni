#pragma once

#include <vector>
#include <utility>

typedef int TCheie;
typedef int TValoare;
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;
typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
    friend class IteratorMDO;

private:
    struct Nod {
        TCheie cheie;
        vector<TValoare> valori;
        Nod* st;
        Nod* dr;

        Nod(TCheie c, TValoare v) : cheie(c), st(nullptr), dr(nullptr) {
            valori.push_back(v);
        }
    };

    Nod* radacina;
    Relatie rel;
    int dimensiune_mdo;

    Nod* stergeRec(Nod* p, TCheie c, TValoare v, bool& sters);
    Nod* stergeNodRec(Nod* p, TCheie c);
    void distrugeRec(Nod* p);

public:
    // constructorul implicit al MultiDictionarului Ordonat
    MDO(Relatie r);

    // adauga o pereche (cheie, valoare) in MDO
    void adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    //sterge o cheie si o valoare 
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    //returneaza numarul de perechi (cheie, valoare) din MDO 
    int dim() const;

    //verifica daca MultiDictionarul Ordonat e vid 
    bool vid() const;

    // se returneaza iterator pe MDO
    // iteratorul va returna perechile in ordine in raport cu relatia de ordine
    IteratorMDO iterator() const;

    // destructorul  
    ~MDO();
};