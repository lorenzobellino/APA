

#ifndef ESERCIZIO3_INVARRAY_H
#define ESERCIZIO3_INVARRAY_H

typedef struct tabinv_t *inventary;

#include "inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initialize_inv(inventary *arsenale);
void termina_inv(inventary arsenale);
void store_arsenale(inventary *arsenale, char filename[]);
void print_inventario(inventary arsenale);
void read_obj_tastiera(inventary *arsenale);
void find_obj(inventary arsenale);
void print_specs(inventary arsenale);
void stampa_oggetto(inventary arsenale, int i);
void get_stats_obj(int a, inventary arsenale,int *hp,int *mp,int *atk,int *def, int *mag,int *spr);
int empty_inv(inventary arsenale);
int find_obj_name(inventary arsenale, char name[]);
int max_inventario(inventary arsenale);
int controllo_nome_eq(inventary arsenale, int n, char buff[]);

#endif //ESERCIZIO3_INVARRAY_H
