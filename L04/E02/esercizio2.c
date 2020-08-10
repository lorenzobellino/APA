#include <stdio.h>
#define N 20
 
int majority(int *vett, int n);
int conta(int *vett, int n, int x);
 
int main(){
    int maggioritario,n,i,v[N];
    printf("quanti elementi nel vettore?\n");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&v[i]);
    }
    maggioritario=majority(v,n);
    printf("Elemento maggioritario: %d\n", maggioritario);
    return 0;
}
 
int majority(int *vett, int n){
    int majorityL, majorityR, k, contaL, contaR;
    if (n==1){
        return vett[0];
    }
    if (n==2){
        if (vett[0]==vett[1]){
            return vett[0];
        }
        else{
            return -1;
        }
    }
    k=n/2;
    majorityL=majority(vett,k);
    if (n%2==0){
        majorityR=majority(&vett[k],k);
    }
    majorityR=majority(&vett[k],k+1);
    if (majorityL==majorityR){
        return majorityL;
    }
    contaL=conta(vett,n,majorityL);
    contaR=conta(vett,n,majorityR);
    if (contaL>k){
        return majorityL;
    }
    else if (contaR>k){
        return majorityR;
    }
    else {
        return -1;
    }
}

int conta(int *vett, int n, int x){
    int i,count=0;
    for (i=0;i<n;i++){
        if (vett[i]==x){
            count++;
        }
    }
    return count;
}