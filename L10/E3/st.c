
#include "st.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct data{char id_elab[30];char id_rete[30];int id;} *Data;
struct symboltable{Data data; int maxN;};

ST ST_init(int E){
    ST tab;
    tab=malloc(sizeof(*tab));
    tab->maxN=E;
    tab->data = calloc(E,sizeof(Data));
    return tab;
}

int ST_search(ST tab, char id[], int n){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(id, tab->data[i].id_elab)==0) return tab->data[i].id;
    }
    return -1;
}

void ST_insert(ST tab,char id_elab[],char id_rete[], int id){
    strcpy(tab->data[id].id_elab,id_elab);
    strcpy(tab->data[id].id_rete,id_rete);
    tab->data[id].id=id;
    tab->maxN=id;
    //printf("el inserito: %s %s [%d]\n",tab->data[id].id_elab,tab->data[id].id_rete,tab->data[id].id);
}

void stampatab(ST tab, int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d --> %s\n",i, tab->data[i].id_elab);
    }
}

char *ST_search_by_index(ST tab, int i){
    return tab->data[i].id_elab;
}

void ST_free(ST tab){
    free(tab->data);
    free(tab);
}