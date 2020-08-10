

#ifndef ESERCIZIO3_PGLIST_H
#define ESERCIZIO3_PGLIST_H

#include "pg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tabPg_t *tabPg;

void initialize_pg(tabPg *characters);
void read_characters(tabPg *characters, char filename[]);
void read_pg_tastiera(tabPg *characters);
void print_characters(tabPg characters, inventary arsenale);
void termina_pg(tabPg characters);
void delete_pg(tabPg *characters, inventary arsenale);
void equip_pg(tabPg *characters, inventary arsenale);
void cerca_pg(tabPg characters);
void delete_equip_pg(tabPg *characters,inventary arsenale);
void calcola_stats(tabPg characters, inventary arsenale);
int empty_pg(tabPg characters);

#endif //ESERCIZIO3_PGLIST_H
