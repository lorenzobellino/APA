//
// Created by loren on 13/12/2018.
//

#include "equipArray.h"

struct tabEquip_t{
    int inUso;
    int vettEq[8];
};

void inizializza_equip(equipped v_eq){
    int k;
    v_eq->inUso=0;
    for(int k=0;k<8;k++){
        v_eq->vettEq[k]=-1;
    }
}

void print_equip_pg(equipped v_eq, inventary arsenale){
    int i;
    for(i=0;i<v_eq->inUso;i++){
        printf("\t");
        stampa_oggetto(arsenale,v_eq->vettEq[i]);
    }
}

void ordina_vett_eq(equipped v_eq){
    int i,j;
    int tmp;
    for(j=0;j<8;j++){
        for(i=0;i<7;i++){
            if(v_eq->vettEq[i]==-1){
                tmp=v_eq->vettEq[i];
                v_eq->vettEq[i]=v_eq->vettEq[i+1];
                v_eq->vettEq[i+1]=tmp;
            }
        }
    }
}

int max_equip(equipped eq){
    if(eq->inUso==8) return 1;
    else return 0;
}

void libera_equip(equipped eq, int a){
    eq->inUso-=1;
    eq->vettEq[a]=-1;
}

int zero_equip(equipped eq){
    if(eq->inUso==0) return 1;
    else return 0;
}

int find_eq_name(equipped eq,char buff[], inventary arsenale){
    int i;
    for(i=0;i<eq->inUso;i++){
        if(controllo_nome_eq(arsenale, eq->vettEq[i],buff)) return i;
    }
    return 8;
}

void add_n_equip(equipped eq){
    eq->inUso+=1;
}

void equipaggia(equipped eq, int a){
    eq->vettEq[eq->inUso-1]=a;
}

int n_equip(equipped eq){
    return eq->inUso;
}

int get_index_equip(equipped eq, int n){
    return eq->vettEq[n];
}