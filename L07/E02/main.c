#include <stdio.h>
#include <malloc.h>
#include <time.h>

typedef enum{zaffiri, rubini, topazi, smeraldi} pietra;
static int k=1;
static int find=0;
typedef struct{
    int z,val_z;
    int t,val_t;
    int r,val_r;
    int s,val_s;
    int max_rip;
}collana;

collana *read_data(collana *test,int *n);
void solution(collana *test, int n);
int *recursive(int z, int r, int t, int s,collana test, int *sol, int n, int pos, int scelta,int *best_sol,int *costo_max);
void stampa(int *sol, int n, FILE *g);
int controllo_z_s(int *sol, int n);
void copia_sol(int *sol, int *best_sol, int n);
int calcola_costo(int z, int r, int t, int s, collana test,int n);

int main() {
    int n;
    collana *test;
    test = read_data(test,&n);
    if(test==NULL){
        printf("non è stato possibile aprire il file\n");
        return -1;
    }
    solution(test, n);
    free(test);
    return 0;
}

collana *read_data(collana *test, int *n){
    FILE *f;
    int i;
    f=fopen("collana.txt","r");
    if(f==NULL) return NULL;
    fscanf(f,"%d",n);
    test=malloc(*n*sizeof(collana));
    for(i=0;i<*n;i++){
        fscanf(f,"%d %d %d %d %d %d %d %d %d",&test[i].z,&test[i].r,&test[i].t,&test[i].s,
                &test[i].val_z,&test[i].val_r,&test[i].val_t,&test[i].val_s,&test[i].max_rip);
    }
    fclose(f);
    return test;
}

void solution(collana *test, int n){
    int i,dim,j,*sol,*best_sol,costo_max;
    FILE *g;
    g=fopen("risultati_collane.txt","w+");

    for(i=0;i<n;i++){
        dim=test[i].z+test[i].r+test[i].t+test[i].s;
        sol = malloc(dim*sizeof(int));
        best_sol = malloc(dim*sizeof(int));
        fprintf(g,"TEST #%d:\n",i+1);
        fprintf(g,"zaffiri : |%d| [%d], rubini : |%d| [%d], topazi : |%d| [%d], smeraldi : |%d| [%d];\n PIETRE TOTALI : |%d| {max_rip : |%d|}\n",
                test[i].z,test[i].val_z,test[i].r,test[i].val_r,test[i].t,test[i].val_t,test[i].s,test[i].val_s,dim,test[i].max_rip);
        find=0;
        costo_max=0;
        for(j=0;j<dim && sol != NULL && !find;j++){
            if(test[i].z!=0){
                k=1;
                sol = recursive(test[i].z-1,test[i].r,test[i].t,test[i].s,test[i],sol,dim-j,0,zaffiri,best_sol,&costo_max);
            }
            if(sol!=NULL && test[i].r!=0){
                k=1;
                sol = recursive(test[i].z,test[i].r-1,test[i].t,test[i].s,test[i],sol,dim-j,0,rubini,best_sol,&costo_max);
            }
            if(sol!=NULL && test[i].t!=0){
                k=1;
                sol = recursive(test[i].z,test[i].r,test[i].t-1,test[i].s,test[i],sol,dim-j,0,topazi,best_sol,&costo_max);
            }
            if(sol!=NULL && test[i].s!=0){
                k=1;
                sol = recursive(test[i].z,test[i].r,test[i].t,test[i].s-1,test[i],sol,dim-j,0,smeraldi,best_sol,&costo_max);
            }
        }
        stampa(best_sol,dim-j+1,g);
        fprintf(g,"    COSTO COLLANA : |%d|\n",costo_max);
        free(sol);
        free(best_sol);
    }
    fclose(g);
}

int *recursive(int z, int r, int t, int s, collana test, int *sol,int n, int pos, int scelta,int *best_sol,int *costo_max){
    int cost=0;
    sol[pos]=scelta;
    pos+=1;
    if(pos==n){
        if(controllo_z_s(sol,n)){
            cost= calcola_costo(z,r,t,s,test,n);
            if(cost>*costo_max){
                *costo_max=cost;
                copia_sol(sol,best_sol,n);
            }
            find=1;
        }
            return sol;
    }
        switch (scelta) {
            case zaffiri:
                if (z != 0 && k < test.max_rip){
                    k+=1;
                    sol = recursive(z-1, r, t, s,test, sol, n, pos, zaffiri,best_sol,costo_max);
                }
                if (r != 0 && sol!=NULL){
                    k=1;
                    sol = recursive(z, r-1, t, s,test, sol, n, pos, rubini,best_sol,costo_max);
                }
                break;
            case rubini:
                if (t != 0){
                    k=1;
                    sol = recursive(z, r, t-1, s,test, sol, n, pos, topazi,best_sol,costo_max);
                }
                if (s != 0 && sol!=NULL){
                    k=1;
                    sol = recursive(z, r, t, s - 1,test, sol, n, pos, smeraldi,best_sol,costo_max);
                }
                break;
            case topazi:
                if (r != 0){
                    k=1;
                    sol = recursive(z, r-1, t, s,test, sol, n, pos, rubini,best_sol,costo_max);
                }
                if (z != 0 && sol!=NULL){
                    k=1;
                    sol = recursive(z-1, r, t, s,test, sol, n, pos, zaffiri,best_sol,costo_max);
                }
                break;
            case smeraldi:
                if (s != 0 && k<test.max_rip){
                    k+=1;
                    sol = recursive(z, r, t, s - 1,test, sol, n, pos, smeraldi,best_sol,costo_max);
                }
                if (t != 0 && sol!=NULL){
                    k=1;
                    sol = recursive(z, r, t-1, s,test, sol, n, pos, topazi,best_sol,costo_max);
                }
                break;
            default:
                break;
        }

    return sol;
}

void stampa(int *sol, int n, FILE *g){
    int i;
    fprintf(g,"massimal lunghezza collana : |%d|\n",n );
    fprintf(g,"composizione : ");
    for(i=0;i<n;i++){
        switch(sol[i]){
            case zaffiri:
                fprintf(g,"z");
                break;
            case rubini:
                fprintf(g,"r");
                break;
            case topazi:
                fprintf(g,"t");
                break;
            case smeraldi:
                fprintf(g,"s");
                break;
            default:
                break;
        }
    }
}

int controllo_z_s(int *sol, int n){
    int i,n_z=0,n_s=0;
    for(i=0;i<n;i++){
        if(sol[i]==zaffiri) n_z++;
        if(sol[i]==smeraldi) n_s++;
    }
    if(n_z>n_s) return 0;
    else return 1;
}


int calcola_costo(int z, int r, int t, int s, collana test, int n){
    int cost=(test.z-z)*test.val_z + (test.r-r)*test.val_r + (test.t-t)*test.val_t +(test.s-s)*test.val_s;
    return cost;
}

void copia_sol(int *sol, int *best_sol, int n){
    int i;
    for(i=0;i<n;i++){
        best_sol[i]=sol[i];
    }
}

