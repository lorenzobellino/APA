

#include "pgList.h"

struct tabPg_t{
    nodo_pg *headPg;
    nodo_pg *tailPg;
    int nPg;
};

void initialize_pg(tabPg *characters){
    *characters = malloc(sizeof(struct tabPg_t));
    (*characters)->nPg=0;
    (*characters)->headPg=NULL;
    (*characters)->tailPg=NULL;
}

void read_characters(tabPg *characters, char filename[]){
        int i,prev_pg;
        nodo_pg persona;
        FILE *f=fopen(filename,"r");
        if(f!=NULL){
            prev_pg=(*characters)->nPg;
            fscanf(f,"%d",&(*characters)->nPg);
            (*characters)->nPg+=prev_pg;
            for(i=prev_pg;i<(*characters)->nPg;i++){
                fscanf(f,"%s %s %s %d %d %d %d %d %d\n",persona.personaggio.codice,persona.personaggio.nome,persona.personaggio.classe,
                       &persona.personaggio.stat.hp,&persona.personaggio.stat.mp,&persona.personaggio.stat.atk,&persona.personaggio.stat.def,
                       &persona.personaggio.stat.mag,&persona.personaggio.stat.spr);
                persona.next=NULL;
                persona.personaggio.equip = malloc(sizeof(equipped));
                inizializza_equip(persona.personaggio.equip);
                while(controllo_cod(persona.personaggio.codice,(*characters)->headPg)){
                    printf("il codice %s esiste gia', codici gia' esistenti:\n",persona.personaggio.codice);
                    print_code((*characters)->headPg,(*characters)->nPg);
                    printf("inserisci un codice inutilizzato\n");
                    scanf("%s", persona.personaggio.codice);
                }
                (*characters)->headPg = new_pg(persona,(*characters)->headPg);
                if((*characters)->tailPg==NULL) (*characters)->tailPg=(*characters)->headPg;
            }
        }
        fclose(f);
}

void read_pg_tastiera(tabPg *characters){
    nodo_pg p;
    (*characters)->nPg+=1;
    printf("codice: \n");
    scanf("%s",p.personaggio.codice);
    while(controllo_cod(p.personaggio.codice,(*characters)->headPg)){
        printf("il codice %s esiste gia', codici gia' esistenti:\n",p.personaggio.codice);
        print_code((*characters)->headPg,(*characters)->nPg);
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
    inizializza_equip(p.personaggio.equip);
    (*characters)->headPg = new_pg(p,(*characters)->headPg);
    if((*characters)->tailPg==NULL) (*characters)->tailPg=(*characters)->headPg;
}

int empty_pg(tabPg characters){
    if(characters->nPg==0) return 1;
    else return 0;
}

void print_characters(tabPg characters, inventary arsenale){
    int i;
    nodo_pg *x=characters->headPg;
    for(i=0;i<characters->nPg && x!=NULL;i++){
        printf("%s %s %s %d %d %d %d %d %d\n",x->personaggio.codice,x->personaggio.nome,x->personaggio.classe,
               x->personaggio.stat.hp,x->personaggio.stat.mp,x->personaggio.stat.atk,x->personaggio.stat.def,
               x->personaggio.stat.mag,x->personaggio.stat.spr);
            print_equip_pg(x->personaggio.equip,arsenale);
        x=x->next;
    }

}

void termina_pg(tabPg characters){
    int i;
    nodo_pg *x;
    for(x=characters->headPg;x!=NULL;x=x->next){
        free(x->personaggio.equip);
        free(x);
    }
    free(characters->headPg);
    free(characters->tailPg);
    free(characters);
}

void delete_pg(tabPg *characters, inventary arsenale){
    char buff[maxs];
    nodo_pg *x=NULL, *p=NULL;
    int i;
    printf("codice del personaggio da eliminare? <list> per conoscere la lista dei personaggi\n");
    do{
        scanf("%s",buff);
        if(strcmp(buff,"list")==0){
            print_characters(*characters, arsenale);
        }
        else {
            for (x = (*characters)->headPg, p = NULL;x != NULL && strcmp(x->personaggio.codice, buff) != 0; p = x, x = x->next);
            if (x == NULL) printf("codice non trovato\ndigita list per conoscere la lista dei personaggi\n");
        }
    }while(x==NULL);

    if(p==NULL){
        //cancella in testa
        p=(*characters)->headPg;
        (*characters)->headPg=p->next;
        free(p->personaggio.equip);
        free(p);
    }

    else{
        if(x->next==NULL){
            //cancella in coda
            x=(*characters)->tailPg;
            (*characters)->tailPg=p;
            free(x->personaggio.equip);
            free(x);
            (*characters)->tailPg->next=NULL;
        }
        else{
            //cancella in mezzo
            p->next=x->next;
            free(x->personaggio.equip);
            free(x);
        }

    }
    (*characters)->nPg = (*characters)->nPg-1;
}

void cerca_pg(tabPg characters){char buff[maxs];
    nodo_pg *x=NULL;
    printf("quale personaggio stai cercando (ricerca per codice) ?\n");
    while(x==NULL){
        scanf("%s",buff);
        for(x=characters->headPg;x!=NULL && strcmp(buff,x->personaggio.codice)!=0;x=x->next);
        if(x==NULL)printf("personaggio non trovato\ninserisci un codice presente in elenco\n");
    }
    printf("nome : %s classe : %s\n",x->personaggio.nome, x->personaggio.classe);
    //print_equip_pg(x);
}

void equip_pg(tabPg *characters, inventary arsenale){
    int a=8,risp=0;
    char buff[maxs+1];
    nodo_pg *x=NULL;
    printf("codice del personaggio da equipaggiare (<list> per conoscere tutti i personaggi): \n");
    scanf("%s",buff);
    while(x==NULL){
        if(strcmp(buff,"list")==0){
            print_characters(*characters,arsenale);
            scanf("%s",buff);
        }
        else{
            x=find_pg_code((*characters)->headPg,buff);
            if(x==NULL) {
                printf("codice non trovato, assicurati che sia nella forma PGXXXX\ndigita list per conoscere tutti i personaggi\n");
                scanf("%s",buff);
            }
        }
    }
    if(max_equip(x->personaggio.equip)){
        printf("il personaggio ha gia' il numero massimo di equipaggiamenti (digita 'l' per conoscerli)\nvuoi eliminarne uno? [s][n]\n");
        while(!risp){
            switch (getchar()){
                case 's':
                    printf("quale equipaggiamento? (list per conoscere gli oggetti gia' equipaggiati)\n");
                    scanf("%s",buff);
                    while(a==8){
                        if(strcmp(buff,"list")==0){
                            print_equip_pg(x->personaggio.equip,arsenale);
                            scanf("%s",buff);
                        }
                        else{
                            a=find_eq_name(x->personaggio.equip, buff,arsenale);
                            if(a==8){
                                printf("equipaggiamento non presente in elenco\n(digita list per conoscere gli oggetti gia' equipaggiati)\n");
                                scanf("%s",buff);
                            }
                        }
                    }
                    libera_equip(x->personaggio.equip,a);
                    ordina_vett_eq(x->personaggio.equip);
                    risp=1;
                    break;
                case 'l':
                    print_equip_pg(x->personaggio.equip,arsenale);
                    printf("vuoi eliminarne uno? (s , n)\n");
                    break;
                case 'n':
                    return;
                default:
                    printf("risposte valide: s oppure n\n");
                    break;
            }
        }
        printf("elemento eliminato correttamente\n\n");
    }
    a=max_inventario(arsenale);
    if(!max_equip(x->personaggio.equip)){
        add_n_equip(x->personaggio.equip);
        printf("nome dell'oggetto da equipaggiare? (digita list per conoscere cosa e' presente nell'inventario)\n");
        scanf("%s",buff);
        while(a>=max_inventario(arsenale)){
            if(strcmp(buff,"list")==0){
                print_inventario(arsenale);
                scanf("%s",buff);
            }
            else{
                a=find_obj_name(arsenale, buff);
                if(a>=max_inventario(arsenale)){
                    printf("equipaggiamento non presente in elenco\n(digita list per conoscere cosa e' presente nell'inventario)\n");
                    scanf("%s",buff);
                }
            }
        }
        equipaggia(x->personaggio.equip, a);
    }
}

void delete_equip_pg(tabPg *characters,inventary arsenale){
    int a=8;
    char buff[maxs+1];
    nodo_pg *x=NULL;
    printf("codice del personaggio (<list> per conoscere tutti i personaggi): \n");
    scanf("%s",buff);
    while(x==NULL){
        if(strcmp(buff,"list")==0) print_characters(*characters, arsenale);
        else x=find_pg_code((*characters)->headPg,buff);

        if(x==NULL) {
            printf("codice non trovato, assicurati che sia nella forma PGXXXX\ndigita list per conoscere tutti i personaggi\n");
            scanf("%s", buff);
        }
    }
    if(zero_equip(x->personaggio.equip)) printf("il personaggio non ha oggetti equipaggiati\n");
    else{
        printf("nome dell'equipaggiamento da eliminare ? ( digita list per conoscere gli oggetti gia' equipaggiati)\n");
        while(a>=8){
            scanf("%s",buff);
            if(strcmp(buff,"list")==0) print_equip_pg(x->personaggio.equip,arsenale);
            else{
                a=find_eq_name(x->personaggio.equip, buff,arsenale);
                if(a>=8){
                    printf("\nequipaggiamento non presente in elenco\n(digita list per conoscere gli oggetti gia' equipaggiati)\n");
                }
            }
        }
        printf("equipaggiamento eliminato con successo\n");
        libera_equip(x->personaggio.equip,a);
        ordina_vett_eq(x->personaggio.equip);
    }
}

void calcola_stats(tabPg characters, inventary arsenale){
    char buff[maxc];
    int hp,mp,atk,def,mag,spr,i;
    nodo_pg *x=NULL;
    printf("inserisci codice? (list per la lista completa)\n");
    do{
        scanf("%s", buff);
        if(strcmp(buff,"list")==0) print_characters(characters,arsenale);
        else {
            x=find_pg_code(characters->headPg,buff);
            if(x==NULL) {
                printf("codice non trovato, assicurati che sia nella forma PGXXXX\ndigita list per conoscere tutti i personaggi\n");
            }
        }
    }while(x==NULL);
    hp=x->personaggio.stat.hp;
    mp=x->personaggio.stat.mp;
    atk=x->personaggio.stat.atk;
    def=x->personaggio.stat.def;
    mag=x->personaggio.stat.mag;
    spr=x->personaggio.stat.spr;
    for(i=0;i<n_equip(x->personaggio.equip);i++){
        get_stats_obj(get_index_equip(x->personaggio.equip, i),arsenale,&hp,&mp,&atk,&def,&mag,&spr);
    }
    printf("|STATISTICHE : %s %s|\n",x->personaggio.nome,x->personaggio.classe);
    printf("HP  : %d\n",max(hp,0));
    printf("MP  : %d\n",max(mp,0));
    printf("ATK : %d\n",max(atk,0));
    printf("DEF : %d\n",max(def,0));
    printf("MAG : %d\n",max(mag,0));
    printf("SPR : %d\n",max(spr,0));
}