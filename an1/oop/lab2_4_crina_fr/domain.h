#ifndef DOMAIN_H
#define DOMAIN_H

typedef enum {
    INTRARE = 1,
    IESIRE = 2
} TipTranzactie;

typedef struct {
    int ziua;
    double suma;
    TipTranzactie tip;
    char descriere[100];
} Tranzactie;

Tranzactie* creeaza_tranzactie(int ziua, double suma, int tip, const char* descriere);

void distruge_tranzactie(Tranzactie* t);

Tranzactie* copiaza_tranzactie(Tranzactie* t);

int valideaza_tranzactie(int ziua, double suma, int tip, const char* descriere);

#endif