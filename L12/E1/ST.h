
#ifndef ESERCIZIO12_ST_H
#define ESERCIZIO12_ST_H

//STRUTTURE DATI:
//1) tabella di simboli costruito come ADT di I classe
typedef struct symboltable *ST;

//FUNZIONI STANDARD PER UNA TABELLA DI SIMBOLI:

ST STinit(int v);
void STinsert(ST table, char label[], int i);
int STsearch(ST table, char label[]);
char* STsearchbyindex(ST table, int index);
void ST_free(ST table);

#endif
