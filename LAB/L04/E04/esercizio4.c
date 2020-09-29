#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

#define FILENAME "log.txt"
#define max_l 10000
#define max_s 55

typedef struct{
    char codice_tratte[15];
    char partenza[max_s];
    char destinazione[max_s];
    char data[12];
    char ora_partenza[10];
    char ora_arrivo[10];
    int ritardo;
} corsa;

typedef enum{
    print_f,
    print_v,
    ord_data,
    ord_cod,
    ord_part,
    ord_arr,
    ric_part,
    quit
} comandi;

void read_and_store_data(FILE *f, corsa tratte[], int n);
int leggi_comando(char comando[]);
int seleziona_dati(corsa tratte[], int n, int c, char comando[], int *ordine_corrente);
void print_on_file(corsa tratte[],int n);
void print_on_screen(corsa tratte[],int n);
void ordina_per_data(corsa tratte[], int n);
void ordina_per_codice(corsa tratte[], int n);
void ordina_per_partenza(corsa tratte[], int n);
void ordina_per_arrivo(corsa tratte[], int n);
void ricerca_lineare(corsa tratte[],int n,char cod[]);
void ricerca_dicotomica(corsa tratte[], int n,char cod[]);
int controllo_ordine(char staz_part[],char cod[]);
char *cerca_exp(char *src, char *regexp);

int main(int argc, char argv[]){
    
    FILE *f;
    int righe, c, fine = 1, ordine_corrente=-1;
    char comando[max_s], codice[10];
    corsa tratte[max_l];
    system("cls");

    f = fopen(FILENAME, "r");
    if (f == NULL){
        printf("errore");
        return 1;
    }
    fscanf(f, "%d\n", &righe);
    read_and_store_data(f, tratte, righe);
    fclose(f);

    do{
        printf("                                ||  LISTA COMANDI POSSIBILI  ||\n\n");
        printf("             COMANDO                 ||     FORMATO    ||            USO \n");
        printf("stampa su file                              print_f                 print_f\n");
        printf("stampa a video                              print_v                 print_v\n");
        printf("ordina il file per data                     ord_data                ord_data\n");
        printf("ordina il file per codice di tratte         ord_cod                 ord_cod\n");
        printf("ordina il file per stazione di partenza     ord_part                ord_part\n");
        printf("ordina il file per stazione di arrivo       ord_arr                 ord_arr\n");
        printf("ricerca per stazione di partenza            ric_part                ric_part\n");
        printf("quit                                        quit                    quit\n");

        gets(comando);
        system("cls");
        sscanf(comando, "%s", codice);
        c = leggi_comando(codice);
        fine = seleziona_dati(tratte, righe, c, comando, &ordine_corrente);
    } while (!fine);
    
    return 0;
}

void read_and_store_data(FILE *f, corsa tratte[], int n){
    int i;
    char linea[256];
    
    for (i = 0; i < n; i++)
    {
        fgets(linea, 256, f);
        sscanf(linea, "%s %s %s %s %s %s %d\n",
               tratte[i].codice_tratte, tratte[i].partenza, tratte[i].destinazione,
               tratte[i].data,
               tratte[i].ora_partenza,
               tratte[i].ora_arrivo,
               &tratte[i].ritardo);
    }
}


int leggi_comando(char comando[]){

    int c = 0;
    char tabella[8][10] = {
        "print_f", "print_v", "ord_data", "ord_cod", "ord_part", "ord_arr","ric_part","quit"};

    while (c < 8 && strcmp(tabella[c], comando) != 0){
        c++;
    }
    return (c);
}

int seleziona_dati(corsa tratte[], int n, int c, char comando[], int* ordine_corrente){
    char cod[max_s];
    switch (c)
    {
        case print_f:
            print_on_file(tratte,n);
        break;

        case print_v:
            print_on_screen(tratte, n);
        break;

        case ord_data:
            if(*ordine_corrente!=1){
                ordina_per_data(tratte,n);
                *ordine_corrente = 1;
            }
        break;

        case ord_cod:
            if(*ordine_corrente!=2){
                ordina_per_codice(tratte,n);
                *ordine_corrente= 2; 
            } 
        break;

        case ord_part:
            if(*ordine_corrente!=3){
                ordina_per_partenza(tratte,n);
                *ordine_corrente= 3;
            }
        break;

        case ord_arr:
            if(*ordine_corrente!=4){
                ordina_per_arrivo(tratte,n);
                *ordine_corrente= 4;
            }
        break;

        case ric_part:
            sscanf(comando,"%*s %s",cod);
            if(*ordine_corrente!=3) ricerca_lineare(tratte,n,cod);
            else ricerca_dicotomica(tratte,n,cod);
        break;
        case quit:
        return 1;

    default:
        printf("%s non e riconosciuto come comando\nper favore inseriscine uno in forma corretta\n\n\n", comando);
        break;
    }

    return 0;
}

void print_on_file(corsa tratte[],int n){
    int i;
    FILE *g;
    g= fopen(FILENAME, "w");
    fprintf(g,"%d\n",n);
    for(i=0;i<n;i++){
        fprintf(g,"%s %s %s %s %s %s %d\n",
               tratte[i].codice_tratte, tratte[i].partenza, tratte[i].destinazione,
               tratte[i].data, tratte[i].ora_partenza, tratte[i].ora_arrivo, tratte[i].ritardo);
    }
    fclose(g);
}

void print_on_screen(corsa tratte[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s %s %s %s %s %s %d\n",
               tratte[i].codice_tratte, tratte[i].partenza, tratte[i].destinazione,
               tratte[i].data, tratte[i].ora_partenza, tratte[i].ora_arrivo, tratte[i].ritardo);
    }
    
}

void ordina_per_data(corsa tratte[], int n){
    int i,j;
    corsa t;
    for(i=0;i<n;i++){
        for(j=0;j<n-i;j++){
            if(strcmp(tratte[j].data,tratte[j+1].data)<0){
                t=tratte[j];
                tratte[j]=tratte[j+1];
                tratte[j+1]=t;
            }
            else{
                if(strcmp(tratte[j].data,tratte[j+1].data)==0 && strcmp(tratte[j].ora_partenza,tratte[j+1].ora_partenza)<0){
                    t=tratte[j];
                    tratte[j]=tratte[j+1];
                    tratte[j+1]=t;
                }
            }
        }
    }

}

void ordina_per_codice(corsa tratte[], int n){
    int i,j;
    corsa t;
    for(i=0;i<n;i++){
        for(j=0;j<n-i;j++){
            if(strcmp(tratte[j].codice_tratte,tratte[j+1].codice_tratte)<0){
                t=tratte[j];
                tratte[j]=tratte[j+1];
                tratte[j+1]=t;
                
            }
            
        }
    }
}

void ordina_per_partenza(corsa tratte[], int n){
    int i,j;
    corsa t;
    for(i=0;i<n;i++){
        for(j=0;j<n-i;j++){
            if(strcmp(tratte[j].partenza,tratte[j+1].partenza)>0){
                t=tratte[j];
                tratte[j]=tratte[j+1];
                tratte[j+1]=t;
            }
            
        }
    }
}

void ordina_per_arrivo(corsa tratte[], int n){
    int i,j;
    corsa t;
    for(i=0;i<n;i++){
        for(j=0;j<n-i;j++){
            if(strcmp(tratte[j].destinazione,tratte[j+1].destinazione)>0){
                t=tratte[j];
                tratte[j]=tratte[j+1];
                tratte[j+1]=t;
            }
            
        }
    }
}

void ricerca_lineare(corsa tratte[],int n,char cod[]){
    
    int i,j;
    char *c= NULL;
    for(i=0;i<n;i++){
        c = NULL;
        c = cerca_exp( tratte[i].partenza, cod);
        
        if(c!=NULL){
            printf("%s %s %s %s %s %s %d\n",tratte[i].codice_tratte, tratte[i].partenza, tratte[i].destinazione,
                tratte[i].data, tratte[i].ora_partenza, tratte[i].ora_arrivo, tratte[i].ritardo);
        }
    }

}

char * cerca_exp(char *src, char *regexp){

    if(strlen(regexp)!=0){
        if(*src == tolower(*regexp) || *src == toupper(*regexp)) src = cerca_exp((src+1), (regexp+1));
        else return NULL;
    }
    return src;
}

void ricerca_dicotomica(corsa tratte[], int n,char cod[]){
        

        int inizio=0, fine=n, centro, i, j, trovato=0;
        while(inizio<=fine && !trovato){
            centro = (inizio+fine)/2;
            if( cerca_exp(tratte[centro].partenza,cod) != NULL) trovato=1;
            else{
                if(controllo_ordine(tratte[centro].partenza,cod)) inizio=centro+1;
                else fine=centro-1;  
            } 
        }
        if(inizio<=fine){
            j=centro;
            i=centro-1;
            while(cerca_exp(tratte[j].partenza,cod)!=NULL && j<n){
            printf("%s %s %s %s %s %s %d\n",
               tratte[j].codice_tratte, tratte[j].partenza, tratte[j].destinazione,
               tratte[j].data, tratte[j].ora_partenza, tratte[j].ora_arrivo, tratte[j].ritardo);
               j++;
            }
            while(cerca_exp(tratte[i].partenza,cod)!=NULL&&i>-1){
            printf("%s %s %s %s %s %s %d\n",
               tratte[i].codice_tratte, tratte[i].partenza, tratte[i].destinazione,
               tratte[i].data, tratte[i].ora_partenza, tratte[i].ora_arrivo, tratte[i].ritardo);
               i--;
            }
        }

}
int controllo_ordine(char staz_part[],char cod[]){
    int i;
    for(i=0;i<strlen(cod);i++){
        if(isupper(staz_part[i])&&staz_part[i]<toupper(cod[i])) return 1;
        if(isupper(staz_part[i])&&staz_part[i]>toupper(cod[i])) return 0;
        if(islower(staz_part[i])&&staz_part[i]<tolower(cod[i])) return 1;
        if(islower(staz_part[i])&&staz_part[i]>tolower(cod[i])) return 0;
    }
    return 0;
}
