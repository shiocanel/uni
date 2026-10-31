#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 10000

int sir_de_numere(int *ans, int n){
    /*
    genereaza o lista de numere consecutive ai suma este egala cu n
    parametrii:
        - ans (pointer catre o lista de int) - lista un salvez rezultatul
        - n (int) - n cerut de utilizator

    preconditii:
        - ans != NULL 
        - n numar natural intreg > 0
    postconditii:
        - ans = lista cu numerele naturale consecutive daca este posibil
        - returneaza -1 daca este imposibil pentru n dat sau
          sz (int) dimensiunea lui ans (lista de numere)
    */

    int sz = 0;
    for(int i = 1; i < n; i++){
        int x = i;
        int sum = 0;

        sz = 0;
        while(sum < n){
            sum += x;
            ans[sz++] = x;
            x++;
        }

        if(sum == n)
            return sz;
    }
    // ex8 -> next lab

    return -1;
}

void afis_rezultat(int *ans, int sz, int n){
    /*
    afiseaza rezlultatul pentru un n
    parametrii:
        - ans (pointer catre o lista de int) - lista un salvez rezultatul
        - sz (int) - dimensiunea listei sau -1 daca nu este posibil de generat o lista
        - n (int) - n cerut de utilizator
    preconditii:
        - ans != NULL 
        - sz (int) 
        - n numar natural intreg > 0
    postconditii:
        afiseaza ans cu lista cu numerele naturale consecutive daca este posibil
        sau un mesaj daca este imposibil
    */

    if(sz <= 0)
        printf("Numarul n = %d nu poate fi reprezentat ca o suma de numere consecutive!!!\n", n);
    else if(sz > 0){
        printf("Numarul n = %d poate fi reprezentat ca: ", n);
        for(int i = 0; i < sz; i++)
            printf("%d ", ans[i]);
        printf("\n");
    }
}

int main(int argc, char const *argv[]){
    int n;
    int ans[MAX_N];
    int sz = 0;

    while(1){
        printf("==Menu==\n");
        printf("1) Citeste n\n");
        printf("2) N poate fi reprezentat cu suma de numere consecutive:\n");
        printf("0) Exit\n");
        printf("==Menu==\n");

        printf("Optiune: \n");
        int t = -1;
        scanf("%d", &t);

        if(t == 1){
            printf("n: ");
            scanf("%d", &n);
        }
        else if(t == 2){
            if(n <= 0){
                printf("Te rog sa introduci un n numar natural!!!\n");
                continue;
            }

            sz = sir_de_numere(ans, n);

            afis_rezultat(ans, sz, n);
        }
        else if(t == 0){
            printf("Sa fie cu sanatate!\n");
            break;
        }
        else{
            printf("Optiune invalida!!\n");
        }
    }


    return 0;
}
