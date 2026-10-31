#include <stdio.h>

int rezolva(int a, int b, int c);

int main()
{
    int a = 0, b = 0, c = 0, ans = 0;

    printf("a=");
    scanf("%d", &a);

    printf("b=");
    scanf("%d", &b);

    printf("c=");
    scanf("%d", &c);

    ans = rezolva(a, b, c);
    
    printf("Rezultatul este: %d", ans);

    return 0;
}