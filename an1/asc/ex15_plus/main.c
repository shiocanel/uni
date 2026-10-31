#include <stdio.h>

void rezolva(int n, char ans[]);

void citesteSir(char sir[]);

int main(){
    int n;
    
    printf("n = ");
    scanf("%d", &n);
    
    char ans[303] = "";
    
    rezolva(n, ans);

    return 0;
}

void citesteSir(char sir[]){
    printf("sir: ");
    fgets(sir, sizeof(sir), stdin);
}