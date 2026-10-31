#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "vector.h"
#include "domain.h"

typedef struct {
	Vector* tranzactii;
} Cont;

Cont* init_cont();

void adauga_repo(Cont* cont, Tranzactie* t);

void sterge_repo(Cont* cont, int index);

void modifica_repo(Cont* cont, int index, Tranzactie* t_noua);

void distruge_cont(Cont* cont);

int get_nr_elemente(Cont* cont);

Tranzactie* get_tranzactie(Cont* cont, int index);

#endif