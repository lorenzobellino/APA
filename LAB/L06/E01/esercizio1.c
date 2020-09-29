#include<stdio.h>
#include<stdlib.h>

#define filename "grafo2.txt"

int ** read_and_store_data(int *N, int *E, int **edges);
void vertex_cover(int E,int N, int *sol, int n, int pos, int start, int **edges);
void print_solution(int *sol, int n);
void free_graph(int *sol, int **edges, int E);
int min(int a, int b);

int main(){

    int N,E,i;
    int **edges,*sol,*vertex;
    edges = read_and_store_data(&N,&E,edges);
    sol=malloc(N*sizeof(int));
    for(i=1;i<=N;i++)   vertex_cover(E,N,sol,i,0,0,edges);
    free_graph(sol, edges, E);
    return 0;
}

int ** read_and_store_data(int *N, int *E, int **edges){
    FILE *f;
    int i;
    f=fopen(filename,"r");
    if(f==NULL) return NULL;
    fscanf(f,"%d %d",N,E);
    edges=malloc(*E*sizeof(*edges));
    for(i=0;i<*E;i++){
        edges[i]=malloc(2*sizeof(int));
        fscanf(f,"%d %d\n", &edges[i][0], &edges[i][1]);
    }
    fclose(f);
    return edges;
}

void vertex_cover(int E,int N, int *sol, int n, int pos, int start, int **edges){
    int i=0,j=0,wrong=0;
    /*per ogni arco controlllo che sia coperto da almeno un nodo della soluzione
      se trovo un nodo che soddisfa questa condizione allora controllo l'arco
      successivo,altrimenti passo al nodo successivo
      se trovo un arco che non è coperto da nessun nodo allora la soluzione non 
      è valida e viene scartata
    */
    if(pos==n){
        for(i=0;i<E && !wrong;i++){
            for(j=0;j<n;j++){
                if(sol[j]==edges[i][0] || sol[j] == edges[i][1]){
                    wrong=0;
                    break;
                }
                else wrong=1;
            }
        }
        if(!wrong) print_solution(sol,n);
        return;
    }

    for(i=start;i<N;i++){
	    sol[pos]=i;
	    vertex_cover(E,N,sol,n,pos+1,i+1,edges);
    }
    return;
}

void print_solution(int *sol, int n){
    int i=0;
    printf("{");
    for(i=0;i<n;i++){
        printf("%d, ", sol[i]);
    }
    printf("\b\b}\n");
}

void free_graph(int *sol, int **edges, int E){
    int i;
    free(sol);
    for(i=0;i<E;i++){
        free(edges[i]);
    }
    free(edges);
}