#include<stdio.h>
#include<stdlib.h>

int gdc(int a, int b){
    int tmp;
    if(a==b) return a;
    if(a<b){
        tmp=a;
        a=b;
        b=tmp;
    }

    if(a%2==0 && b%2==0) return 2*gdc(a/2, b/2);
    
    if(a%2==1 && b%2==0) return gdc(a,b/2);
    
    if(a%2==0 && b%2==1) return gdc(a/2, b);

    return gdc((a-b)/2, b);
}

int main(int argc, char *argv[]){
    int a,b,d;
    printf("due interi :\n");
    scanf("%d %d", &a, &b);
    printf("il massimo comun divisore e' : ");
    d=gdc(a,b);
    printf("%d\n",d);
    return 0;
}
