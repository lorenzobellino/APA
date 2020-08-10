

#include "graph.h"
#include "st.h"

typedef struct node *link;
struct node{int v; int wt; link next;};
struct graph{int V; int E; link *l_adj; ST table; link z; int **m_adj;};

static int n_E;
static int n_V;

static void get_nE(FILE *f);

static link New(int v, int wt, link next);
static link *L_ADJ_init(int n,GRAPH G);
static void L_ADJ_load(int **M, GRAPH G);
static void insert_edge(GRAPH G, Edge edge);

GRAPH GRAPH_load(char *filename){
    char id_elab1[30],id_elab2[30],id_rete1[30],id_rete2[30];
    int i,j,flusso,id1,id2;
    GRAPH G;
    FILE *f = fopen(filename,"r");
    if(f==NULL) return NULL;
    get_nE(f);
    G = GRAPH_init();
    if(G==NULL) return NULL;
       for(i=0;i<n_E;i++){
           fscanf(f,"%s %s %s %s %d\n",id_elab1,id_rete1,id_elab2,id_rete2,&flusso);
           printf("%s %s -> %s %s [%d]\n",id_elab1,id_rete1,id_elab2,id_rete2,flusso);
           if(ST_search(G->table,id_elab1,n_V)==-1){
               ST_insert(G->table,id_elab1,id_rete1,n_V);
               n_V+=1;
           }
           if(ST_search(G->table,id_elab2,n_V)==-1){
               ST_insert(G->table,id_elab2,id_rete2,n_V);
               n_V+=1;
           }
       }
       printf("\n");
       stampatab(G->table,n_V);
       G->V=n_V;
       rewind(f);
       G->m_adj=M_ADJ_init(n_V);
       for(i=0;i<n_E;i++){
            fscanf(f,"%s %s %s %s %d",id_elab1,id_rete1,id_elab2,id_rete2,&flusso);
            id1 = ST_search(G->table,id_elab1,G->V);
            id2 = ST_search(G->table,id_elab2,G->V);
            if(id1>=0 && id2 >=0){
                GRAPH_insertE(G,EDGE_create(id1,id2,flusso));
            }
       }
       printf("\n");
       print_madj(G);


    return G;
}

GRAPH GRAPH_init(){
    GRAPH g;
    g = malloc(sizeof(GRAPH));
    if(g==NULL) return NULL;
    g->E=n_E;
    g->V=n_E;
    g->table = ST_init(n_E);
    g->z=calloc(1,sizeof(link));
    g->z->v=-1;
    g->z->wt=0;
    g->z->next=NULL;
    return g;
}

static void get_nE(FILE *f){
    while(fscanf(f,"%*s %*s %*s %*s %*d")==0) n_E+=1;
    rewind(f);
}

int **M_ADJ_init(int n){
    int i=0,j;
    int **M;
    M = calloc(n,sizeof(int*));
    for(i=0;i<n;i++){
        M[i] = calloc(n,sizeof(int));
    }
    return M;
}

void GRAPH_insertE(GRAPH G, Edge e){
    G->m_adj[e.v][e.w]=e.flusso;
    G->m_adj[e.w][e.v]=e.flusso;
}

Edge EDGE_create(int id1, int id2, int flux){
    Edge e;
    e.v=id1;
    e.w=id2;
    e.flusso=flux;
    return e;
}

static link *L_ADJ_init(int n, GRAPH G){
    int i;
    link *ladj;
    ladj = malloc(n*sizeof(link));
    for(i=0;i<n;i++){
        ladj[i]=G->z;
    }
    return ladj;
}

static void L_ADJ_load(int **M, GRAPH G){
    int i,j;
    for(i=0;i<G->V;i++){
        for(j=i;j<G->V;j++){
            if(M[i][j]!=0){
                insert_edge(G, EDGE_create(i,j,M[i][j]));
                insert_edge(G,EDGE_create(j,i,M[j][i]));
            }
        }
    }
}

static void insert_edge(GRAPH G, Edge edge){
    int v = edge.v, w = edge.w, wt = edge.flusso;
    G->l_adj[v] = New(w,wt,G->l_adj[v]);
}

static link New(int v, int wt, link next) {
    link x;
    x = malloc(1*sizeof(*x));
    if (x == NULL) return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

void SCELTE(int scelta, int *flg,GRAPH G){
    int i;
    char **M_V;
    char vertex_choice[3][30];
    switch(scelta-1){
        case 0:
            M_V=calloc(G->V,sizeof(char*));
            for(i=0;i<G->V;i++){
                M_V[i]=calloc(30,sizeof(char));
            }
            extract_VERTEX(M_V,G);
            break;
        case 1:
            for(i=0;i<3;i++){
                printf("vertice [%d]\n",i);
                scanf("%s",vertex_choice[i]);
            }
            search_MADJ(vertex_choice,G);
            break;
        case 2:
            for(i=0;i<3;i++){
                printf("vertice [%d]\n",i);
                scanf("%s",vertex_choice[i]);
            }
            search_LADJ(vertex_choice,G);
            break;
        case 3:
            if(*flg==1){
                printf("lista delle adiacenze gia' generata\n");
                break;
            }
            *flg=1;
            G->l_adj=L_ADJ_init(G->V,G);
            L_ADJ_load(G->m_adj,G);
            print_LADJ(G);
            break;
        case 4:
            printf("esci\n");
            break;
        default:
            printf("comando non trovato\n");
            break;
    }
}

void extract_VERTEX(char **M,GRAPH G){
    int i,j;
    char tmp[30];
    for(i=0;i<G->V;i++){
        strcpy(M[i],ST_search_by_index(G->table,i));
    }
    for(i=0;i<G->V-1;i++){
        for(j=i+1;j<G->V;j++){
            if(strcmp(M[i],M[j])>0){
                strcpy(tmp,M[i]);
                strcpy(M[i],M[j]);
                strcpy(M[j],tmp);
            }
        }
    }
    for(i=0;i<G->V;i++){
        printf("%s\n",M[i]);
    }
}

void print_madj(GRAPH g){
    int i,j;
    for(i=0;i<g->V;i++){
        for(j=0;j<g->V;j++){
            printf("%d ",g->m_adj[i][j]);
        }
        printf("\n");
    }
}

void print_LADJ(GRAPH g){
    link t;
    int i;
    for(i=0;i<g->V;i++){
        printf("\n%d",i);
        for(t=g->l_adj[i];t!=g->z;t=t->next){
            printf(" -> %d",t->v);
        }
    }
}

void search_MADJ(char v_c[][30],GRAPH G){
    int i,id[3],find=0;
    for(i=0;i<3;i++){
        id[i]=ST_search(G->table,v_c[i],G->V);
    }
    for(i=0;i<3;i++){
        if(id[i]<0){
            printf("il vertice %s non e' in lista\n\n",v_c[i]);
            return;
        }
    }
    if(G->m_adj[id[0]][id[1]]!=0) find++;
    if(G->m_adj[id[0]][id[2]]!=0) find++;
    if(G->m_adj[id[1]][id[2]]!=0) find++;
    if(find>=2) printf("i vertici %s -> %s -> %s sono adiacenti\n\n",v_c[0],v_c[1],v_c[3]);
    else printf("i vertici %s <-> %s <-> %s non sono adiacenti\n\n",v_c[0],v_c[1],v_c[3]);
}

void search_LADJ(char v_c[][30],GRAPH G){
    int i,j,id[3],find=0;
    link t;
    for(i=0;i<3;i++){
        id[i]=ST_search(G->table,v_c[i],G->V);
    }
    for(i=0;i<3;i++){
        if(id[i]<0){
            printf("il vertice %s non e' in lista\n\n",v_c[i]);
            return;
        }
    }
    for(i=0;i<3;i++){
        for(t=G->l_adj[id[i]];t!=G->z;t=t->next){
            for(j=0;j<3;j++){
                if(j!=i) if(t->v==id[j]) find+=1;
            }
        }
    }
    if(find>=3) printf("i vertici %s -> %s -> %s sono adiacenti\n\n",v_c[0],v_c[1],v_c[3]);
    else printf("i vertici %s <-> %s <-> %s non sono adiacenti\n\n",v_c[0],v_c[1],v_c[3]);
}

void GRAPH_free(GRAPH g){
    for(int i=0;i<g->V;i++){
        free(g->m_adj[i]);
    }
    free(g->m_adj);
    ST_free(g->table);
}