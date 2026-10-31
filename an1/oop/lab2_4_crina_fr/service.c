#include "service.h"
#include <stdlib.h>
#include <string.h>

Vector* copy_current_state(Vector* v) {
	Vector* copy = createVector();
	for (int i = 0; i < size(v); i++) {
		Tranzactie* t = (Tranzactie*)get(v, i);
		add(copy, copiaza_tranzactie(t));
	}
	return copy;
}

void distruge_lista_tranzactii(Vector* v) {
	for (int i = 0; i < size(v); i++) {
		Tranzactie* t = (Tranzactie*)get(v, i);
		distruge_tranzactie(t);
	}
	destroyVector(v);
}

Service* createService() {
	Service* s = (Service*)malloc(sizeof(Service));
	s->cont_curent = init_cont();
	s->undo_stack = createVector();
	return s;
}

void destroyService(Service* s) {
	distruge_cont(s->cont_curent);

	for (int i = 0; i < size(s->undo_stack); i++) {
		Vector* v = (Vector*)get(s->undo_stack, i);
		distruge_lista_tranzactii(v);
	}
	destroyVector(s->undo_stack);
	free(s);
}

int adauga_srv(Service* s, int ziua, double suma, int tip, const char* descriere) {
	if (!valideaza_tranzactie(ziua, suma, tip, descriere)) return 0;

	Vector* state_copy = copy_current_state(s->cont_curent->tranzactii);
	add(s->undo_stack, state_copy);

	Tranzactie* t = creeaza_tranzactie(ziua, suma, tip, descriere);
	adauga_repo(s->cont_curent, t);
	return 1;
}

int sterge_srv(Service* s, int index) {
	if (index < 0 || index >= get_nr_elemente(s->cont_curent)) 
		return 0;

	Vector* state_copy = copy_current_state(s->cont_curent->tranzactii);
	add(s->undo_stack, state_copy);

	sterge_repo(s->cont_curent, index);
	return 1;
}

void delete_by_tip_srv(Service* s, int tip) {
	Vector* state_copy = copy_current_state(s->cont_curent->tranzactii);
	add(s->undo_stack, state_copy);

	for (int i = 0; i < size(s->cont_curent->tranzactii); i++) {
		Tranzactie* t = (Tranzactie*)get(s->cont_curent->tranzactii, i);

		if ((int)t->tip == tip) 
			sterge_repo(s->cont_curent, i);
	}
}

int modifica_srv(Service* s, int index, int ziua, double suma, int tip, const char* descriere) {
	if (index < 0 || index >= get_nr_elemente(s->cont_curent)) 
		return 0;
	if (!valideaza_tranzactie(ziua, suma, tip, descriere)) 
		return 0;

	Vector* state_copy = copy_current_state(s->cont_curent->tranzactii);
	add(s->undo_stack, state_copy);

	Tranzactie* t_nou = creeaza_tranzactie(ziua, suma, tip, descriere);
	modifica_repo(s->cont_curent, index, t_nou);
	return 1;
}

int undo(Service* s) {
	int n = size(s->undo_stack);
	if (n <= 0) 
		return 0;

	Vector* last_state = (Vector*)deleteElement(s->undo_stack, n - 1);

	distruge_lista_tranzactii(s->cont_curent->tranzactii);

	s->cont_curent->tranzactii = last_state;
	return 1;
}

Vector* filtreaza_suma_minima_srv(Service* s, double suma_minima) {
	Vector* rez = createVector();
	for (int i = 0; i < get_nr_elemente(s->cont_curent); i++) {
		Tranzactie* t = get_tranzactie(s->cont_curent, i);
		if (t->suma >= suma_minima) {
			add(rez, t);
		}
	}
	return rez;
}

int cmp_suma_cresc(Tranzactie* t1, Tranzactie* t2) {
	if (t1->suma < t2->suma) 
		return -1;
	if (t1->suma > t2->suma) 
		return 1;
	return 0;
}

int cmp_suma_desc(Tranzactie* t1, Tranzactie* t2) {
	return cmp_suma_cresc(t2, t1);
}

int cmp_zi_cresc(Tranzactie* t1, Tranzactie* t2) {
	return t1->ziua - t2->ziua;
}

int cmp_zi_desc(Tranzactie* t1, Tranzactie* t2) {
	return cmp_zi_cresc(t2, t1);
}

Vector* sorteaza_srv(Service* s, FunctieCompara cmp) {
	Vector* v = s->cont_curent->tranzactii;
	int n = size(v);

	Vector* lista_sortata = createVector();
	for (int i = 0; i < n; i++) {
		add(lista_sortata, get(v, i));
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			Tranzactie* t1 = (Tranzactie*)get(lista_sortata, i);
			Tranzactie* t2 = (Tranzactie*)get(lista_sortata, j);

			if (cmp(t1, t2) > 0) {
				set(lista_sortata, i, t2);
				set(lista_sortata, j, t1);
			}
		}
	}
	return lista_sortata;
}