
#ifndef ESERCIZIO3_ST_H
#define ESERCIZIO3_ST_H


typedef struct symboltable *ST;

ST ST_init(int E);
int ST_search(ST tab, char id[], int n);
void ST_insert(ST tab,char id_elab[],char id_rete[], int id);
void stampatab(ST tab, int n);
void ST_free(ST tab);
char *ST_search_by_index(ST tab, int i);

#endif
