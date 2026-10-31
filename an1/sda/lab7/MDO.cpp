#include "MDO.h"
#include "IteratorMDO.h"
#include <exception>
#include <iostream>

using namespace std;

/*
best: Theta(1)
average: Theta(1)
worst: Theta(1)
*/
MDO::MDO(Relatie r) {
    radacina = nullptr;
    rel = r;
    dimensiune_mdo = 0;
}

/*
best: Theta(1)
average: Theta(logn)
worst: O(n)
*/
void MDO::adauga(TCheie c, TValoare v) {
    if (radacina == nullptr) {
        radacina = new Nod(c, v);
        dimensiune_mdo++;
        return;
    }

    Nod* curent = radacina;
    while (true) {
        if (curent->cheie == c) {
            curent->valori.push_back(v);
            dimensiune_mdo++;
            return;
        }
        if (rel(c, curent->cheie)) {
            if (curent->st == nullptr) {
                curent->st = new Nod(c, v);
                dimensiune_mdo++;
                return;
            }
            curent = curent->st;
        }
        else {
            if (curent->dr == nullptr) {
                curent->dr = new Nod(c, v);
                dimensiune_mdo++;
                return;
            }
            curent = curent->dr;
        }
    }
}

/*
best: Theta(1)
average: Theta(logn + k)
worst: Theta(n + k)
*/
vector<TValoare> MDO::cauta(TCheie c) const {
    Nod* curent = radacina;
    while (curent != nullptr) {
        if (curent->cheie == c) {
            return curent->valori;
        }
        if (rel(c, curent->cheie)) {
            curent = curent->st;
        }
        else {
            curent = curent->dr;
        }
    }
    return vector<TValoare>();
}

/*
best: Theta(1)
average: Theta(logn)
worst: O(n)
*/
MDO::Nod* MDO::stergeNodRec(Nod* p, TCheie c) {
    if (p == nullptr) 
        return nullptr;

    if (p->cheie == c) {
        if (p->st == nullptr) {
            Nod* temp = p->dr;
            delete p;
            return temp;
        }
        if (p->dr == nullptr) {
            Nod* temp = p->st;
            delete p;
            return temp;
        }

        Nod* minNod = p->dr;
        while (minNod->st != nullptr) {
            minNod = minNod->st;
        }

        p->cheie = minNod->cheie;
        p->valori = minNod->valori;
        p->dr = stergeNodRec(p->dr, minNod->cheie);
        return p;
    }

    if (rel(c, p->cheie)) {
        p->st = stergeNodRec(p->st, c);
    }
    else {
        p->dr = stergeNodRec(p->dr, c);
    }
    return p;
}

/*
best: Theta(1)
average: Theta(logn + k)
worst: Theta(n + k)
*/
MDO::Nod* MDO::stergeRec(Nod* p, TCheie c, TValoare v, bool& sters) {
    if (p == nullptr) 
        return nullptr;

    if (p->cheie == c) {
        for (auto it = p->valori.begin(); it != p->valori.end(); ++it) {
            if (*it == v) {
                p->valori.erase(it);
                sters = true;
                dimensiune_mdo--;
                break;
            }
        }

        if (p->valori.empty()) {
            if (p->st == nullptr) {
                Nod* temp = p->dr;
                delete p;
                return temp;
            }
            if (p->dr == nullptr) {
                Nod* temp = p->st;
                delete p;
                return temp;
            }

            Nod* minNod = p->dr;
            while (minNod->st != nullptr) {
                minNod = minNod->st;
            }

            p->cheie = minNod->cheie;
            p->valori = minNod->valori;
            p->dr = stergeNodRec(p->dr, minNod->cheie);
        }
        return p;
    }

    if (rel(c, p->cheie)) {
        p->st = stergeRec(p->st, c, v, sters);
    }
    else {
        p->dr = stergeRec(p->dr, c, v, sters);
    }
    return p;
}

/*
best: Theta(1)
average: Theta(logn + k)
worst: Theta(n + k)
*/
bool MDO::sterge(TCheie c, TValoare v) {
    bool sters = false;
    radacina = stergeRec(radacina, c, v, sters);
    return sters;
}

/*
best: Theta(1)
average: Theta(1)
worst: Theta(1)
*/
int MDO::dim() const {
    return dimensiune_mdo;
}

/*
best: Theta(1)
average: Theta(1)
worst: Theta(1)
*/
bool MDO::vid() const {
    return dimensiune_mdo == 0;
}

/*
best: Theta(1)
average: Theta(logn)
worst: O(n)
*/
IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}

/*
best: Theta(n)
average: Theta(n)
worst: Theta(n)
*/
void MDO::distrugeRec(Nod* p) {
    if (p != nullptr) {
        distrugeRec(p->st);
        distrugeRec(p->dr);
        delete p;
    }
}

/*
best: Theta(n)
average: Theta(n)
worst: Theta(n)
*/
MDO::~MDO() {
    distrugeRec(radacina);
}