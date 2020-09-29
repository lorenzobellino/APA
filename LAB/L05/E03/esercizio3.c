#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define max_s 50

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
    data_f,
    data_v,
    cod_f,
    cod_v,
    part_f,
    part_v,
    arr_f,
    arr_v,
    read_file,
    quit
} comandi;

corsa** read_and_store_data(char filename[], int *righe, corsa **tratte);
void ordinamenti(corsa **tratte, int n, corsa ***p_codice, corsa ***p_data, corsa ***p_partenza, corsa ***p_arrivo);
int leggi_comando(char comando[]);
int seleziona_dati(int *righe,int c, corsa ***p_codice, corsa ***p_arrivo, corsa ***p_data, corsa ***p_partenza, char filename[], char comando[], corsa ***tratte);
corsa** ordina_per_codice(corsa **tratte, int n, corsa **p_codice);
corsa** ordina_per_data(corsa **tratte, int n, corsa **p_data);
corsa** ordina_per_partenza(corsa **tratte, int n, corsa **p_partenz);
corsa** ordina_per_arrivo(corsa **tratte, int n, corsa **p_arrivo);
void freelog(corsa **p_arrivo, corsa **p_codice, corsa **p_data, corsa **p_partenza, corsa **tratte, int n);
void print_on_file(corsa **p,int n,char filename[]);
void print_on_screen(corsa **p,int n);

int main(){
    
    FILE *f;
    int righe, c, fine = 1;
    char comando[max_s], codice[15], FILENAME[max_s] = "log.txt";
    corsa **tratte, **p_codice, **p_arrivo, **p_partenza, **p_data;
    system("cls");

    tratte = read_and_store_data(FILENAME, &righe, tratte);
    
    ordinamenti(tratte,righe,&p_codice,&p_data,&p_partenza,&p_arrivo);
    
    do{
        printf("                              || LISTA COMANDI POSSIBILI ||\n\n");
        printf("             COMANDO          ||                         ||           FORMATO    \n");
        printf("stampa su file per data                                        data_f <FILENAME>               \n");
        printf("stampa a video per data                                        data_v                           \n");
        printf("stampa su file per codice di tratte                            cod_f <FILENAME>                \n");
        printf("stampa a videoper codice di tratte                             cod_v                            \n");
        printf("stampa su file per stazione di partenza                        part_f <FILENAME>               \n");
        printf("stampa a video per stazione di partenza                        part_v                            \n");
        printf("stampa su file per stazione di arrivo                          arr_f <FILENAME>              \n");
        printf("stampa a video per stazione di arrivo                          arr_v                        \n");
        printf("leggi da nuovo file                                            read_file <FILENAME>             \n");
        printf("quit                                                            quit                                \n");

        gets(comando);
        system("cls");
        sscanf(comando, "%s", codice);
        c = leggi_comando(codice);
        fine = seleziona_dati(&righe, c, &p_codice, &p_arrivo, &p_data, &p_partenza,FILENAME,comando,&tratte);
        
    } while (!fine);
    freelog(p_arrivo,p_codice,p_data,p_partenza,tratte,righe);
    return 0;
}

corsa** read_and_store_data(char filename[], int *righe, corsa **tratte){
    int i;
    char linea[300];
    FILE *f;
    f = fopen(filename, "r");
    if (f != NULL){
    
        fscanf(f, "%d\n", righe);
        
        tratte =(corsa**) malloc((*righe)*sizeof(corsa*));
        for (i = 0; i < *righe; i++){
            tratte[i] = (corsa*) malloc(sizeof(corsa));
            fgets(linea, 255, f);
            sscanf(linea, "%s %s %s %s %s %s %d",
               (tratte[i])->codice_tratte, (tratte[i])->partenza, (tratte[i])->destinazione,
               (tratte[i])->data,
               (tratte[i])->ora_partenza,
               (tratte)[i]->ora_arrivo,
               &(tratte)[i]->ritardo);
        }
    }
    else{
        printf("\n\nnon e' stato possibile aprire il file\n\n");
    }
    
    fclose(f);
    return tratte;
}

void ordinamenti(corsa **tratte, int n, corsa ***p_codice, corsa ***p_data, corsa ***p_partenza, corsa ***p_arrivo){
    *p_codice = ordina_per_codice(tratte,n,*p_codice);
    *p_data = ordina_per_data(tratte,n, *p_data);
    *p_partenza = ordina_per_partenza(tratte,n, *p_partenza);
    *p_arrivo = ordina_per_arrivo(tratte,n, *p_arrivo);
}

int leggi_comando(char comando[]){

    int c = 0;
    char tabella[10][30] = {
        "data_f","data_v", "cod_f","cod_v", "part_f","part_v", "arr_f","arr_v","read_file","quit"};

    while (c < 10 && strcmp(tabella[c], comando) != 0)
    {
        c++;
    }

    return (c);
}

int seleziona_dati(int *righe, int c, corsa ***p_codice, corsa ***p_arrivo, corsa ***p_data, corsa ***p_partenza,char filename[],char comando[],corsa ***tratte){
    char buff[max_s];
    
    switch (c){
        case data_f:
            sscanf(comando,"%*s %s", filename);
            print_on_file(*p_data,*righe,filename);
        break;

        case data_v:
            print_on_screen(*p_data, *righe);
        break;

        case cod_f:
            sscanf(comando,"%*s %s", filename);
            print_on_file(*p_codice,*righe,filename);
        break;

        case cod_v:
             print_on_screen(*p_codice, *righe);
        break;

        case part_f:
            
            sscanf(comando,"%*s %s", filename);
            print_on_file(*p_partenza,*righe,filename);
        break;

        case part_v:
            print_on_screen(*p_partenza, *righe);
        break;

        case arr_f:
            sscanf(comando,"%*s %s", filename);
            print_on_file(*p_arrivo,*righe,filename);
        break;

        case arr_v:
            print_on_screen(*p_arrivo, *righe);
        break;

        case read_file:
            sscanf(comando,"%*s %s",  filename);
            freelog(*p_arrivo,*p_codice,*p_data,*p_partenza,*tratte,*righe);
            *tratte = read_and_store_data(filename,&(*righe),*tratte);
            ordinamenti(*tratte,*righe,&(*p_codice),&(*p_data),&(*p_partenza),&(*p_arrivo));

        break;

        case quit:
        return 1;

        default:
            printf("il comando inserito non e riconosciuto come comando\nper favore inseriscine uno in forma corretta\n\n\n");
        break;
    }

    return 0;
}

corsa** ordina_per_codice(corsa **tratte, int n, corsa **p_codice){
    int i,j;
    corsa *t;
    p_codice = (corsa**) malloc(n*sizeof(corsa*));
    for(i=0;i<n;i++) p_codice[i] = (corsa*) malloc(sizeof(corsa));
    
    *p_codice=*tratte;
    for(i=1;i<n;i++){
        t = tratte[i];
        j=i-1;
        
        while(j>=0 && strcmp((*t).codice_tratte , (*p_codice[j]).codice_tratte)>0){
            p_codice[j+1]=p_codice[j];
            j--;
        }
        p_codice[j+1]= t;

    }
    return p_codice;
}

corsa** ordina_per_data(corsa **tratte, int n, corsa **p_data){
    int i,j;
    corsa *t;
    p_data = (corsa**) malloc(n*sizeof(corsa*));
    for(i=0;i<n;i++) p_data[i] = (corsa*) malloc(sizeof(corsa));
    *p_data = *tratte;
    for(i=1;i<n;i++){
        t = tratte[i];
        j=i-1;
        while(j>=0 && ((strcmp((*t).data,(*p_data[j]).data)>0) || ( strcmp((*t).data,(*p_data[j]).data)==0 && strcmp((*t).ora_partenza,(*p_data[j]).ora_partenza)>0))){
            p_data[j+1]=p_data[j];
            j--;
        }
        p_data[j+1]= t;
    }
    return p_data;
}

corsa** ordina_per_partenza(corsa **tratte, int n, corsa **p_partenza){
    int i,j;
    corsa *t;
    p_partenza = (corsa**) malloc(n*sizeof(corsa*));
    for(i=0;i<n;i++) p_partenza[i] = (corsa*) malloc(sizeof(corsa));
    *p_partenza= *tratte;
    for(i=1;i<n;i++){
        t = tratte[i];
        j=i-1;
        while(j>=0 && strcmp((*t).partenza,(*p_partenza[j]).partenza)<0 ){
            p_partenza[j+1]=p_partenza[j];
            j--;
        }
        p_partenza[j+1]= t;

    }
    return p_partenza;
}

corsa** ordina_per_arrivo(corsa **tratte, int n, corsa **p_arrivo){
    int i,j;
    corsa *t;
    p_arrivo = (corsa**) malloc(n*sizeof(corsa*));
    for(i=0;i<n;i++) p_arrivo[i] = (corsa*) malloc(sizeof(corsa));
    *p_arrivo= *tratte;
    for(i=1;i<n;i++){
        t = tratte[i];
        j=i-1;
        while(j>=0 && strcmp((*t).destinazione,(*p_arrivo[j]).destinazione)<0 ){
            p_arrivo[j+1]=p_arrivo[j];
            j--;
        }
        p_arrivo[j+1]= t;

    }
    return p_arrivo;
}

void print_on_file(corsa *p[],int n, char filename[]){
    int i;
    FILE *g;
    g= fopen(filename, "w");
    fprintf(g,"%d",n);
    for(i=0;i<n;i++){
        fprintf(g,"\n%s %s %s %s %s %s %d",p[i]->codice_tratte, p[i]->partenza, p[i]->destinazione,p[i]->data, p[i]->ora_partenza, p[i]->ora_arrivo, p[i]->ritardo);
    }
    fclose(g);
}

void print_on_screen(corsa **p, int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s %s %s %s %s %s %d\n",p[i]->codice_tratte, p[i]->partenza, p[i]->destinazione,p[i]->data, p[i]->ora_partenza, p[i]->ora_arrivo, p[i]->ritardo);
    }
    
}

void freelog(corsa **p_arrivo, corsa **p_codice, corsa **p_data, corsa **p_partenza, corsa **tratte, int n){
    int i;
    for(i=0;i<n;i++){
        free(p_arrivo[i]);
        free(p_codice[i]);
        free(p_data[i]);
        free(p_partenza[i]);
        free(tratte[i]);
    }
    free(p_arrivo);
    free(p_codice);
    free(p_data);
    free(p_partenza);
    free(tratte);
}

