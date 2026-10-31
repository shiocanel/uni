#include "Matrice.h"
#include <exception>

using namespace std;

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
int Matrice::d(int linie, int coloana) const {
    return (int)((1LL * linie * nr_coloane + coloana) % cap);
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
void Matrice::valideazaPozitie(int i, int j) const {
    if (i < 0 || i >= nr_linii || j < 0 || j >= nr_coloane) {
        throw exception();
    }
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
Matrice::Matrice(int m, int n) {
    if (m <= 0 || n <= 0) {
        throw exception();
    }

    nr_linii = m;
    nr_coloane = n;
    cap = 10;

    elemente = new Triplet[cap];
    urm = new int[cap];

    for (int i = 0; i < cap; i++) {
        elemente[i].linie = -1;
        elemente[i].coloana = -1;
        elemente[i].valoare = NULL_TELEMENT;
        urm[i] = -1;
    }

    primLiber = 0;
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
Matrice::~Matrice() {
    delete[] elemente;
    delete[] urm;
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
int Matrice::nrLinii() const {
    return nr_linii;
}

/*
Best: Theta(1);
Worst: Theta(1);
Average: Theta(1);
*/
int Matrice::nrColoane() const {
    return nr_coloane;
}

/*
Best: Theta(1);
Worst: O(n);
Average: Theta(1);
*/
TElem Matrice::element(int i, int j) const {
    valideazaPozitie(i, j);

    int poz = d(i, j);
    while (poz != -1) {
        if (elemente[poz].linie == i && elemente[poz].coloana == j) {
            return elemente[poz].valoare;
        }
        poz = urm[poz];
    }

    return NULL_TELEMENT;
}

/*
Best: Theta(n);
Worst: Theta(n);
Average: Theta(n);
*/
void Matrice::redimensionare() {
    int vechiCap = cap;
    Triplet* vechiElemente = elemente;
    int* vechiUrm = urm;

    cap *= 2;
    elemente = new Triplet[cap];
    urm = new int[cap];

    for (int i = 0; i < cap; i++) {
        elemente[i].linie = -1;
        elemente[i].coloana = -1;
        elemente[i].valoare = NULL_TELEMENT;
        urm[i] = -1;
    }

    primLiber = 0;

    for (int i = 0; i < vechiCap; i++) {
        if (vechiElemente[i].linie != -1) {
            modifica(vechiElemente[i].linie, vechiElemente[i].coloana, vechiElemente[i].valoare);
        }
    }

    delete[] vechiElemente;
    delete[] vechiUrm;
}

/*
Best: Theta(1);
Worst: Theta(n);
Average: Theta(1);
*/
TElem Matrice::modifica(int i, int j, TElem elem) {
    valideazaPozitie(i, j);

    int poz = d(i, j);
    int precedent = -1;
    int curent = poz;

    while (curent != -1 && !(elemente[curent].linie == i && elemente[curent].coloana == j)) {
        precedent = curent;
        curent = urm[curent];
    }

    if (curent != -1) {
        TElem vechi = elemente[curent].valoare;

        if (elem != NULL_TELEMENT) {
            elemente[curent].valoare = elem;
            return vechi;
        }

        bool gata = false;
        while (!gata) {
            int p = urm[curent];
            int pp = curent;

            while (p != -1 && d(elemente[p].linie, elemente[p].coloana) != curent) {
                pp = p;
                p = urm[p];
            }

            if (p == -1) {
                gata = true;
            }
            else {
                elemente[curent] = elemente[p];
                precedent = pp;
                curent = p;
            }
        }

        if (precedent != -1) {
            urm[precedent] = urm[curent];
        }

        elemente[curent].linie = -1;
        elemente[curent].coloana = -1;
        elemente[curent].valoare = NULL_TELEMENT;
        urm[curent] = -1;

        if (primLiber > curent) {
            primLiber = curent;
        }

        while (primLiber < cap && elemente[primLiber].linie != -1) {
            primLiber++;
        }

        return vechi;
    }

    if (elem == NULL_TELEMENT) {
        return NULL_TELEMENT;
    }

    while (primLiber < cap && elemente[primLiber].linie != -1) {
        primLiber++;
    }

    if (primLiber == cap) {
        redimensionare();
    }

    poz = d(i, j);

    if (elemente[poz].linie == -1) {
        elemente[poz].linie = i;
        elemente[poz].coloana = j;
        elemente[poz].valoare = elem;
    }
    else {
        int p = poz;
        while (urm[p] != -1) {
            p = urm[p];
        }

        elemente[primLiber].linie = i;
        elemente[primLiber].coloana = j;
        elemente[primLiber].valoare = elem;
        urm[p] = primLiber;
    }

    while (primLiber < cap && elemente[primLiber].linie != -1) {
        primLiber++;
    }

    return NULL_TELEMENT;
}