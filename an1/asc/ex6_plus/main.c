#include <stdio.h>

void citesteSir(char sir[]);

int concateneaza(char sir1[], char sir2[], char sir3[], char ans[]);

int main(){
    char sir1[101] = "";
    char sir2[101] = "";
    char sir3[101] = "";
    char ans[303] = "";
    
    citesteSir(sir1);
    scanf("%s", &sir1);
    
    citesteSir(sir2);
    scanf("%s", &sir2);
    
    citesteSir(sir3);
    scanf("%s", &sir3);
    
    int len = concateneaza(sir1, sir2, sir3, ans);
    
    printf("Lungimea sirului: %d", len);
    printf("Sirul rezultat: %s", ans);

    return 0;
}