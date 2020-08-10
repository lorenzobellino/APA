#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// STRUTTURE DATI : non visibili al main
typedef struct node *link;
struct node { int v; int wt; link next;};
struct graph { int V; int E; link *ladj; ST tab; link z; };

//FUNZIONI LOCALI A graph.c
static link New(int v, int wt, link next);
static Edge create_edge(int id1, int id2, int peso);
static void insert_edge(Graph G, Edge edge);
static void removeE(Graph G,Edge e);
static int *TS_dag(Graph G);
static void TS_dfsR(Graph G, int v, int *ts, int *pre, int *time);
static void relaxation(int *ts, Graph G, int id);

//STANDARD PER LA CREAZIONE E DISTRUZIONE DI ARCHI

static link New(int v, int wt, link next) {
    link x;
    x = malloc(1*sizeof(*x));
    if (x == NULL) return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

static Edge create_edge(int id1, int id2, int peso){
    Edge E;
    E.v=id1;
    E.w=id2;
    E.wt=peso;
    return E;
}

static void insert_edge(Graph G, Edge edge){
    int v = edge.v, w = edge.w, wt = edge.wt;
    G->ladj[v] = New(w,wt,G->ladj[v]);
    G->E++;
}

static void removeE(Graph G,Edge e){
    int v=e.v, w=e.w;
    link x;
    if (G->ladj[v]->v==w){
        G->ladj[v]=G->ladj[v]->next;
        G->E--;
    }
    else {
        for(x=G->ladj[v]; x!=G->z; x=x->next){
            if(x->next->v==w){
                x->next=x->next->next;
                G->E--;
            }
        }
    }
}

//FUNZIONI STANDARD PER  IL TOPOLOGICAL SORTING DI UN DAG

static int *TS_dag(Graph G){
    int v, time = 0, *pre, *ts; //time serve per contare solo l'ordine di  completamento
                                //di un vertice, non ci servono informazioni sul tempo di scoperta
    pre = malloc(G->V*sizeof(int)); //marcamento degli archi visitati
    ts = malloc(G->V*sizeof(int));  //vettore di vertici ordinati
    for (v=0; v < G->V; v++){
        pre[v] = -1; ts[v] = -1;
    }
    for (v=0; v < G->V; v++){
        if (pre[v]== -1) TS_dfsR(G, v, ts, pre, &time);
    }
    return ts;
}

static void TS_dfsR(Graph G, int v, int *ts, int *pre, int *time){
    link t;
    pre[v] = 0;
    for(t = G->ladj[v]; t != G->z; t=t->next){
        if(pre[t->v]==-1) TS_dfsR(G, t->v, ts, pre, time);
    }
    ts[(*time)++] = v; //se il vertice non ha piu archi disponibili viene
                        // inserito nel vettore finale già ordinato fino
                        // alla casella di indice 'time' e il contatore di pempo aumentato
}

//RELAZATION PER CAMMINI MASSIMO IN UN DAG

static void relaxation(int *ts, Graph G, int id){
    int i,v;
    link t;
    int *fn = malloc(G->V*sizeof(int));     //vettore di padri dei nodi
    int *max_d = malloc(G->V * sizeof(int)); // vettore per segnare la distanzta massima percorribile ver raggiungere il vertice
    //inizializzazione
    for(i=0;i<G->V;i++){
        fn[i]=-1;
        max_d[i]=-1;
    }
    //inizializzo il vertice di partenza
    fn[id]=id;
    max_d[id]=0;
    //per ogni vertice seguendo l'ordine topologico:
    for(i=1;i<=G->V;i++){
        v=ts[(G->V)-i];
        if(fn[v]!=-1){ //se il vertice non ha padri:
            //per ogni arco possibile partendo dall'arco v:
            for(t=G->ladj[v];t!=G->z;t=t->next){
                //applico la relaxation
                if(max_d[v]+t->wt > max_d[t->v]){
                    max_d[t->v]= max_d[v]+t->wt;
                    fn[t->v]=v;
                }
            }
        }
    }
    for(i=0;i<G->V;i++) printf("%s->%s peso massimo : [%d]\n",STsearchbyindex(G->tab,id),STsearchbyindex(G->tab,i),max_d[i]);
}

//FUNZIONI STANDARD DELL'ADT GRAFO

Graph GRAPH_load(char *filename){
    Graph G;
    int v,i,peso,id1,id2;
    char label1[30], label2[30];
    FILE *f;
    f=fopen(filename,"r");
    fscanf(f,"%d",&v);
    G = GRAPH_init(v);
    if(G==NULL) return NULL;
    for(i=0;i<v;i++){
        fscanf(f,"%s",label1);
        STinsert(G->tab,label1,i);
    }
    while(fscanf(f,"%s %s %d",label1,label2,&peso)==3){
        id1=STsearch(G->tab,label1);
        id2=STsearch(G->tab,label2);
        if(id1>=0 && id2>=0){
            insert_edge(G, create_edge(id1,id2,peso));
        }
    }
    fclose(f);
    return G;
}

Graph GRAPH_init(int v){
    Graph G;
    int i;
    G = malloc(sizeof *G);
    if (G == NULL) return NULL;
    G->V=v;
    G->E=0;
    G->z=New(-1,0,NULL);
    if(G->z==NULL) return NULL;
    G->ladj = malloc((G->V)*sizeof(link));
    if(G->ladj==NULL) return NULL;
    for(i=0;i<G->V;i++){
        G->ladj[i] = G->z;
    }
    G->tab = STinit(v);
    if(G->tab==NULL) return NULL;
    return G;
}

void GRAPH_edges(Graph G, Edge *a){
    int v,E=0;
    link t;
    for (v=0;v<G->V;v++){
        for (t=G->ladj[v]; t!=G->z; t=t->next){
            a[E++]=create_edge(v,t->v,t->wt);
        }
    }
}

void GRAPH_remove(Graph G, int id1, int id2){
    removeE(G, create_edge(id1,id2,0));
}

void GRAPH_dfs(Graph G){
    int v,time=0,*pre,*post,*st;
    pre=malloc(G->V* sizeof(int));
    post=malloc(G->V* sizeof(int));
    st=malloc(G->V* sizeof(int));
    for(v=0;v<G->V;v++){
        pre[v]=-1; post[v]=-1; st[v]=-1;
    }
    printf("\nTIPO DI ARCHI:\n");
    for(v=0;v<G->V;v++){
        if (pre[v]==-1){
            GRAPH_dfsR(G,create_edge(v,v,1),&time,pre,post,st);
        }
    }
}

void GRAPH_dfsR(Graph G, Edge e, int *time, int *pre, int *post,int *st){
    link t;
    int v,w=e.w;
    Edge x;

    if (e.v!=e.w){
        printf("(%s, %s): T\n",STsearchbyindex(G->tab,e.v),STsearchbyindex(G->tab,e.w));
    }
    st[e.w]=e.v;
    pre[w]=(*time)++;
    for(t=G->ladj[w];t!=G->z;t=t->next){
        if(pre[t->v]==-1){
            GRAPH_dfsR(G,create_edge(w,t->v,1),time,pre,post,st);
        }
        else {
            v=t->v;
            x=create_edge(w,v,1);
            if (post[v]==-1){
                printf("(%s, %s): B\n",STsearchbyindex(G->tab,x.v),STsearchbyindex(G->tab,x.w));
            }
            else {
                if (pre[v]>pre[w]){
                    printf("(%s, %s): F\n",STsearchbyindex(G->tab,x.v),STsearchbyindex(G->tab,x.w));
                }
                else {
                    printf("(%s, %s): C\n",STsearchbyindex(G->tab,x.v),STsearchbyindex(G->tab,x.w));
                }
            }
        }
    }
    post[w]=(*time)++;
}

void GRAPH_free(Graph G){
    int v;
    link t,next;
    for (v=0;v<G->V;v++){
        for (t=G->ladj[v];t!=G->z;t=next){
            next=t->next;
            free(t);
        }
    }
    ST_free(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

//DFS modificata per conoscere il numero di archi back nel grafo

int dfs_mod(Graph G){
    int v,time=0,*pre,*post,*st,bcount=0;
    pre=malloc(G->V* sizeof(int));
    post=malloc(G->V* sizeof(int));
    st=malloc(G->V* sizeof(int));
    for(v=0;v<G->V;v++){
        pre[v]=-1; post[v]=-1; st[v]=-1;
    }
    for(v=0;v<G->V;v++){
        if (pre[v]==-1){
            dfs_R_mod(G,create_edge(v,v,1),&time,pre,post,st,&bcount);
        }
    }
    free(pre);
    free(post);
    free(st);
    return bcount;
}

void dfs_R_mod(Graph G,Edge e, int *time, int *pre, int *post,int *st,int *bcount){
    link t;
    int v,w=e.w;
    st[e.w]=e.v;
    pre[w]=(*time)++;
    for(t=G->ladj[w];t!=G->z;t=t->next){
        if(pre[t->v]==-1){
            dfs_R_mod(G,create_edge(w,t->v,1),time,pre,post,st,bcount);
        }
        else {
            v=t->v;
            if (post[v]==-1){
                (*bcount)++; //counter per gli archi di tipo back
            }
        }
    }
    post[w]=(*time)++;
}

//funzioni specifiche per l'esercizio

void graph_to_DAG(Graph G){
    int i,find=0,best_del;
    int j, id1, id2, peso;
    Edge *a = malloc(G->E * sizeof(Edge)); //vettore di archi
    Edge *removed = malloc(G->E * sizeof(Edge)); // vettore di possibili archi da rimuovere
    Edge **tentativi = malloc((G->E)* sizeof(Edge*)); // matrice di archi sovradimensionata (E*E) che conterrà gli insiemi di archi rimovibili
                                                     // un insieme per riga
    for(i=0;i<G->E;i++) tentativi[i] = malloc(G->E * sizeof(Edge));

    GRAPH_edges(G,a); //costruisco il vettore di archi

    for(i=0;i<G->E && !find;i++){
        printf("\ngeneratore set di cardinalita' %d : \n",i);
        find = tentativo_DAG(0,a,removed,tentativi,G->E,i,0,0,G);
    }
    if(!find){
        printf("non e' possibile generare un DAG partendo da questo grafo\n");
        return;
    }
    if(i==1){
        printf("il grafo e' gia' un DAG\n");
        return;
    }
    //trovo la riga della matrice contenente l'insieme rimovibile a peso massimo
    best_del=best_DAG(tentativi,find,i-1,G);

    //stampa dei risultati
    for(j=0;j<i-1;j++){
        id1=tentativi[best_del][j].v;
        id2=tentativi[best_del][j].w;
        peso=tentativi[best_del][j].wt;
        removeE(G, create_edge(id1,id2,peso));
        printf("arco rimosso : %s -> %s di peso [%d]\n",STsearchbyindex(G->tab,id1),STsearchbyindex(G->tab,id2),peso);
    }
    printf("\n\nDAG risultante :\nG \\ {");
    for(j=0;j<i-1;j++){
        id1=tentativi[best_del][j].v;
        id2=tentativi[best_del][j].w;
        printf("(%s , %s),",STsearchbyindex(G->tab,id1),STsearchbyindex(G->tab,id2));
    }
    printf("\b}\n");

    //free dei dati precedentemente allocati
    free(a);
    free(removed);
    for (i=0; i<G->E;i++){
        free(tentativi[i]);
    }
    free(tentativi);
}

int tentativo_DAG(int pos, Edge* val, Edge *sol, Edge **tentativi, int n, int k, int start, int count, Graph G){
    int i,j;
    //se arrivo allla cardinalita' richiesta:
    if(pos>=k){
        printf("G \\ {");
        for(j=0;j<k;j++){
            printf("(%s,%s),",STsearchbyindex(G->tab,sol[j].v),STsearchbyindex(G->tab,sol[j].w));
        }
        if(j!=0) printf("\b}\n");
        else printf("}\n");
        //provo a eliminare l'insieme di vertici contenuto nella soluzione
        for(j=0;j<k;j++){
            GRAPH_remove(G,sol[j].v,sol[j].w);
        }
        //verifico l'aciclicita'
        if(dfs_mod(G)==0){
            printf("aciclico = si'\n");
            //se l'insieme trovato e' rimovibile lo inserisco nella matrice delle soluzioni accettabili all'indice 'count'
            for(j=0;j<k;j++){
                tentativi[count][j]=sol[j];
            }
            count++;
        }
        else printf("aciclico = no\n");
        //riinserisco gli archi nel grafo per poter continuare a verificare le ipotesi successive
        for(j=0;j<k;j++){
            insert_edge(G,create_edge(sol[j].v,sol[j].w,sol[j].wt));
        }
        return count;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i]; //nel vettore sol salvo la soluzione ipotizzata localmente
        count=tentativo_DAG(pos+1,val,sol,tentativi,n,k,i+1,count,G); //ricorro sulla posizione successiva
    }
    return count; //ritorno il numero di soluzioni possibili ho trovato
}

int best_DAG(Edge **tentativi, int find, int cardinal,Graph G){
    int b_id=0, b_sum=0, sum=0, i,j, id1=0,id2=0;
    for(i=0;i<find;i++){
        sum=0;
        printf("\npossibile cancellazione : ");
        for(j=0;j<cardinal;j++){
            sum += tentativi[i][j].wt;
            id1 = tentativi[i][j].v;
            id2 = tentativi[i][j].w;
            printf("(%s -> %s) ", STsearchbyindex(G->tab,id1),STsearchbyindex(G->tab,id2));
        }
        printf("peso [%d]",sum);
        if(sum>b_sum){
            b_sum=sum;
            b_id=i;
        }
    }
    printf("\n\n");
    return b_id; //ritorno l'indice della riga della matrice tentativi in cui
                 // e' presente l'insieme eliminabile di archi a peso massimo
}

void GRAPH_longest_path(Graph G) {
    int *TS,i;
    TS = TS_dag(G); // TS è un vettore di vertici ordinati secondo il topological sorting inverso
    for(i=G->V-1;i>=0;i--){ // per conoscere l'ordine topologico semplice leggo il vettore da destra a sinistra
        printf("\nSORGENTE  %s :\n",STsearchbyindex(G->tab,TS[i]));
        relaxation(TS, G, TS[i]); //applico la relaxation a seguendo l'ordine topologico partendo, TS[i] = vertice di partenza
    }
}
