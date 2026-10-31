#pragma once

typedef int TElem;
#define NULL_TELEMENT 0

class Matrice {
private:
    struct Triplet {
        int linie;
        int coloana;
        TElem valoare;
    };

    int nr_linii;
    int nr_coloane;
    int cap;
    Triplet* elemente;
    int* urm;
    int primLiber;

    int d(int linie, int coloana) const;
    void redimensionare();
    void valideazaPozitie(int i, int j) const;

public:
    Matrice(int m, int n);
    ~Matrice();

    int nrLinii() const;
    int nrColoane() const;

    TElem element(int i, int j) const;
    TElem modifica(int i, int j, TElem e);
};