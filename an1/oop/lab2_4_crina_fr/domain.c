#define _CRT_SECURE_NO_WARNINGS
#include "domain.h"
#include <string.h>
#include <stdlib.h>

Tranzactie* creeaza_tranzactie(int ziua, double suma, int tip, const char* descriere) {
    Tranzactie* t = (Tranzactie*)malloc(sizeof(Tranzactie));
    if (t == NULL) return NULL;

    t->ziua = ziua;
    t->suma = suma;
    t->tip = (TipTranzactie)tip;
    strncpy(t->descriere, descriere, 99);
    t->descriere[99] = '\0';
    return t;
}

void distruge_tranzactie(Tranzactie* t) {
    if (t != NULL) {
        free(t);
    }
}

Tranzactie* copiaza_tranzactie(Tranzactie* t) {
    if (t == NULL) return NULL;
    return creeaza_tranzactie(t->ziua, t->suma, (int)t->tip, t->descriere);
}

int valideaza_tranzactie(int ziua, double suma, int tip, const char* descriere) {
    if (ziua < 1 || ziua > 31) return 0;
    if (suma <= 0.0) return 0;
    if (tip != 1 && tip != 2) return 0;
    if (descriere == NULL || strlen(descriere) == 0) return 0;
    return 1;
}