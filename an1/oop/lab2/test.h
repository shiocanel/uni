#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "service.h"
#include "validator.h"

/*
 * verifica daca crearea si distrugerea unui obiect de tip product functioneaza corect.
 * pre: -
 * post: testul trece daca toate atributele sunt setate corect, altfel se opreste in assert.
 */
void testProduct();

/*
 * verifica functionalitatile de baza ale vectorului dinamic (creare, adaugare, distrugere).
 * pre: -
 * post: testul confirma daca dimensiunea si elementele sunt gestionate corect in memorie.
 */
void testVector();

/*
 * testeaza operatiile de stocare, cautare, actualizare si stergere din repository.
 * pre: -
 * post: se asigura ca schimbarile asupra datelor sunt persistente in vectorul intern.
 */
void testRepository();

/*
 * verifica logica de business pentru operatiile de tip creare, citire, actualizare si stergere.
 * pre: -
 * post: confirma integrarea corecta intre service si repository, inclusiv validarea unicitatii.
 */
void testServiceCRUD();

/*
 * testeaza toate cazurile de eroare si de succes pentru datele de intrare ale unui produs.
 * pre: -
 * post: se asigura ca datele invalide sunt respinse si cele valide sunt acceptate.
 */
void testValidator();

/*
 * verifica corectitudinea algoritmilor de sortare dupa pret si cantitate.
 * pre: -
 * post: confirma ordinea elementelor atat in mod crescator, cat si descrescator.
 */
void testSort();

/*
 * verifica functionalitatea de filtrare dupa producator, pret si cantitate.
 * pre: -
 * post: confirma ca vectorul rezultat contine doar elementele care indeplinesc criteriul.
 */
void testFilter();

/*
 * apeleaza succesiv toate suitele de teste unitare definite in program.
 * pre: -
 * post: afiseaza un mesaj de succes daca toate testele au trecut cu bine.
 */
void runAllTests();


#endif // !TEST_H
