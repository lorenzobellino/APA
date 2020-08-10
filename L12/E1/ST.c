#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

//definizione della struttura dati:
struct symboltable {char **a; int maxN;};

//funzioni standard

ST STinit(int maxN) {
    int i;
    ST st;
    st = malloc(sizeof(*st));
    if (st == NULL) {
        printf("errore di allocazione\n");
        return NULL;
    }
    st->a = calloc(maxN,sizeof(char *));
    if (st->a == NULL) {
        printf("errore di allocazione\n");
        free(st);
        return NULL;
    }
    st->maxN = maxN;
    for (i=0; i<maxN; i++)
        st->a[i] = NULL;
    return st;
}

void STinsert(ST table, char label[], int i){
    if (i >= table->maxN) {
        printf("indice: %d e' troppo grande\n", i);
        return;
    }
    table->a[i] = strdup(label);
}

//data l'etichetta ritorna (nome del vertice) l'id intero
int STsearch(ST table, char label[]){
    int i;
    for (i = 0; i  < table->maxN; i++){
        if (table->a[i]!=NULL && strcmp(label, table->a[i])==0) return i;
    }
    return -1;
}

//dato l'id intero ritorna l'etichetta (nome del vertice)
char* STsearchbyindex(ST table, int index){
    if(index>table->maxN) return NULL;
    return table->a[index];
}

void ST_free(ST table){
    int i;
    for (i = 0; i  < table->maxN; i++)
        if (table->a[i]!=NULL)
            free(table->a[i]);
    free(table->a);
    free(table);
}
