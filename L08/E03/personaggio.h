
#ifndef ESERCIZIO3_PERSONAGGIO_H
#define ESERCIZIO3_PERSONAGGIO_H

#define maxs 50
#define maxc 8

typedef struct tabEquip_t{
    int inUso;
    Item *vettEq[maxc];
}equipped;

typedef struct pg_t{
    char codice[maxc];
    char nome[maxs+1];
    char classe[maxs+1];
    equipped *equip;
    stats stat;
}pg;

typedef struct nodoPg_t{
    pg personaggio;
    struct nodoPg_t *next;
}nodo_pg;

typedef struct tabPg_t{
    nodo_pg *headPg;
    nodo_pg *tailPg;
    int nPg;
}tabPg_t;

tabPg_t *read_characters(tabPg_t *characters,char filename[]);
nodo_pg *new_pg(nodo_pg p, nodo_pg *head);
tabPg_t *read_pg_tastiera(tabPg_t *characters);
tabPg_t *equip_pg(tabPg_t *characters, inventary *arsenale);
tabPg_t *delete_equip_pg(tabPg_t *characters);
tabPg_t *delete_pg(tabPg_t *characters);
nodo_pg *find_pg_code(tabPg_t *characters, char code[]);
nodo_pg *ordina_vett_eq(nodo_pg *p);
void cerca_pg(tabPg_t *characters);
void print_characters(tabPg_t *characters);
int controllo_cod(char cod[],nodo_pg *head);
int max(int a, int b);
void print_code(tabPg_t *characters);
void print_equip_pg(nodo_pg *p);
void calcola_stats(tabPg_t *characters);

#endif //ESERCIZIO3_PERSONAGGIO_H
