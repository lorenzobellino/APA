#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct persona{
    char codice[6];
    char nome[51];
    char cognome[51];
    int data[3];
    char via[51];
    char citta[51];
    int cap;
    struct persona *next;
}persona;

persona* read_data(persona *head, char filename[]);
persona* newNode(persona val, persona* next);
persona* Inserimento_lista(persona* h, persona val);
persona * menu(int s, persona *head);
persona* cancella(persona *h, persona* p);
persona* cerca_codice(persona *h, char cod[], int *find);
persona * cerca_data(persona* h, int d[], int *find);
void stampa_all(persona *h);
void stampa_utente(persona *x,persona*h);
int key_greater_data(int k[], int val[]);
int Key_eq_cod(char chiave[], char codice[]);
int controllo_codice(persona *h, char codice[]);




int main(int argc, char **argv){
    persona *head =NULL;
    int scelta, fine=1;

    do{
        printf("\n\n\t\t\tmenu\n");
        printf("1  inserisci elementi da file\n");
        printf("2  inserimento da tastiera\n");
        printf("3  ricerca elemento per codice\n");
        printf("4  cancella elemento per codice\n");
        printf("5  cancella elementi tra 2 date\n");
        printf("6  stampa a video\n");
        printf("7  esci\n");
        scanf("%d",&scelta);
        if(scelta==7) break;
        system("cls");
        head= menu(scelta,head);
    }while(fine!=0);

    return 0;
}

persona* read_data(persona *head ,char filename[]){
    FILE *f=fopen(filename,"r");
    persona u;
    while(fscanf(f,"%s %s %s %d/%d/%d %s %s %d\n",u.codice, u.nome,u.cognome,&u.data[0],&u.data[1],&u.data[2],u.via,u.citta,&u.cap)!=EOF){
        
        u.next=NULL;
        
        if(!controllo_codice(head,u.codice)){
            head = Inserimento_lista(head,u);
        }
        
    }
    return head;
}

persona* Inserimento_lista(persona* h, persona val) {   
    persona *x, *p;   
    int k[3];
    if(h==NULL) return newNode(val, h);
    k[0]= val.data[0];
    k[1]=val.data[1];
    k[2]=val.data[2];
    if(key_greater_data(h->data, k)) return newNode(val, h);
    for (x=h->next, p=h;x!=NULL && (key_greater_data(k,x->data)) ;p=x,x=x->next);  
    p->next = newNode(val, x);   
    return h; 
} 

persona* newNode(persona val, persona* next) {   
    persona  *x = malloc(sizeof *x);   
    if (x==NULL)      return NULL;   
    else {     
        x->cap = val.cap;
        strcpy(x->citta,val.citta);
        strcpy(x->nome,val.nome);
        strcpy(x->codice,val.codice);
        strcpy(x->cognome,val.cognome);
        x->data[0]=val.data[0];
        x->data[1]=val.data[1];
        x->data[2]=val.data[2];
        strcpy(x->via,val.via);     
        x->next = next;   
        }   
    return x; 
}

persona* menu(int s, persona *head){
    char filename[50], codice[6], buff[6];
    int d1[3],d2[3],find=1;
    persona utente,*p;
    
    switch(s){
        case 1:
            printf("nome file\n");
            scanf("%s",filename);
            head = read_data(head,filename);
        break;

        case 2:
            do{
                printf("\ncodice :");
                scanf("%s", buff);  
            }while(controllo_codice(head,buff));
            strcpy(utente.codice,buff);
            printf("\nnome :");
            scanf("%s",utente.nome);
            printf("\ncognome :");
            scanf("%s", utente.cognome);
            printf("\ndata :");
            scanf("%d/%d/%d",&utente.data[0],&utente.data[1],&utente.data[2]);
            printf("\nvia :");
            scanf("%s", utente.via);
            printf("\ncitta :");
            scanf("%s",utente.citta);
            printf("\ncap :");
            scanf("%d", &utente.cap);
            utente.next=NULL;
            head = Inserimento_lista(head,utente);
        break;

        case 3:
            printf("\ncodice da cercare :");
            scanf("%s",codice);
            p = cerca_codice(head,codice,&find);
            if(find==0){
                printf("\ncodice non trovato\n");
                break; 
            } 
            stampa_utente(p,head);
        break;

        case 4:
            printf("\ncodice da cancellare :");
            scanf("%s", codice);
            p=cerca_codice(head,codice, &find);
            if(find==0) {
                printf("\ncodice non trovato\n");
                break;
            }
            stampa_utente(p,head);
            head = cancella(head, p);
        break;

        case 5:
            printf("data di inizio :");
            scanf("%d/%d/%d",&d1[0],&d1[1],&d1[2]);
            printf("data di fine :");
            scanf("%d/%d/%d",&d2[0],&d2[1],&d2[2]);
            p= cerca_data(head,d2,&find);
            if (find==0) break;
            if(p==NULL){
                while(head!=NULL && key_greater_data(d1,head->data)){
                    stampa_utente(p,head);
                    head = cancella(head,p);
                }
            }
            else{
                while(p->next!=NULL && key_greater_data(d1,p->next->data)){
                stampa_utente(p,head);
                head = cancella(head,p);
                }
            }
            
            
        break;

        case 6:
            stampa_all(head);
        break;

        default:
            printf("comando non trovato\n");
        break;

    }
    return head;
}

void stampa_all(persona *head){
    if(head==NULL) return;
    persona *x=head;
    stampa_utente(NULL,head);
    while(x->next!=NULL){
        stampa_utente(x,head);
        x=x->next;
    }
}

void stampa_utente(persona *x, persona*h){
    if(h==NULL) return;
    if(x==NULL) printf("%s %s %s %d/%d/%d %s %s %d\n",h->codice, h->nome,h->cognome,h->data[0],h->data[1],h->data[2],h->via,h->citta,h->cap);
    else printf("%s %s %s %d/%d/%d %s %s %d\n",x->next->codice, x->next->nome,x->next->cognome,x->next->data[0],x->next->data[1],x->next->data[2],x->via,x->next->citta,x->next->cap);
}

int key_greater_data(int k[], int val[]){
    if(val[2]<k[2]) return 0;
    if(val[2]==k[2] && val[1]<k[1]) return 0;
    if(val[2]==k[2] && val[1]==k[1] && val[0]<k[0]) return 0;
    else return 1;
}

int Key_eq_cod(char chiave[], char codice[]){
    if(strncmp(chiave,codice,5)==0) return 1;
    else return 0;
}

persona* cancella(persona *h, persona* p){
    persona *x;
    if(h==NULL) return NULL;
    if(p==NULL){
        p=h;
        h=h->next;
        free(p);
        return h;
    }
    x=p->next;
    p->next=x->next;
    free(x);
    return h;
}

persona* cerca_codice(persona *h, char cod[], int *find){
    persona *x,*p;
    if(h==NULL) return NULL;
    for (x=h,p=NULL; x!=NULL && !(Key_eq_cod(cod,x->codice)) ;p=x,x=x->next);
    if(x==NULL && Key_eq_cod(cod,p->codice)==0) *find=0;
    return p;
}

persona * cerca_data(persona *h, int d[],int *find){
    persona *x,*p;
    if(h==NULL) return NULL;
    for (x=h,p=NULL; x!=NULL && !(key_greater_data(x->data,d)) ;p=x,x=x->next);
    if(x==NULL && key_greater_data(x->data,d)==0) *find=0;
    return p;
}
int controllo_codice(persona *h, char codice[]){
    persona *x,*p;
    if(h==NULL) return 0;
    for (x=h; x!=NULL && ((strcmp(codice,x->codice)!=0 )); x=x->next);
    if(x==NULL) return 0;
    else{
        printf("| %s | codice gia' presente\n",codice);
        return 1;
    }
}