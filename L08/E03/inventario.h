
#ifndef ESERCIZIO3_INVENTARIO_H
#define ESERCIZIO3_INVENTARIO_H

#define maxs 50

typedef struct stat_t{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stats;

typedef struct inv_t{
    char nome[maxs+1];
    char tipo[maxs+1];
    stats stat;
}Item;

typedef struct tabinv_t{
    Item *vettInv;
    int maxinv;
}inventary;

inventary *store_arsenale(inventary *arsenale, char filename[]);
inventary *read_obj_tastiera(inventary *arsenale);
void print_inventario(inventary *arsenale);
int find_obj_name(inventary *arsenale,char name[]);
void find_obj(inventary *arsenale);
void print_specs(inventary *arsenale);

#endif
