#include <stdio.h>
#include <malloc.h>
#include <time.h>
typedef enum{zaffiri, rubini, topazi, smeraldi} pietra;

typedef struct{
    int z;
    int t;
    int r;
    int s;
}collana;

collana *read_data(collana *test,int *n);
void solution(collana *test, int n);
int *recursive(int z, int r, int t, int s, int *sol, int n, int pos, int scelta, FILE *g);
void stampa(int *sol, int n, FILE *g);


int main() {
    int n;
    collana *test;
    test = read_data(test,&n);
    solution(test, n);
    free(test);
    return 0;
}

collana *read_data(collana *test, int *n){
    FILE *f;
    int i;
    f=fopen("collana.txt","r");
    fscanf(f,"%d",n);
    test=malloc(*n*sizeof(collana));
    for(i=0;i<*n;i++){
        fscanf(f,"%d %d %d %d",&test[i].z,&test[i].r,&test[i].t,&test[i].s);
    }

    fclose(f);
    return test;
}

void solution(collana *test, int n){
    int i,dim,j,*sol;
    FILE *g;
    clock_t inizio, fine;
    double tempo,tottempo=0;
    g=fopen("risultati_collane.txt","w+");

    for(i=0;i<n;i++){
        dim=test[i].z+test[i].r+test[i].t+test[i].s;
        sol = malloc(dim*sizeof(int));
        fprintf(g,"TEST #%d:\n",i+1);
        fprintf(g,"zaffiri : |%d|, rubini : |%d|, topazi : |%d|, smeraldi : |%d|; PIETRE TOTALI : |%d|\n",test[i].z,test[i].r,test[i].t,test[i].s,dim);
        inizio=clock();
        for(j=0;j<dim && sol != NULL;j++){
            if(test[i].z!=0){
                sol = recursive(test[i].z-1,test[i].r,test[i].t,test[i].s,sol,dim-j,0,zaffiri,g);
            }
            if(sol!=NULL && test[i].r!=0){
                sol = recursive(test[i].z,test[i].r-1,test[i].t,test[i].s,sol,dim-j,0,rubini,g);
            }
            if(sol!=NULL && test[i].t!=0){
                sol = recursive(test[i].z,test[i].r,test[i].t-1,test[i].s,sol,dim-j,0,topazi,g);
            }
            if(sol!=NULL && test[i].s!=0){
                sol = recursive(test[i].z,test[i].r,test[i].t,test[i].s-1,sol,dim-j,0,smeraldi,g);
            }
        }
        fine=clock();
        tempo= (double) (fine-inizio)/CLOCKS_PER_SEC;
        tottempo +=tempo;
        fprintf(g,"tempo impiegato %f secondi\n\n", tempo);
        free(sol);
    }
    printf("tot tempo di esec : %f", tottempo);
    fclose(g);
}

int *recursive(int z, int r, int t, int s, int *sol,int n, int pos, int scelta,FILE *g){
    sol[pos]=scelta;
    pos+=1;
    if(pos==n){
        stampa(sol,n,g);
        return NULL;
    }
    if(sol!=NULL) {
        switch (scelta) {
            case zaffiri:
                if (r != 0) sol = recursive(z, r-1, t, s, sol, n, pos, rubini,g);
                if (z != 0 && sol!=NULL) sol = recursive(z-1, r, t, s, sol, n, pos, zaffiri,g);
                break;
            case rubini:
                if (t != 0) sol = recursive(z, r, t-1, s, sol, n, pos, topazi,g);
                if (s != 0 && sol!=NULL) sol = recursive(z, r, t, s - 1, sol, n, pos, smeraldi,g);
                break;
            case topazi:
                if (r != 0) sol = recursive(z, r-1, t, s, sol, n, pos, rubini,g);
                if (z != 0 && sol!=NULL) sol = recursive(z-1, r, t, s, sol, n, pos, zaffiri,g);
                break;
            case smeraldi:
                if (t != 0) sol = recursive(z, r, t-1, s, sol, n, pos, topazi,g);
                if (s != 0 && sol!=NULL) sol = recursive(z, r, t, s - 1, sol, n, pos, smeraldi,g);
                break;
            default:
                break;
        }
    }
    return sol;
}

void stampa(int *sol, int n, FILE *g){
    int i;
    fprintf(g,"MASSIMA DIMENSIONE COLLANA : |%d|\n",n );
    for(i=0;i<n;i++){
        switch(sol[i]){
            case 0:
                fprintf(g,"z-");
                break;
            case 1:
                fprintf(g,"r-");
                break;
            case 2:
                fprintf(g,"t-");
                break;
            case 3:
                fprintf(g,"s-");
                break;
            default:
                break;
        }
    }
    fprintf(g,"\n");
}
