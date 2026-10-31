#include <stdio.h>

int oglindit(char sir[], char ans[]);

int verifica(char sir[], char c);

int main(){
    char c = 'a';
    int n = 3;
    
    //printf("c = ");
    //scanf("%c", &c);
    
    //printf("n = ");
    //scanf("%n", &n);
    
    
    for(int i = 0; i < n; i++){
        char sir[31] = "";
        char ans[31] = "";

        printf("sir: ");
        scanf("%s", sir);
        
        int len = 0;
        len = oglindit(sir, ans);
        
        int ok = 0;
        ok = verifica(sir, c);
        
        printf("len = %d \n", len);
        printf("ok = %d \n", ok);
        printf("ogl = %s \n", ans);
        
        if(ok == 1){
            if(len % 2 == 0)
                printf("%s \n", sir);
            else
                printf("%s \n", ans);    
        }
    }
    
    return 0;
}