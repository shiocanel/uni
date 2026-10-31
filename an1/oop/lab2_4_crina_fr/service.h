#ifndef SERVICE_H
#define SERVICE_H

#include "repository.h"

typedef struct {
	Cont* cont_curent;
	Vector* undo_stack;
} Service;

Service* createService();

void destroyService(Service* s);

int adauga_srv(Service* s, int ziua, double suma, int tip, const char* descriere);

int sterge_srv(Service* s, int index);

int modifica_srv(Service* s, int index, int ziua, double suma, int tip, const char* descriere);

void delete_by_tip_srv(Service* s, int tip);

int undo(Service* s);

Vector* filtreaza_suma_minima_srv(Service* s, double suma_minima);

typedef int (*FunctieCompara)(Tranzactie*, Tranzactie*);
int cmp_suma_cresc(Tranzactie* t1, Tranzactie* t2);
int cmp_suma_desc(Tranzactie* t1, Tranzactie* t2);
int cmp_zi_cresc(Tranzactie* t1, Tranzactie* t2);
int cmp_zi_desc(Tranzactie* t1, Tranzactie* t2);
Vector* sorteaza_srv(Service* s, FunctieCompara cmp);


#endif