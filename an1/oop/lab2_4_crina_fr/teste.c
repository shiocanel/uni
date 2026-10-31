#include "teste.h"
#include "service.h"
#include "domain.h"
#include "vector.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void test_domain_si_validare() {
    assert(valideaza_tranzactie(15, 100.0, 1, "Salariu") == 1);
    assert(valideaza_tranzactie(0, 100.0, 1, "Salariu") == 0);
    assert(valideaza_tranzactie(32, 100.0, 1, "Salariu") == 0);
    assert(valideaza_tranzactie(15, -1.0, 1, "Salariu") == 0);
    assert(valideaza_tranzactie(15, 100.0, 3, "Salariu") == 0);
    assert(valideaza_tranzactie(15, 100.0, 1, "") == 0);
    assert(valideaza_tranzactie(15, 100.0, 1, NULL) == 0);

    Tranzactie* t = creeaza_tranzactie(10, 50.0, 1, "Test");
    assert(t->ziua == 10);
    Tranzactie* c = copiaza_tranzactie(t);
    assert(c->suma == 50.0);
    assert(strcmp(c->descriere, "Test") == 0);

    distruge_tranzactie(t);
    distruge_tranzactie(c);
}

void test_vector_generic() {
    Vector* v = createVector();
    assert(size(v) == 0);

    int* n1 = malloc(sizeof(int)); *n1 = 10;
    int* n2 = malloc(sizeof(int)); *n2 = 20;
    int* n3 = malloc(sizeof(int)); *n3 = 30;

    add(v, n1);
    add(v, n2);
    add(v, n3);
    assert(size(v) == 3);
    assert(*(int*)get(v, 1) == 20);

    int* removed = (int*)deleteElement(v, 1);
    assert(*removed == 20);
    assert(size(v) == 2);
    free(removed);

    int* n4 = malloc(sizeof(int)); *n4 = 40;
    set(v, 0, n4);
    assert(*(int*)get(v, 0) == 40);
    free(n1);
    free(get(v, 0));
    free(get(v, 1));
    destroyVector(v);
}

void test_service_si_undo() {
    Service* s = createService();

    adauga_srv(s, 10, 100.0, 1, "A");
    assert(get_nr_elemente(s->cont_curent) == 1);

    undo(s);
    assert(get_nr_elemente(s->cont_curent) == 0);

    adauga_srv(s, 1, 10.0, 1, "T1");
    adauga_srv(s, 2, 20.0, 2, "T2");

    sterge_srv(s, 0);
    assert(get_nr_elemente(s->cont_curent) == 1);

    undo(s);
    assert(get_nr_elemente(s->cont_curent) == 2);

    undo(s);
    assert(get_nr_elemente(s->cont_curent) == 1);
    assert(get_tranzactie(s->cont_curent, 0)->ziua == 1);

    modifica_srv(s, 0, 5, 50.0, 1, "Modificat");
    assert(get_tranzactie(s->cont_curent, 0)->ziua == 5);
    undo(s);
    assert(get_tranzactie(s->cont_curent, 0)->ziua == 1);

    assert(undo(s) == 1);
    assert(undo(s) == 0);

    adauga_srv(s, 1, 10.0, 1, "T1");
    adauga_srv(s, 2, 20.0, 2, "T2");
    delete_by_tip_srv(s, 1);

    destroyService(s);
}

void test_filtrari() {
    Service* s = createService();
    adauga_srv(s, 10, 100.0, 1, "Salariu");
    adauga_srv(s, 11, 200.0, 1, "Bonus");
    adauga_srv(s, 12, 50.0, 2, "Mancare");

    Vector* filtrate = filtreaza_suma_minima_srv(s, 150.0);
    assert(size(filtrate) == 1);
    destroyVector(filtrate);

    assert(sterge_srv(s, 100) == 0);
    assert(modifica_srv(s, 100, 1, 1, 1, "X") == 0);
    assert(modifica_srv(s, 0, 99, 1, 1, "X") == 0);

    destroyService(s);
}

void test_comparatori() {
    Tranzactie* t1 = creeaza_tranzactie(1, 100.0, 1, "A");
    Tranzactie* t2 = creeaza_tranzactie(2, 200.0, 2, "B");
    Tranzactie* t3 = creeaza_tranzactie(1, 100.0, 1, "C");

    assert(cmp_suma_cresc(t1, t2) < 0);
    assert(cmp_suma_cresc(t2, t1) > 0);
    assert(cmp_suma_cresc(t1, t3) == 0);

    assert(cmp_suma_desc(t1, t2) > 0);
    assert(cmp_suma_desc(t2, t1) < 0);

    assert(cmp_zi_cresc(t1, t2) < 0);
    assert(cmp_zi_cresc(t2, t1) > 0);
    assert(cmp_zi_cresc(t1, t3) == 0);

    assert(cmp_zi_desc(t1, t2) > 0);

    distruge_tranzactie(t1);
    distruge_tranzactie(t2);
    distruge_tranzactie(t3);
}

void test_sortare_service() {
    Service* s = createService();

    adauga_srv(s, 20, 50.0, 1, "Ieftin");
    adauga_srv(s, 10, 500.0, 2, "Scump");
    adauga_srv(s, 15, 100.0, 1, "Mediu");

    Vector* sortate_suma = sorteaza_srv(s, cmp_suma_cresc);
    assert(size(sortate_suma) == 3);
    assert(((Tranzactie*)get(sortate_suma, 0))->suma == 50.0);
    assert(((Tranzactie*)get(sortate_suma, 1))->suma == 100.0);
    assert(((Tranzactie*)get(sortate_suma, 2))->suma == 500.0);
    destroyVector(sortate_suma);

    Vector* sortate_zi = sorteaza_srv(s, cmp_zi_desc);
    assert(((Tranzactie*)get(sortate_zi, 0))->ziua == 20);
    assert(((Tranzactie*)get(sortate_zi, 1))->ziua == 15);
    assert(((Tranzactie*)get(sortate_zi, 2))->ziua == 10);
    destroyVector(sortate_zi);

    assert(get_tranzactie(s->cont_curent, 0)->ziua == 20);

    destroyService(s);
}

void ruleaza_toate_testele() {
    test_domain_si_validare();
    test_vector_generic();
    test_service_si_undo();
    test_comparatori();
    test_sortare_service();
    test_filtrari();
    printf("[OK] Toate testele (100%% Coverage) au trecut!\n");
}

