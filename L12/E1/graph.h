
#ifndef ESERCIZIO12_GRAPH_H
#define ESERCIZIO12_GRAPH_H

#include "ST.h"

//STRUTTURE DATI:
// 1) ADT di I classe GRAFO
typedef struct graph *Graph;

// 2) quasi ADT per la struct EDGE
typedef struct edges{int v; int w; int wt;} Edge;

//FUNZIONI STANDARD PER L' ADT GRAFO

Graph GRAPH_init(int v);
Graph GRAPH_load(char *filename);
void GRAPH_free(Graph G);
void GRAPH_dfs(Graph G);
void GRAPH_dfsR(Graph G, Edge e, int *time, int *pre, int *post,int *st);
void GRAPH_edges(Graph G, Edge *a);
void GRAPH_remove(Graph G, int id1, int id2);

// FUNZIONI MODIFICATE PER L'ESERCIZIO

int dfs_mod(Graph G);
void dfs_R_mod(Graph G,Edge e, int *time, int *pre, int *post,int *st,int *bcount);

//FUNZIONI IMPLEMENTATE ESPLICITAMENTE PER QUESTO ESERCIZIO

void graph_to_DAG(Graph G);
int tentativo_DAG(int pos, Edge* val, Edge *sol, Edge **tentativi, int n, int k, int start, int count, Graph G);
int best_DAG(Edge **tentativi, int find, int cardinal,Graph G);
void GRAPH_longest_path(Graph G);

#endif
