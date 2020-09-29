//
// Created by loren on 13/12/2018.
//

#include "inv.h"

void get_stats(Item item, int *hp,int *mp,int *atk,int *def, int *mag,int *spr){
    (*hp)+=item.stat.hp;
    (*mp)+=item.stat.mp;
    (*atk)+=item.stat.atk;
    (*def)+=item.stat.def;
    (*mag)+=item.stat.mag;
    (*spr)+=item.stat.spr;
}

int max(int a,int b){
    if(a>b) return a;
    else return b;
}