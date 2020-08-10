#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define FILENAME "log.txt"
#define max_l 10000
#define max_s 30

typedef struct{
    char codice_tratte[15];
    char partenza[max_s];
    char destinazione[max_s];
    char data[11];
    char ora_partenza[9];
    char ora_arrivo[9];
    int ritardo;
} corsa;

typedef enum{
    ord_data_f,
    ord_data_v,
    ord_cod_f,
    ord_cod_v,
    ord_part_f,
    ord_part_v,
    ord_arr_f,
    ord_arr_v,
    quit
} comandi;

void read_and_store_data(FILE *f, corsa tratte[], int n);
int leggi_comando(char comando[]);
int seleziona_dati(int n,int c, corsa *p_codice[], corsa *p_arrivo[], corsa *p_data[], corsa *p_partenza[]);
void ordina_per_codice(corsa tratte[], int n, corsa *p_codice[]);
void ordina_per_data(corsa tratte[], int n, corsa *p_data[]);
void ordina_per_partenza(corsa tratte[], int n, corsa *p_partenza[]);
void ordina_per_arrivo(corsa tratte[], int n, corsa *p_arrivo[]);
void print_on_file(corsa *p[],int n);
void print_on_screen(corsa *p[],int n);

int main(int argc, char argv[]){
    
    FILE *f;
    int righe, c, fine = 1;
    char comando[max_s], codice[10];
    corsa tratte[max_l];
    corsa *p_codice[max_l], *p_arrivo[max_l], *p_partenza[max_l], *p_data[max_l];

    system("cls");

    f = fopen(FILENAME, "r");
    if (f == NULL){
        printf("errore");
        return 1;
    }
    fscanf(f, "%d\n", &righe);
    read_and_store_data(f, tratte, righe);
    fclose(f);
    
    ordina_per_codice(tratte,righe,p_codice);
    ordina_per_data(tratte,righe, p_data);
    ordina_per_partenza(tratte,righe, p_partenza);
    ordina_per_arrivo(tratte,righe, p_arrivo);
    

    do{
        printf("                              || LISTA COMANDI POSSIBILI ||\n\n");
        printf("             COMANDO          ||                         ||     FORMATO    \n");
        printf("stampa su file per data                                        ord_data_f                \n");
        printf("stampa a video per data                                        ord_data_v                \n");
        printf("stampa su file per codice di tratte                            ord_cod_f                 \n");
        printf("stampa a videoper codice di tratte                             ord_cod_v                 \n");
        printf("stampa su file per stazione di partenza                        ord_part_f                \n");
        printf("stampa a video per stazione di partenza                        ord_part_v                \n");
        printf("stampa su file per stazione di arrivo                          ord_arr_f                 \n");
        printf("stampa a video per stazione di arrivo                          ord_arr_v                 \n");
        printf("quit                                                            quit                      \n");

        gets(comando);
        system("cls");
        sscanf(comando, "%s", codice);
        c = leggi_comando(codice);
        fine = seleziona_dati(righe, c, p_codice, p_arrivo, p_data, p_partenza);
        
    } while (!fine);
    
    return 0;
}

void read_and_store_data(FILE *f, corsa tratte[], int n){
    int i;
    char buff[300]; 
    for (i = 0; i < n; i++)
    {
        fgets(buff, 255, f);
        sscanf(buff, "%s %s %s %s %s %s %d",
               tratte[i].codice_tratte, tratte[i].partenza, tratte[i].destinazione,
               tratte[i].data,tratte[i].ora_partenza,tratte[i].ora_arrivo,&tratte[i].ritardo);
    }
}

int leggi_comando(char comando[]){

    int c = 0;
    char tabella[9][max_s] = {
        "ord_data_f","ord_data_v", "ord_cod_f","ord_cod_v", "ord_part_f","ord_part_v", "ord_arr_f","ord_arr_v","quit"};

    while (c < 9 && strcmp(tabella[c], comando) != 0)
    {
        c++;
    }

    return (c);
}

int seleziona_dati(int n, int c, corsa *p_codice[], corsa *p_arrivo[], corsa *p_data[], corsa *p_partenza[]){
    switch (c)
    {
        case ord_data_f:
            print_on_file(p_data,n);
        break;

        case ord_data_v:
            print_on_screen(p_data, n);
        break;

        case ord_cod_f:
            print_on_file(p_codice,n);
        break;

        case ord_cod_v:
             print_on_screen(p_codice, n);
        break;

        case ord_part_f:
            print_on_file(p_partenza,n);
        break;

        case ord_part_v:
            print_on_screen(p_partenza, n);
        break;

        case ord_arr_f:
            print_on_file(p_arrivo,n);
        break;

        case ord_arr_v:
            print_on_screen(p_arrivo, n);
        break;

        case quit:
        return 1;

    default:
        printf("il comando inserito non e riconosciuto come comando\nper favore inseriscine uno in forma corretta\n\n\n");
        break;
    }

    return 0;
}

void ordina_per_codice(corsa tratte[], int n, corsa *p_codice[]){
    int i,j;
    corsa *t;
    p_codice[0]=&tratte[0];
    for(i=1;i<n;i++){
        t = &tratte[i];
        j=i-1;
        while(j>=0 && strcmp((*t).codice_tratte , (*p_codice[j]).codice_tratte)<0){
            p_codice[j+1]=p_codice[j];
            j--;
        }
        p_codice[j+1]= t;

    }
}

void ordina_per_data(corsa tratte[], int n, corsa *p_data[]){
    int i,j;
    corsa *t;
    p_data[0] = &tratte[0];
    for(i=1;i<n;i++){
        t = &tratte[i];
        j=i-1;
        while(j>=0 && ((strcmp((*t).data,(*p_data[j]).data)>0) || ( strcmp((*t).data,(*p_data[j]).data)==0 && strcmp((*t).ora_partenza,(*p_data[j]).ora_partenza)>0))){
            p_data[j+1]=p_data[j];
            j--;
        }
        p_data[j+1]= t;
    }
}

void ordina_per_partenza(corsa tratte[], int n, corsa *p_partenza[]){
    int i,j;
    corsa *t;
    p_partenza[0]=&tratte[0];
    for(i=1;i<n;i++){
        t = &tratte[i];
        j=i-1;
        while(j>=0 && strcmp((*t).partenza,(*p_partenza[j]).partenza)<0 ){
            p_partenza[j+1]=p_partenza[j];
            j--;
        }
        p_partenza[j+1]= t;

    }
}

void ordina_per_arrivo(corsa tratte[], int n, corsa *p_arrivo[]){
    int i,j;
    corsa *t;
    p_arrivo[0]=&tratte[0];
    for(i=1;i<n;i++){
        t = &tratte[i];
        j=i-1;
        while(j>=0 && strcmp((*t).destinazione,(*p_arrivo[j]).destinazione)<0 ){
            p_arrivo[j+1]=p_arrivo[j];
            j--;
        }
        p_arrivo[j+1]= t;

    }
}

void print_on_file(corsa *p[],int n){
    int i;
    FILE *g;
    g= fopen(FILENAME, "w");
    fprintf(g,"%d",n);
    for(i=0;i<n;i++){
        fprintf(g,"\n%s %s %s %s %s %s %d",p[i]->codice_tratte, p[i]->partenza, p[i]->destinazione,p[i]->data, p[i]->ora_partenza, p[i]->ora_arrivo, p[i]->ritardo);
    }
    fclose(g);
}

void print_on_screen(corsa *p[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s %s %s %s %s %s %d\n",p[i]->codice_tratte, p[i]->partenza, p[i]->destinazione,p[i]->data, p[i]->ora_partenza, p[i]->ora_arrivo, p[i]->ritardo);
    }
    
}

