

#ifndef ESERCIZIO3_GRAPH_H
#define ESERCIZIO3_GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "st.h"

typedef struct graph *GRAPH;
typedef struct edge{ int v; int w; int flusso;}Edge;

GRAPH GRAPH_load(char *filename);
GRAPH GRAPH_init();
int **M_ADJ_init(int n);
void SCELTE(int scelta, int *flg, GRAPH G);
void GRAPH_insertE(GRAPH G, Edge e);
Edge EDGE_create(int id1, int id2, int flux);
void search_MADJ(char v_c[][30],GRAPH G);
void search_LADJ(char v_c[][30],GRAPH G);
void print_madj(GRAPH g);
void print_LADJ(GRAPH g);
void GRAPH_free(GRAPH g);
void extract_VERTEX(char **M,GRAPH G);

#endif
