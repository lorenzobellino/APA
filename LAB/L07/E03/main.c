#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxs 50
#define maxc 8

typedef enum{carica_pg,carica_obj,add_pg,del_pg,add_equip,del_equip,status,print_pg,print_inv,quit}commands;

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

typedef struct tabinv_t{
    Item *vettInv;
    int maxinv;
}inventary;

tabPg_t *read_characters(tabPg_t *characters,char filename[]);
nodo_pg *new_pg(nodo_pg p, nodo_pg *head);
inventary *store_arsenale(inventary *arsenale, char filename[]);
tabPg_t *read_pg_tastiera(tabPg_t *characters);
tabPg_t *equip_pg(tabPg_t *characters, inventary *arsenale);
tabPg_t *delete_equip_pg(tabPg_t *characters);
tabPg_t *delete_pg(tabPg_t *characters);
nodo_pg *find_pg_code(tabPg_t *characters, char code[]);
nodo_pg *ordina_vett_eq(nodo_pg *p);
int print_command();
void print_inventario(inventary *arsenale);
void print_characters(tabPg_t *characters);
int controllo_cod(char cod[],nodo_pg *head);
int find_obj_name(inventary *arsenale,char name[]);
int find_eq_name(nodo_pg* p, char name[]);
void print_code(tabPg_t *characters);
void print_equip_pg(nodo_pg *p);
void initialize(tabPg_t **characters,inventary **arsenale);
void calcola_stats(tabPg_t *characters);
void termina(tabPg_t *characters, inventary *arsenale);


int main(){
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
                calcola_stats(characters);
                break;
            case print_pg:
                print_characters(characters);
                break;
            case print_inv:
                print_inventario(arsenale);
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
    fclose(f);
    return arsenale;
    }
    else return NULL;
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

tabPg_t* read_characters(tabPg_t * characters,char filename[]){
    int i,j,prev_pg;
    nodo_pg persona;
    FILE *f=fopen(filename,"r");
    if(f!=NULL){
        prev_pg=characters->nPg;
        fscanf(f,"%d",&characters->nPg);
        characters->nPg+=prev_pg;
        for(i=prev_pg;i<characters->nPg;i++){
            fscanf(f,"%s %s %s %d %d %d %d %d %d\n",persona.personaggio.codice,persona.personaggio.nome,persona.personaggio.classe,
                    &persona.personaggio.stat.hp,&persona.personaggio.stat.mp,&persona.personaggio.stat.atk,&persona.personaggio.stat.def,
                    &persona.personaggio.stat.mag,&persona.personaggio.stat.spr);
            persona.next=NULL;
            persona.personaggio.equip = malloc(sizeof(equipped));
            (persona.personaggio.equip)->inUso=0;
            for(j=0;j<8;j++){
                (persona.personaggio.equip)->vettEq[j]=calloc(1,sizeof(Item));
                (persona.personaggio.equip)->vettEq[j]=NULL;
            }
            while(controllo_cod(persona.personaggio.codice,characters->headPg)){
                    printf("il codice %s esiste gia', codici gia' esistenti:\n",persona.personaggio.codice);
                    print_code(characters);
                    printf("inserisci un codice inutilizzato\n");
                    scanf("%s", persona.personaggio.codice);
            }
            characters->headPg = new_pg(persona,characters->headPg);
            if(characters->tailPg==NULL) characters->tailPg=characters->headPg;
        }
    }
    fclose(f);
    return characters;
}

nodo_pg* new_pg(nodo_pg p, nodo_pg *head){
    nodo_pg *x=malloc(sizeof *x);
    x->next=NULL;
    x->personaggio=p.personaggio;
    if(head==NULL){
        head=x;
    }
    else{
        x->next=head;
        head=x;
    }
    return head;
}

tabPg_t *read_pg_tastiera(tabPg_t *characters){
    int j;
    nodo_pg p;
    characters->nPg+=1;
    printf("codice: \n");
    scanf("%s",p.personaggio.codice);
    while(controllo_cod(p.personaggio.codice,characters->headPg)){
        printf("il codice %s esiste gia', codici gia' esistenti:\n",p.personaggio.codice);
        print_code(characters);
        printf("inserisci un codice inutilizzato\n");
        scanf("%s", p.personaggio.codice);
    }
    printf("\nnome : \n");
    scanf("%s",p.personaggio.nome);
    printf("classe :\n");
    scanf("%s",p.personaggio.classe);
    printf("stats : (hp , mp , atk , def , mag , srp) :\n");
    scanf("%d %d %d %d %d %d",&p.personaggio.stat.hp,&p.personaggio.stat.mp,&p.personaggio.stat.atk,
            &p.personaggio.stat.def, &p.personaggio.stat.mag, &p.personaggio.stat.spr);
    p.next=NULL;
    p.personaggio.equip = malloc(sizeof(equipped));
    (p.personaggio.equip)->inUso=0;
    for(j=0;j<8;j++){
        (p.personaggio.equip)->vettEq[j]=calloc(1,sizeof(Item));
        (p.personaggio.equip)->vettEq[j]=NULL;
    }
    characters->headPg = new_pg(p,characters->headPg);
    if(characters->tailPg==NULL) characters->tailPg=characters->headPg;
    return characters;
}

tabPg_t *equip_pg(tabPg_t *characters, inventary *arsenale){
    int a=8,risp=0;
    char buff[maxs+1];
    nodo_pg *x=NULL;
    printf("codice del personaggio da equipaggiare (<list> per conoscere tutti i personaggi): \n");
    scanf("%s",buff);
    while(x==NULL){
        if(strcmp(buff,"list")==0){
            print_characters(characters);
            scanf("%s",buff);
        }
        else{
            x=find_pg_code(characters,buff);
            if(x==NULL) {
                printf("codice non trovato, assicurati che sia nella forma PGXXXX\ndigita list per conoscere tutti i personaggi\n");
                scanf("%s",buff);
            }
        }
    }
    if(x->personaggio.equip->inUso==8){
        printf("il personaggio ha gia' il numero massimo di equipaggiamenti (digita 'l' per conoscerli)\nvuoi eliminarne uno? [s][n]\n");
        while(!risp){
            switch (getchar()){
                case 's':
                    printf("quale equipaggiamento? (list per conoscere gli oggetti gia' equipaggiati)\n");
                    scanf("%s",buff);
                    while(a==8){
                        if(strcmp(buff,"list")==0){
                            print_equip_pg(x);
                            scanf("%s",buff);
                        }
                        else{
                            a=find_eq_name(x,buff);
                            if(a==8){
                                printf("equipaggiamento non presente in elenco\n(digita list per conoscere gli oggetti gia' equipaggiati)\n");
                                scanf("%s",buff);
                            }
                        }
                    }
                    (x->personaggio.equip)->vettEq[a] = NULL;
                    (x->personaggio.equip)->inUso -= 1;
                    x = ordina_vett_eq(x);
                    risp=1;
                    break;
                case 'l':
                    print_equip_pg(x);
                    printf("vuoi eliminarne uno? (s , n)\n");
                    break;
                case 'n':
                    return characters;
                default:
                    printf("risposta valida: s oppure n\n");
                    break;
            }
        }
        printf("elemento eliminato correttamente\n\n");
    }

    a=arsenale->maxinv;
    if(x->personaggio.equip->inUso<8){
        x->personaggio.equip->inUso+=1;
        printf("nome dell'oggetto da equipaggiare? (digita list per conoscere cosa e' presente nell'inventario)\n");
        scanf("%s",buff);
        while(a>=arsenale->maxinv){
            if(strcmp(buff,"list")==0){
                print_inventario(arsenale);
                scanf("%s",buff);
            }
            else{
                a=find_obj_name(arsenale, buff);
                if(a>=arsenale->maxinv){
                    printf("equipaggiamento non presente in elenco\n(digita list per conoscere cosa e' presente nell'inventario)\n");
                    scanf("%s",buff);
                }
            }
        }
        x->personaggio.equip->vettEq[x->personaggio.equip->inUso-1]=&(arsenale->vettInv[a]);
    }
    return characters;
}

int print_command(){
    char cod[15], opzioni[10][15]={"carica_pg","carica_obj","add_pg","del_pg","add_equip","del_equip","status","print_pg","print_inv","quit"};
    int i;
    printf("\n\n\t\t\t |MENU|\n");
    printf("       |opzioni|    \t\t   |codici|\n");
    printf("carica personaggi   \t\t carica_pg\n");
    printf("carica oggetti      \t\t carica_obj\n");
    printf("aggiungi personaggio\t\t add_pg\n");
    printf("rimuovi personaggio \t\t del_pg\n");
    printf("aggiungi oggetto    \t\t add_equip\n");
    printf("rimuovi oggetto     \t\t del_equip\n");
    printf("calcola statistiche \t\t status\n");
    printf("stampa personaggio  \t\t print_pg\n");
    printf("stampa inventario   \t\t print_inv\n");
    printf("esci                \t\t quit\n");
    scanf("%s",cod);
    for(i=0;i<10;i++){
        if(strcmp(cod,opzioni[i])==0){
            return i;
        }
    }
    return -1;
}

void print_inventario(inventary *arsenale){
    int i;
    for(i=0; i<arsenale->maxinv;i++){
        printf("%s %s %d %d %d %d %d %d \n",arsenale->vettInv[i].nome,arsenale->vettInv[i].tipo,
                arsenale->vettInv[i].stat.hp,arsenale->vettInv[i].stat.mp,arsenale->vettInv[i].stat.atk,
               arsenale->vettInv[i].stat.def,arsenale->vettInv[i].stat.mag,arsenale->vettInv[i].stat.spr);
    }
}

void print_characters(tabPg_t *characters){
    int i;
    nodo_pg *x=characters->headPg;
    for(i=0;i<characters->nPg && x!=NULL;i++){
        printf("%s %s %s %d %d %d %d %d %d\n",x->personaggio.codice,x->personaggio.nome,x->personaggio.classe,
               x->personaggio.stat.hp,x->personaggio.stat.mp,x->personaggio.stat.atk,x->personaggio.stat.def,
               x->personaggio.stat.mag,x->personaggio.stat.spr);
        print_equip_pg(x);
        x=x->next;
    }
}

void print_equip_pg(nodo_pg *p){
    int i;
    for(i=0;i<p->personaggio.equip->inUso;i++){
        printf("\t%s %s %d %d %d %d %d %d \n",p->personaggio.equip->vettEq[i]->nome,p->personaggio.equip->vettEq[i]->tipo,
                p->personaggio.equip->vettEq[i]->stat.hp,p->personaggio.equip->vettEq[i]->stat.mp,
               p->personaggio.equip->vettEq[i]->stat.atk,p->personaggio.equip->vettEq[i]->stat.def,
               p->personaggio.equip->vettEq[i]->stat.mag,p->personaggio.equip->vettEq[i]->stat.spr);
    }
}

void print_code(tabPg_t *characters){
    int i;
    nodo_pg *x=characters->headPg;
    for(i=0;i<characters->nPg && x!=NULL;i++){
        printf("%s\n",x->personaggio.codice);
        x=x->next;
    }
}

int controllo_cod(char cod[],nodo_pg *head){
    nodo_pg *x;
    for(x=head;x!=NULL && (strcmp(cod,x->personaggio.codice))!=0;x=x->next);
    if(x==NULL) return 0;
    else return 1;
}

int find_obj_name(inventary *arsenale,char name[]){
    int i;
    for(i=0;i<arsenale->maxinv && strcmp(name,arsenale->vettInv[i].nome)!=0; i++);
    return i;
}

int find_eq_name(nodo_pg* p, char name[]){
    int i;
    for(i=0;i<p->personaggio.equip->inUso && strcmp(name,p->personaggio.equip->vettEq[i]->nome)!=0;i++);
    return i;
}

nodo_pg *find_pg_code(tabPg_t *characters, char code[]){
    nodo_pg *p;
    for(p=characters->headPg;p!=NULL && strcmp(code, p->personaggio.codice)!=0; p=p->next);

    return p;
}

tabPg_t *delete_pg(tabPg_t *characters){
    char buff[maxs];
    nodo_pg *x=NULL, *p=NULL;
    int i;
    printf("codice del personaggio da eliminare? <list> per conoscere la lista dei personaggi\n");
    do{
        scanf("%s",buff);
        if(strcmp(buff,"list")==0){
            print_characters(characters);
        }
        else{
            for(x=characters->headPg, p=NULL;x!=NULL && strcmp(x->personaggio.codice,buff)!=0;p=x,x=x->next);
        }
        if(x==NULL){
            printf("codice non trovato\ndigita list per conoscere la lista dei personaggi\n");
        }
    }while(x==NULL);

    if(p==NULL){
        //cancella in testa
        p=characters->headPg;
        characters->headPg=p->next;
        for(i=0;i<8;i++){
            free(p->personaggio.equip->vettEq[i]);
        }
        free(p->personaggio.equip);
        free(p);
    }

    else{
        if(x->next==NULL){
            //cancella in coda
            x=characters->tailPg;
            characters->tailPg=p;
            for(i=0;i<8;i++){
                free(x->personaggio.equip->vettEq[i]);
            }
            free(x->personaggio.equip);
            free(x);
            characters->tailPg->next=NULL;
        }
        else{
            //cancella in mezzo
            p->next=x->next;
            for(i=0;i<8;i++){
                free(x->personaggio.equip->vettEq[i]);
            }
            free(x->personaggio.equip);
            free(x);
        }

    }
    characters->nPg = characters->nPg-1;
    return characters;
}

tabPg_t *delete_equip_pg(tabPg_t *characters){
    int a=8;
    char buff[maxs+1];
    nodo_pg *x=NULL;
    printf("codice del personaggio (<list> per conoscere tutti i personaggi): \n");
    scanf("%s",buff);
    while(x==NULL){
        if(strcmp(buff,"list")==0) print_characters(characters);
        else x=find_pg_code(characters,buff);

        if(x==NULL) {
            printf("codice non trovato, assicurati che sia nella forma PGXXXX\ndigita list per conoscere tutti i personaggi\n");
            scanf("%s", buff);
        }
    }
    if(x->personaggio.equip->inUso==0) printf("il personaggio non ha oggetti equipaggiati\n");
    else{
        printf("nome dell'equipaggiamento da eliminare ? ( digita list per conoscere gli oggetti gia' equipaggiati)\n");
        scanf("%s",buff);
        while(a>=x->personaggio.equip->inUso){
            if(strcmp(buff,"list")==0) print_equip_pg(x);
            else a=find_eq_name(x, buff);
            if(a>=x->personaggio.equip->inUso){
                printf("\nequipaggiamento non presente in elenco\n(digita list per conoscere gli oggetti gia' equipaggiati)\n");
                scanf("%s",buff);
            }
        }
        x->personaggio.equip->inUso-=1;
        x->personaggio.equip->vettEq[a]=NULL;
        x = ordina_vett_eq(x);
    }
    return characters;
}

nodo_pg *ordina_vett_eq(nodo_pg *p){
    int i,j;
    Item* tmp;
    for(j=0;j<8;j++){
        for(i=0;i<7;i++){
            if(p->personaggio.equip->vettEq[i]==NULL){
                tmp=p->personaggio.equip->vettEq[i];
                p->personaggio.equip->vettEq[i]=p->personaggio.equip->vettEq[i+1];
                p->personaggio.equip->vettEq[i+1]=tmp;
            }
        }

    }
    return p;
}

void calcola_stats(tabPg_t *characters){
    char buff[maxc];
    int hp,mp,atk,def,mag,spr,i;
    nodo_pg *x=NULL;
    printf("inserisci codice? (list per la lista completa)\n");
    scanf("%s",buff);
    do{
        if(strcmp(buff,"list")==0) print_characters(characters);
        else x=find_pg_code(characters,buff);
        if(x==NULL) {
            printf("codice non trovato, assicurati che sia nella forma PGXXXX\ndigita list per conoscere tutti i personaggi\n");
            scanf("%s", buff);
        }
    }while(x==NULL);
    hp=x->personaggio.stat.hp;
    mp=x->personaggio.stat.mp;
    atk=x->personaggio.stat.atk;
    def=x->personaggio.stat.def;
    mag=x->personaggio.stat.mag;
    spr=x->personaggio.stat.spr;
    for(i=0;i<x->personaggio.equip->inUso;i++){
        hp+=x->personaggio.equip->vettEq[i]->stat.hp;
        mp+=x->personaggio.equip->vettEq[i]->stat.mp;
        atk+=x->personaggio.equip->vettEq[i]->stat.atk;
        def+=x->personaggio.equip->vettEq[i]->stat.def;
        mag+=x->personaggio.equip->vettEq[i]->stat.mag;
        spr+=x->personaggio.equip->vettEq[i]->stat.spr;
    }
    printf("|STATISTICHE : %s %s|\n",x->personaggio.nome,x->personaggio.classe);
    printf("HP  : %d\n",hp);
    printf("MP  : %d\n",mp);
    printf("ATK : %d\n",atk);
    printf("DEF : %d\n",def);
    printf("MAG : %d\n",mag);
    printf("SPR : %d\n",spr);

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