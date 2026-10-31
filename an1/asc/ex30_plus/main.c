#include <stdio.h>

void inverseaza(char sir1[], char ans[]);

int main(){
    char sir[100] = "";
    char ans[100] = "";
    
    printf("Citeste o propozitie: ");
    fgets(sir, sizeof(sir), stdin);
    
    inverseaza(sir, ans);
    
    printf("Cuvintele inversate: %s", ans);


    return 0;
}