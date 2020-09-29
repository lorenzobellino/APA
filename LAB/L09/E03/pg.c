

#include "pg.h"


int controllo_cod(char cod[],nodo_pg *head){
    nodo_pg *x;
    for(x=head;x!=NULL && (strcmp(cod,x->personaggio.codice))!=0;x=x->next);
    if(x==NULL) return 0;
    else return 1;
}

void print_code(nodo_pg *x, int n){
    int i;
    for(i=0;i<n && x!=NULL;i++){
        printf("%s\n",x->personaggio.codice);
        x=x->next;
    }
}

nodo_pg* new_pg(nodo_pg p, nodo_pg *head){

    nodo_pg *x = (nodo_pg*) malloc(sizeof(*x));

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

nodo_pg *find_pg_code(nodo_pg *head, char code[]){
    nodo_pg *p;
    for(p=head;p!=NULL && strcmp(code, p->personaggio.codice)!=0; p=p->next);
    return p;
}