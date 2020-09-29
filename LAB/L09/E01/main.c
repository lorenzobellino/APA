#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int inizio;
    int fine;
    int scelta;
}att;

att *read_data(att *Events, int *n);
att *ordina(att *Events, int n);
void ActivSel(att *v, int N);
void dinamic_sol(att *v, int n, int *sol, int *durata);
void stampa_sol(att *v,int *sol,int last);


int main() {
    int n;
    att *Events;
    Events = read_data(Events, &n);
    Events = ordina(Events, n);
    ActivSel(Events,n);
    free(Events);
    return 0;
}

att *read_data(att *Events, int *n){
    FILE *f;
    int i;
    f=fopen("eventi.txt","r");
    if(f!=NULL){
        fscanf(f,"%d",n);

        Events = malloc((*n)*sizeof(att));
        for(i=0;i<*n;i++){
            fscanf(f,"%d %d",&Events[i].inizio, &Events[i].fine);
            Events[i].scelta=0;
        }
        fclose(f);
        return Events;
    }
    else return NULL;
}

att *ordina(att *Events, int n){
    int i,j;
    att tmp;
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(Events[i].inizio > Events[j].inizio){
                tmp=Events[i];
                Events[i]=Events[j];
                Events[j]=tmp;
            }
        }
    }
    return Events;
}

void ActivSel(att *v, int N){
    int *sol, *durata;
    sol=calloc(N,sizeof(int));
    durata = calloc(N,sizeof(int));
    dinamic_sol(v,N,sol,durata);
    free(sol);
    free(durata);
}

void dinamic_sol(att *v, int n, int *sol, int *durata){
    int i,j,ris=1,last=0;
    sol[0]=-1;
    durata[0]=v[0].fine-v[0].inizio;
    for(i=1;i<n;i++){
        durata[i]=v[i].fine - v[i].inizio;
        sol[i]=-1;
        for(j=0;j<i;j++){
            if((v[j].fine<=v[i].inizio) && (v[i].fine-v[i].inizio +durata[j]>durata[i])){
                durata[i] = durata[j] + v[i].fine - v[i].inizio;
                sol[i]=j;
            }
            if(ris < durata[i]){
                ris=durata[i];
                last=i;
            }

        }
    }
    printf("lista eventi massimale : ");
    stampa_sol(v,sol,last);
    printf("\ndi lunghezza massima : %d",ris);

}

void stampa_sol(att *v,int *sol,int last){
    if(sol[last]==-1){
        printf("(%d , %d) ", v[last].inizio, v[last].fine);
        return;
    }
    stampa_sol(v,sol,sol[last]);
    printf("(%d , %d) ", v[last].inizio, v[last].fine);
}