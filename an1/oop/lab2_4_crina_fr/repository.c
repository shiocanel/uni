#include "repository.h"
#include <stdlib.h>

Cont* init_cont() {
	Cont* c = (Cont*)malloc(sizeof(Cont));
	if (c != NULL) {
		c->tranzactii = createVector();
	}
	return c;
}

void adauga_repo(Cont* cont, Tranzactie* t) {
	if (cont == NULL || t == NULL) return;
	add(cont->tranzactii, t);
}

void sterge_repo(Cont* cont, int index) {
	if (cont == NULL) return;
	Tranzactie* t = (Tranzactie*)deleteElement(cont->tranzactii, index);
	distruge_tranzactie(t);
}

void modifica_repo(Cont* cont, int index, Tranzactie* t_noua) {
	if (cont == NULL || t_noua == NULL) return;

	Tranzactie* t_veche = (Tranzactie*)get(cont->tranzactii, index);
	distruge_tranzactie(t_veche);

	set(cont->tranzactii, index, t_noua);
}

void distruge_cont(Cont* cont) {
	if (cont == NULL) return;

	for (int i = 0; i < size(cont->tranzactii); i++) {
		Tranzactie* t = (Tranzactie*)get(cont->tranzactii, i);
		distruge_tranzactie(t);
	}

	destroyVector(cont->tranzactii);

	free(cont);
}

int get_nr_elemente(Cont* cont) {
	if (cont == NULL) return 0;
	return size(cont->tranzactii);
}

Tranzactie* get_tranzactie(Cont* cont, int index) {
	if (cont == NULL) return NULL;
	return (Tranzactie*)get(cont->tranzactii, index);
}