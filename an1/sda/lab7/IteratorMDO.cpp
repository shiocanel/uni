#include "IteratorMDO.h"
#include <exception>

/*
best: Theta(1)
average: Theta(logn)
worst: O(n)
*/
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
    prim();
}

/*
best: Theta(1)
average: Theta(logn)
worst: O(n)
*/
void IteratorMDO::prim() {
    while (!st.empty()) {
        st.pop();
    }

    MDO::Nod* nod = dict.radacina;
    while (nod != nullptr) {
        st.push(nod);
        nod = nod->st;
    }

    if (!st.empty()) {
        curent = st.top();
    }
    else {
        curent = nullptr;
    }
    indexValoare = 0;
}

/*
best: Theta(1)
average: Theta(1) amortizat
worst: Theta(n)
*/
void IteratorMDO::urmator() {
    if (!valid()) {
        throw std::exception();
    }

    indexValoare++;
    if (indexValoare < curent->valori.size()) {
        return;
    }

    indexValoare = 0;
    MDO::Nod* n = st.top();
    st.pop();

    if (n->dr != nullptr) {
        n = n->dr;
        while (n != nullptr) {
            st.push(n);
            n = n->st;
        }
    }

    if (!st.empty()) {
        curent = st.top();
    }
    else {
        curent = nullptr;
    }
}

/*
best: Theta(1)
average: Theta(1)
worst: Theta(1)
*/
bool IteratorMDO::valid() const {
    return curent != nullptr;
}

/*
best: Theta(1)
average: Theta(1)
worst: Theta(1)
*/
TElem IteratorMDO::element() const {
    if (!valid()) {
        throw std::exception();
    }
    return std::pair<TCheie, TValoare>(curent->cheie, curent->valori[indexValoare]);
}