#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"


inventary *store_arsenale(inventary *arsenale, char filename[]){
    int i,prev_max=0;
    FILE *f = fopen(filename, "r");
    if(f!=NULL){
        if(arsenale->maxinv!=0){
            prev_max=arsenale->maxinv;
            fscanf(f,"%d",&arsenale->maxinv);
            arsenale->maxinv+=prev_max;
            arsenale->vettInv = realloc(arsenale->vettInv,arsenale->maxinv*sizeof(Item));
        }
        else{
            fscanf(f,"%d",&arsenale->maxinv);
            arsenale->vettInv = malloc(arsenale->maxinv*sizeof(Item));
        }
        for(i=prev_max;i<arsenale->maxinv;i++){
            fscanf(f,"%s",arsenale->vettInv[i].nome);
            fscanf(f,"%s",arsenale->vettInv[i].tipo);
            fscanf(f,"%d %d %d %d %d %d",&arsenale->vettInv[i].stat.hp,&arsenale->vettInv[i].stat.mp,&arsenale->vettInv[i].stat.atk,
                   &arsenale->vettInv[i].stat.def,&arsenale->vettInv[i].stat.mag,&arsenale->vettInv[i].stat.spr);
        }
    }
    fclose(f);
    return arsenale;
}

void print_inventario(inventary *arsenale){
    int i;
    for(i=0; i<arsenale->maxinv;i++){
        printf("%s %s %d %d %d %d %d %d \n",arsenale->vettInv[i].nome,arsenale->vettInv[i].tipo,
               arsenale->vettInv[i].stat.hp,arsenale->vettInv[i].stat.mp,arsenale->vettInv[i].stat.atk,
               arsenale->vettInv[i].stat.def,arsenale->vettInv[i].stat.mag,arsenale->vettInv[i].stat.spr);
    }
}

int find_obj_name(inventary *arsenale,char name[]){
    int i;
    for(i=0;i<arsenale->maxinv && strcmp(name,arsenale->vettInv[i].nome)!=0; i++);
    return i;
}

void find_obj(inventary *arsenale){
    char buff[maxs];
    int x;
    printf("quale oggetto stai cercando?\n");
    scanf("%s",buff);
    x=find_obj_name(arsenale,buff);
    if(x>=arsenale->maxinv) printf("l'oggetto non e' presente nell'inventario\ncerca un oggetto presente\n");
    else printf("l'oggetto %s e' presente nell'inventario\n",arsenale->vettInv[x].nome);
}

void print_specs(inventary *arsenale){
    char buff[maxs];
    int x=arsenale->maxinv;
    printf("quale oggetto stai cercando?\n");
    while(x>=arsenale->maxinv){
        scanf("%s",buff);
        x=find_obj_name(arsenale,buff);
        if(x>=arsenale->maxinv) printf("l'oggetto non e' presente nell'inventario\ncerca un oggetto presente\n");
    }
    printf("nome : %s \t tipo : %s\n",arsenale->vettInv[x].nome,arsenale->vettInv[x].tipo);
    printf("statistiche : \n");
    printf("hp : %d\nmp : %d\natk : %d\ndef : %d\nmag : %d\nspr : %d\n",arsenale->vettInv[x].stat.hp,arsenale->vettInv[x].stat.mp,
            arsenale->vettInv[x].stat.atk,arsenale->vettInv[x].stat.def,arsenale->vettInv[x].stat.mag,arsenale->vettInv[x].stat.spr);
}

inventary *read_obj_tastiera(inventary *arsenale){
    arsenale->maxinv+=1;
    if(arsenale->maxinv==1){
        arsenale->vettInv=malloc(arsenale->maxinv*sizeof(Item));
    }
    else{
        arsenale->vettInv=realloc(arsenale->vettInv,arsenale->maxinv*sizeof(Item));
    }
    printf("nome oggetto : \n");
    scanf("%s",arsenale->vettInv[arsenale->maxinv-1].nome);
    printf("tipologia oggetto : \n");
    scanf("%s",arsenale->vettInv[arsenale->maxinv-1].tipo);
    printf("statistiche : hp mp atk def mag spr\n");
    scanf("%d %d %d %d %d %d",&(arsenale->vettInv[arsenale->maxinv-1].stat.hp),&(arsenale->vettInv[arsenale->maxinv-1].stat.mp),
            &(arsenale->vettInv[arsenale->maxinv-1].stat.atk),&(arsenale->vettInv[arsenale->maxinv-1].stat.def),
            &(arsenale->vettInv[arsenale->maxinv-1].stat.mag),&(arsenale->vettInv[arsenale->maxinv-1].stat.spr));
    return arsenale;
}