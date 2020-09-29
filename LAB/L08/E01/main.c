#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
    int inizio;
    int fine;
    int scelta;
}att;
int count=0;

att *read_data(att *Events, int *n);
void ActivSel(int N, att *v);
int *recursive_sel(int n, att *v,int pos, int *sol, int prec, int dim,int *b_sol, int *m_t);
void stampa(att *v, int *sol, int n);
int conta(att *v, int *sol, int n);
void copia_sol(int *sol, int *b_sol, int n);

int main() {
    int n;
    att *Events;
    Events = read_data(Events, &n);
    ActivSel(n,Events);
    free(Events);
    return 0;
}

att *read_data(att *Events, int *n){
    FILE *f;
    char buff[50];
    int i;
    printf("filename\n");
    scanf("%s",buff);
    f=fopen(buff,"r");
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
    else{
        fclose(f);
        return NULL;
    }
}

void ActivSel(int N, att *v){
    int *sol = calloc(N, sizeof(int));
    int *b_sol=calloc(N, sizeof(int));
    int i,m_t=0;
    for(i=0;i<N;i++){
        sol[i]= b_sol[i]=-1;
    }
    for(i=0;i<N;i++){
        sol=recursive_sel(N-i,v,0,sol,0,N,b_sol,&m_t);
    }
    printf("SOLUZIONE OTTIMALE :\n");
    stampa(v,b_sol,N);
    printf("tempo totale : %d\n",m_t);
    printf("COUNT : %d\n",count);
    free(sol);
    free(b_sol);
}

int *recursive_sel(int n, att *v, int pos, int *sol, int prec, int dim, int *b_sol, int *m_t){
    count++;
    int i,t;
    if(pos==n){
        t=conta(v,sol,dim);
        if(t>*m_t){
            *m_t=t;
            copia_sol(sol,b_sol,dim);
        }
        return sol;
    }
    for(i=0;i<dim;i++){
        if(pos==0){
            sol[pos]=i;
            v[i].scelta=1;
            sol = recursive_sel(n,v,pos+1,sol,v[i].fine,dim,b_sol,m_t);
            sol[pos]=-1;
            v[i].scelta=0;
        }
        else {
            if ((v[i].inizio >= prec )&& (v[i].scelta==0)){
                sol[pos]=i;
                v[i].scelta=1;
                sol = recursive_sel(n,v,pos+1,sol,v[i].fine,dim,b_sol,m_t);
                sol[pos]=-1;
                v[i].scelta=0;
            }
        }

    }
    return sol;
}

int conta(att *v, int *sol, int n){
    int i,t=0;
    for(i=0;i<n;i++){
        if(sol[i]!=-1){
            t+=(v[sol[i]].fine-v[sol[i]].inizio);
        }
    }
    return t;
}

void stampa(att *v, int *sol, int n){
    int i;
    for(i=0;i<n;i++){
        if (sol[i] != -1){
            printf("(%d , %d) ", v[sol[i]].inizio, v[sol[i]].fine);
        }
    }
    printf("\n");

}
void copia_sol(int *sol, int *b_sol, int n){
    int i;
    for(i=0;i<n;i++){
        b_sol[i]=sol[i];
    }
}