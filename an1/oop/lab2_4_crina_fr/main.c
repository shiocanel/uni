#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "service.h"

void afiseaza_lista_tranzactii(Vector* v) {
    if (v == NULL || size(v) == 0) {
        printf("\nNu exista tranzactii de afisat.\n");
        return;
    }
    printf("\n--- LISTA TRANZACTII ---\n");
    for (int i = 0; i < size(v); i++) {
        Tranzactie* t = (Tranzactie*)get(v, i);
        printf("[%d] Zi: %2d | Suma: %10.2f | Tip: %s | Desc: %s\n",
            i, t->ziua, t->suma, (t->tip == INTRARE ? "Intrare" : "Iesire"), t->descriere);
    }
}

void print_menu() {
    printf("\n========= GESTIUNE CONT BANCAR =========\n");
    printf("1. Adaugare tranzactie\n");
    printf("2. Afisare toate tranzactiile\n");
    printf("3. Stergere tranzactie\n");
    printf("4. Modificare tranzactie\n");
    printf("5. Filtrare (Suma minima)\n");
    printf("6. Sorteaza dupa suma cresc\n");
    printf("7. Sorteaza dupa suma descresc\n");
    printf("8. Sorteaza dupa zi cresc\n");
    printf("9. Sorteaza dupa zi descresc\n");
    printf("10. Undo\n");
    printf("11. Delete By Tip\n");
    printf("0. Iesire\n");
    printf("========================================\n");
    printf("Alegeti o optiune: ");
}

void run() {
    Service* serv = createService();
    int optiune = -1;

    while (optiune != 0) {
        print_menu();
        if (scanf("%d", &optiune) != 1) {
            printf("Te rog introdu un numar valid.\n");
            while (getchar() != '\n');
            continue;
        }

        if (optiune == 1) {
            int zi, tip;
            double suma;
            char desc[100];
            printf("Ziua (1-31): "); 
            scanf("%d", &zi);
            printf("Suma: "); 
            scanf("%lf", &suma);
            printf("Tip (1-Intrare, 2-Iesire): "); 
            scanf("%d", &tip);
            printf("Descriere: "); 
            scanf(" %[^\n]", desc);

            if (adauga_srv(serv, zi, suma, tip, desc))
                printf("Succes: Tranzactie adaugata!\n");
            else
                printf("Eroare: Date invalide!\n");

        }
        else if (optiune == 2) {
            afiseaza_lista_tranzactii(serv->cont_curent->tranzactii);

        }
        else if (optiune == 3) {
            int idx;
            afiseaza_lista_tranzactii(serv->cont_curent->tranzactii);
            printf("Indexul tranzactiei de sters: ");
            scanf("%d", &idx);
            if (sterge_srv(serv, idx))
                printf("Succes: Tranzactie stearsa!\n");
            else
                printf("Eroare: Index invalid!\n");

        }
        else if (optiune == 4) {
            int idx, zi, tip;
            double suma;
            char desc[100];
            afiseaza_lista_tranzactii(serv->cont_curent->tranzactii);
            printf("Indexul de modificat: "); 
            scanf("%d", &idx);
            printf("Zi noua: "); 
            scanf("%d", &zi);
            printf("Suma noua: "); 
            scanf("%lf", &suma);
            printf("Tip nou: "); 
            scanf("%d", &tip);
            printf("Descriere noua: "); 
            scanf(" %[^\n]", desc);

            if (modifica_srv(serv, idx, zi, suma, tip, desc))
                printf("Succes: Tranzactie modificata!\n");
            else
                printf("Eroare: Date sau index invalid!\n");

        }
        else if (optiune == 5) {
            double prag;
            printf("Afiseaza tranzactii cu suma mai mare sau egala cu: ");
            scanf("%lf", &prag);
            Vector* filtrate = filtreaza_suma_minima_srv(serv, prag);
            afiseaza_lista_tranzactii(filtrate);

            destroyVector(filtrate);
        }
        else if (optiune == 6) {
            Vector* sortate = sorteaza_srv(serv, cmp_suma_cresc);
            afiseaza_lista_tranzactii(sortate);
            destroyVector(sortate);
        }
        else if (optiune == 7) {
            Vector* sortate = sorteaza_srv(serv, cmp_suma_desc);
            afiseaza_lista_tranzactii(sortate);
            destroyVector(sortate);
        }
        else if (optiune == 8) {
            Vector* sortate = sorteaza_srv(serv, cmp_zi_cresc);
            afiseaza_lista_tranzactii(sortate);
            destroyVector(sortate);
        }
        else if (optiune == 9) {
            Vector* sortate = sorteaza_srv(serv, cmp_zi_desc);
            afiseaza_lista_tranzactii(sortate);
            destroyVector(sortate);
        }
        else if (optiune == 10) {
            if (undo(serv))
                printf("Succes: Undo realizat!\n");
            else
                printf("Eroare: Nu se mai poate face undo!\n");
        }
        else if (optiune == 11) {
            int tip;
            printf("Delete by Tip: \n");
            scanf("%d", &tip);

            delete_by_tip_srv(serv, tip);
        }
    }

    destroyService(serv);
}

#include "teste.h"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    ruleaza_toate_testele();

    //int x;

    // delete by name:
    // contains a name

    run(); // ex2

    printf("Aplicatie inchisa. Verificati 'Output' in VS pentru memory leaks.\n");
    return 0;
}