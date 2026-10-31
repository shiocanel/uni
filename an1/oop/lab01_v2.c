#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 10000

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

void genereaza(int ans[], int n){
    /*
    genereaza primele n numere prime si le salveaza
    parametri: solver (pointer de tip NumerePrime)
    preconditii: solver != NULL
    postconditii: Primele MAX_N numere prime sunt salvate in solver.ans iar
                solver.stare <-- 1
    */

    int cur = 0;
    int x = 2;
    while(cur < n){
        if(prim(x))
            ans[cur++] = x;
        x++;
    }
}

int main(int argc, char const *argv[]){
    int n = -1;
    int ans[MAX_N];
    bool ok = 0;
    int temp = 0;

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
            printf("n [0..%d]: ", MAX_N - 1);
            temp = citeste_n();

            if(temp >= 0 && temp < MAX_N){
                n = temp;
                ok = 1;
            }
            else{
                ok = 0;
                n = -2;
            }
        }
        else if(t == 2){
            if(n == -1)
                printf("Nu ai citit n!!\n");
            else if(!ok)
                printf("Nu putem genera pentru un astfel de n: %d \n", temp);
            else{
                genereaza(ans, n);            

                printf("%d numere prime: ", n);
                for(int i = 0; i < n; i++)
                    printf("%d ", ans[i]);
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
