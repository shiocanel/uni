#include <stdio.h>

int main(int argc, char const *argv[]){
    int sum = 0, n, x;

    printf("n: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){    
        printf("x: ");
        scanf("%d", &x);
        sum += x;
    }

    printf("Suma numerelor: %d", sum);

    return 0;
}
