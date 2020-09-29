#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "personaggio.h"

typedef enum{carica_pg,carica_obj,add_pg,add_obj,del_pg,add_equip,del_equip,status,print_pg,print_inv,view_pg,cerca_obj,specs_obj,quit}commands;

int print_command();
void termina(tabPg_t *characters, inventary *arsenale);
void initialize(tabPg_t **characters,inventary **arsenale);

int main() {
    int finish=0;
    char filename[25];
    tabPg_t * characters;
    inventary *arsenale;
    initialize(&characters,&arsenale);

    while(!finish){
        switch(print_command()){
            case carica_pg:
                printf("filename\n");
                scanf("%s",filename);
                characters= read_characters(characters,filename);
                break;
            case carica_obj:
                printf("filename\n");
                scanf("%s",filename);
                arsenale = store_arsenale(arsenale,filename);
                break;
            case add_pg:
                characters=read_pg_tastiera(characters);
                break;
            case add_obj:
                arsenale=read_obj_tastiera(arsenale);
                break;
            case del_pg:
                if(characters->nPg==0 || arsenale->maxinv==0) printf("non ci sono personaggi caricati o oggetti nell'arsenale\n");
                else characters = delete_pg(characters);
                break;
            case add_equip:
                if(characters->nPg==0 || arsenale->maxinv==0) printf("non ci sono personaggi caricati o oggetti nell'arsenale\n");
                else characters=equip_pg(characters, arsenale);
                break;
            case del_equip:
                if(characters->nPg==0 || arsenale->maxinv==0) printf("non ci sono personaggi caricati o oggetti nell'arsenale\n");
                else characters = delete_equip_pg(characters);
                break;
            case status:
                if(characters->nPg==0) printf("non ci sono personaggi caricati in elenco\n");
                else calcola_stats(characters);
                break;
            case print_pg:
                print_characters(characters);
                break;
            case print_inv:
                print_inventario(arsenale);
                break;
            case view_pg:
                if(characters->nPg==0 || arsenale->maxinv==0) printf("non ci sono personaggi caricati o oggetti nell'arsenale\n");
                else cerca_pg(characters);
                break;
            case cerca_obj:
                if(arsenale->maxinv==0) printf("non ci sono oggetti nell'arsenale\n");
                else find_obj(arsenale);
                break;
            case specs_obj:
                if(arsenale->maxinv==0) printf("non ci sono personaggi caricati o oggetti nell'arsenale\n");
                else print_specs(arsenale);
                break;
            case quit:
                finish=1;
                break;
            default:
                printf("comando non trolvato\n");
                break;
        }
    };
    termina(characters,arsenale);
    return 0;
}

void initialize(tabPg_t **characters, inventary **arsenale){
    *characters=malloc(sizeof(tabPg_t));
    (*characters)->nPg=0;
    (*characters)->headPg=NULL;
    (*characters)->tailPg=NULL;
    *arsenale = malloc(sizeof(inventary));
    (*arsenale)->maxinv=0;
    (*arsenale)->vettInv=NULL;
}

int print_command(){
    char cod[15], opzioni[14][15]={"carica_pg","carica_obj","add_pg","add_obj","del_pg","add_equip","del_equip","status","print_pg",
                                   "print_inv","view_pg","cerca_obj","specs_obj","quit"};
    int i;
    printf("\n\n\t\t\t |MENU|\n");
    printf("       |opzioni|        \t\t   |codici|\n");
    printf("carica personaggi       \t\t carica_pg\n");
    printf("carica oggetti          \t\t carica_obj\n");
    printf("aggiungi personaggio    \t\t add_pg\n");
    printf("aggiungi oggetto        \t\t add_obj\n");
    printf("rimuovi personaggio     \t\t del_pg\n");
    printf("aggiungi oggetto        \t\t add_equip\n");
    printf("rimuovi oggetto         \t\t del_equip\n");
    printf("calcola statistiche     \t\t status\n");
    printf("lista personaggi        \t\t print_pg\n");
    printf("stampa inventario       \t\t print_inv\n");
    printf("stampa personaggio      \t\t view_pg\n");
    printf("ricerca oggetto         \t\t cerca_obj\n");
    printf("specifiche oggetto      \t\t specs_obj\n");
    printf("esci                    \t\t quit\n");
    scanf("%s",cod);
    printf("\n");
    for(i=0;i<14;i++){
        if(strcmp(cod,opzioni[i])==0){
            return i;
        }
    }
    return -1;
}

void termina(tabPg_t *characters, inventary *arsenale){
    int i;
    nodo_pg *x;
    for(x=characters->headPg;x!=NULL;x=x->next){
        for(i=0;i<8;i++){
            free(x->personaggio.equip->vettEq[i]);
        }
        free(x->personaggio.equip);
        free(x);
    }
    free(characters->headPg);
    free(characters->tailPg);
    free(characters);
    free(arsenale->vettInv);
    free(arsenale);
}

