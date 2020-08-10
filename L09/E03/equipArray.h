

#ifndef ESERCIZIO3_EQUIPARRAY_H
#define ESERCIZIO3_EQUIPARRAY_H

#include "invArray.h"

typedef  struct tabEquip_t *equipped;

void inizializza_equip(equipped v_eq);
void print_equip_pg(equipped v_eq, inventary arsenale);
void ordina_vett_eq(equipped v_eq);
void libera_equip(equipped eq, int a);
void add_n_equip(equipped eq);
void equipaggia(equipped eq, int a);
int max_equip(equipped eq);
int zero_equip(equipped eq);
int find_eq_name(equipped eq,char buff[], inventary arsenale);
int n_equip(equipped eq);
int get_index_equip(equipped eq, int n);


#endif //ESERCIZIO3_EQUIPARRAY_H
