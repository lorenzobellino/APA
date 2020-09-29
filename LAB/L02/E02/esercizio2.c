#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "corse.txt"
#define max_l 1000
#define max_s 30

typedef struct{
    int codice_tratta;
    char partenza[max_s];
    char destinazione[max_s];
    int data[3];
    int ora_partenza[2];
    int ora_arrivo[2];
    int ritardo;
} corsa;

typedef enum{
    c_date,
    c_part,
    c_arr,
    c_rit,
    r_cors,
    quit
} comandi;

void read_and_store_data(FILE *f, corsa tratte[], int n);
int leggi_comando(char comando[]);
int seleziona_dati(corsa tratte[], int n, int c, char comando[]);
void partenza_fermate(char stop[], corsa tratte[], int n);
void arrivo_fermate(char stop[], corsa tratte[], int n);
void partenza_date(int d1[], int d2[], corsa tratta[], int n);
void ritardo_date(int d1[], int d2[], corsa tratta[], int n);
void ritardo_id(int id_tratta, corsa tratta[], int n);

int main(int argc, char argv[]){

    FILE *f;
    int righe, c, fine = 1;
    comandi codice_comando;
    char comando[max_s];
    char codice[10];
    corsa tratte[max_l];
    system("cls");
    f = fopen(FILENAME, "r");
    if (f == NULL){
        printf("errore");
        return 1;
    }

    fscanf(f, "%d", &righe);

    read_and_store_data(f, tratte, righe);

    do{
        printf("                                ||  LISTA COMANDI POSSIBILI  ||\n\n");
        printf("             COMANDO                 ||     FORMATO    ||            USO \n");
        printf("elenca corse partite entro due date          c_date             c_date <data1> <data2>\n");
        printf("elenca corse partite da una fermata          c_part             c_part <fermata>\n");
        printf("elenca corse in arrivo a una fermata         c_arr              c_arr <capolinea>\n");
        printf("elenca corse arrivate in ritardo in          c_rit              c_rit <data1> <data2>\nun intervallo due date\n");
        printf("elenca ritardo complessivo dato il           r_cors             r_cors <codice>\ncodice tratta\n");
        printf("esci                                         quit               quit\n");

        gets(comando);
        system("cls");
        sscanf(comando, "%s", codice);
        c = leggi_comando(codice);

        fine = seleziona_dati(tratte, righe, c, comando);

    } while (!fine);
    return 0;
}

void read_and_store_data(FILE *f, corsa tratta[], int n){
    int i, a, b;
    int ora_p[2];
    int ora_a[2];
    char linea[100];
    fgets(linea, 100, f);
    for (i = 0; i < n; i++)
    {
        fgets(linea, 100, f);

        sscanf(linea, "%d %s %s %d/%d/%d %d:%d %d:%d %d",
               &tratta[i].codice_tratta, tratta[i].partenza, tratta[i].destinazione,
               &tratta[i].data[0], &tratta[i].data[1], &tratta[i].data[2],
               &tratta[i].ora_partenza[0], &tratta[i].ora_partenza[1],
               &tratta[i].ora_arrivo[0], &tratta[i].ora_arrivo[1],
               &tratta[i].ritardo);
    }
}

int leggi_comando(char comando[]){

    int c = 0;
    char tabella[6][10] = {
        "c_date", "c_part", "c_arr", "c_rit", "r_cors", "quit"};

    while (c < 6 && strcmp(tabella[c], comando) != 0)
    {
        c++;
    }

    return (c);
}

int seleziona_dati(corsa tratte[], int n, int c, char comando[]){

    char cod[25], fermata[25];
    int d1[3], d2[3];
    int id_tratta;
    switch (c)
    {
    case c_date:
        sscanf(comando, "%s %d/%d/%d %d/%d/%d", cod, &d1[0], &d1[1], &d1[2], &d2[0], &d2[1], &d2[2]);
        partenza_date(d1, d2, tratte, n);

        break;
    case c_part:
        sscanf(comando, "%s %s", cod, fermata);
        partenza_fermate(fermata, tratte, n);
        break;
    case c_arr:
        sscanf(comando, "%s %s", cod, fermata);
        arrivo_fermate(fermata, tratte, n);
        break;
    case c_rit:
        sscanf(comando, "%s %d/%d/%d %d/%d/%d", cod, &d1[0], &d1[1], &d1[2], &d2[0], &d2[1], &d2[2]);
        ritardo_date(d1, d2, tratte, n);
        break;
    case r_cors:

        sscanf(comando, "%s %d", cod, &id_tratta);

        ritardo_id(id_tratta, tratte, n);
        break;
    case quit:
        return 1;

    default:
        sscanf(comando, "%s", cod);
        printf("%s non e riconosciuto come comando\nper favore inseriscine uno in forma corretta\n", cod);
        break;
    }

    return 0;
}

//   || FUNZIONI PER LA GESTIONE DATI||
// quando confronti con le stringhe devi fare tolower

void partenza_date(int d1[], int d2[], corsa tratta[], int n){

    int i = 0, flg = 0;
    printf("tratte partite entro le date: <%d/%d/%d> e <%d/%d/%d>\n", d1[0], d1[1], d1[2], d2[0], d2[1], d2[2]);

    for (i = 0; i < n; i++)
    {
        if (tratta[i].data[2] > d1[2] && tratta[i].data[2] < d2[2])
        {
            printf("codice: %d\ndata: %d/%d/%d\npartenza: %s\narrivo: %s\n", tratta[i].codice_tratta, tratta[i].data[0], tratta[i].data[1], tratta[i].data[2], tratta[i].partenza, tratta[i].destinazione);
            flg = 1;
        }
        else
        {
            if (((tratta[i].data[2] == d1[2] || tratta[i].data[2] == d2[2]) && (tratta[i].data[1] > d1[1] && tratta[i].data[1] < d2[1])))
            {
                printf("codice: %d\ndata: %d/%d/%d\npartenza: %s\narrivo: %s\n", tratta[i].codice_tratta, tratta[i].data[0], tratta[i].data[1], tratta[i].data[2], tratta[i].partenza, tratta[i].destinazione);
                flg = 1;
            }
            else
            {
                if ((tratta[i].data[2] == d1[2] || tratta[i].data[2] == d2[2]) && (tratta[i].data[1] == d1[1] || tratta[i].data[1] == d2[1]) && (tratta[i].data[0] >= d1[0] && tratta[i].data[0] <= d2[0]))
                {
                    printf("codice: %d\ndata: %d/%d/%d\npartenza: %s\narrivo: %s\n", tratta[i].codice_tratta, tratta[i].data[0], tratta[i].data[1], tratta[i].data[2], tratta[i].partenza, tratta[i].destinazione);
                    flg = 1;
                }
            }
        }
    }
    if (flg == 0)
        printf("nessuna tratta con queste specifiche e stata trovata\n");
}

void partenza_fermate(char stop[], corsa tratta[], int n){
    int l = 0, flg = 0;

    printf("tratte partite dalla fermata: <%s> \n", stop);
    for (l = 0; l < n; l++)
    {
        if (strcmp(tratta[l].partenza, stop) == 0)
        {
            printf("codice: %d\nora partenza: %d:%d\n", tratta[l].codice_tratta, tratta[l].ora_partenza[0], tratta[l].ora_partenza[1]);
            flg = 1;
        }
    }
    if (flg == 0)
        printf("nessuna linea passa da questa fermata, ricontrolla\n");
}

void arrivo_fermate(char stop[], corsa tratta[], int n){
    int i = 0, flg = 0;
    printf("tratte in arrivo alla fermata: <%s> \n", stop);
    for (i = 0; i < n; i++)
    {
        if (strcmp(stop, tratta[i].destinazione) == 0)
        {
            printf("codice: %d\nora partenza: %d:%d\n", tratta[i].codice_tratta, tratta[i].ora_arrivo[0], tratta[i].ora_arrivo[1]);
            flg = 1;
        }
    }
    if (flg == 0)
        printf("nessuna linea passa da questa fermata, ricontrolla\n");
}

void ritardo_date(int d1[], int d2[], corsa tratta[], int n){
    int i = 0, flg;
    printf("tratte che hanno tardato entro le date: <%d/%d/%d> e <%d/%d/%d> che hanno tardato\n", d1[0], d1[1], d1[2], d2[0], d2[1], d2[2]);
    for (i = 0; i < n; i++)
    {
        if(tratta[i].ritardo != 0){
           if (tratta[i].data[2] > d1[2] && tratta[i].data[2] < d2[2])
        {
            printf("codice: %d\ndata: %d/%d/%d\npartenza: %s\narrivo: %s\nritardo: %d\n", tratta[i].codice_tratta, tratta[i].data[0], tratta[i].data[1], tratta[i].data[2], tratta[i].partenza, tratta[i].destinazione, tratta[i].ritardo);
            flg = 1;
        }
        else
        {
            if (((tratta[i].data[2] == d1[2] || tratta[i].data[2] == d2[2]) && (tratta[i].data[1] > d1[1] && tratta[i].data[1] < d2[1])))
            {
                printf("codice: %d\ndata: %d/%d/%d\npartenza: %s\narrivo: %s\nritardo: %d\n", tratta[i].codice_tratta, tratta[i].data[0], tratta[i].data[1], tratta[i].data[2], tratta[i].partenza, tratta[i].destinazione, tratta[i].ritardo);
                flg = 1;
            }
            else
            {
                if ((tratta[i].data[2] == d1[2] || tratta[i].data[2] == d2[2]) && (tratta[i].data[1] == d1[1] || tratta[i].data[1] == d2[1]) && (tratta[i].data[0] >= d1[0] && tratta[i].data[0] <= d2[0]))
                {
                    printf("codice: %d\ndata: %d/%d/%d\npartenza: %s\narrivo: %s\nritardo: %d\n", tratta[i].codice_tratta, tratta[i].data[0], tratta[i].data[1], tratta[i].data[2], tratta[i].partenza, tratta[i].destinazione, tratta[i].ritardo);
                }
                flg = 1;
            }
        }
        printf("\n"); 
        }
        
    }
    if (flg == 0)
        printf("nessuna tratta con queste specifiche e stata trovata\n");
}

void ritardo_id(int id_tratta, corsa tratta[], int n){
    int i = 0, ritardo_tot = 0, flg = 0;

    printf("stampa il ritardo totale dato il codice tratta\n");
    for (i = 0; i < n; i++)
    {
        if (tratta[i].codice_tratta == id_tratta)
        {
            ritardo_tot = ritardo_tot + tratta[i].ritardo;
            flg = 1;
        }
    }
    if (flg == 0)
        printf("questo codice non esiste\n");
    else
        printf("codice: %d\nritardo totale: %d\n", id_tratta, ritardo_tot);
}
