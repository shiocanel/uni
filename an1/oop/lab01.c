#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 10000

typedef struct NumerePrime{
    int n;
    int ans[MAX_N];
    int stare; // -1 n nu este citit; 0 n este citit; 1 ans este deja generat
} NumerePrime;

int citeste_n(){
    /*
    citeste un numar intreg
    parametri: void
    preconditii: utilizatorul introduce o valoare
    postconditii: returneaza valoare citita
    */
    int n;
    scanf("%d", &n);

    return n;
}

bool prim(int x){
    /*
    verifica primalitatea unui numar
    parametri: x (int)
    preconditii: x sa fie un numar intreg
    postconditii: returneaza true daca x este prim, si false in caz contrar
    */

    if(x < 2)
        return false;

    for(int i = 2; i * i <= x; i++)
        if(x % i == 0)
            return false;
    return true;
}

void genereaza(NumerePrime *solver){
    /*
    genereaza primele MAX_N numere prime si le salveaza
    parametri: solver (pointer de tip NumerePrime)
    preconditii: solver != NULL
    postconditii: Primele MAX_N numere prime sunt salvate in solver.ans iar
                solver.stare <-- 1
    */

    int cur = 0;
    int x = 2;
    while(cur < MAX_N){
        if(prim(x))
            solver->ans[cur++] = x;
        x++;
    }

    solver->stare = 1;
}

int main(int argc, char const *argv[]){
    NumerePrime solver;
    solver.stare = -1;

    while(1){
        printf("==Menu==\n");
        printf("1) Citeste n\n");
        printf("2) Genereaza primele n numere prime\n");
        printf("0) Exit\n");
        printf("==Menu==\n");

        printf("Optiune: \n");
        int t = -1;
        scanf("%d", &t);

        if(t == 1){
            printf("n [0..%d]: ", MAX_N -1);
            solver.n = citeste_n();
            solver.stare = 0;
        }
        else if(t == 2){
            if(solver.stare == -1)
                printf("Nu s-a citit n!!\n");
            else if(solver.n <= 0)
                printf("Nu pot genera pentru n: %d \n", solver.n);
            else{
                if(solver.stare == 0)
                    genereaza(&solver);

                printf("%d numere prime: ", solver.n);
                for(int i = 0; i < solver.n; i++)
                    printf("%d ", solver.ans[i]);
                printf("\n");
            }
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
