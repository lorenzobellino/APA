

#ifndef ESERCIZIO3_PG_H
#define ESERCIZIO3_PG_H

#define maxs 50
#define maxc 15

#include "inv.h"
#include "equipArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct pg_t{
    char codice[maxc];
    char nome[maxs+1];
    char classe[maxs+1];
    equipped equip;
    stats stat;
}pg;

typedef struct nodoPg_t{
    pg personaggio;
    struct nodoPg_t *next;
}nodo_pg;

int controllo_cod(char cod[],nodo_pg *head);
void print_code(nodo_pg *x, int n);
nodo_pg* new_pg(nodo_pg p, nodo_pg *head);
nodo_pg *find_pg_code(nodo_pg *head, char code[]);

#endif //ESERCIZIO3_PG_H
