#include <stdio.h>
#include "graph.h"

int stampa_scelte();

int main() {
    GRAPH G;
    int scelta,flg=0;
    G = GRAPH_load("GRAPH.txt");
    do{
        scelta=stampa_scelte();
        if(scelta!=3 || flg) SCELTE(scelta,&flg,G);
        else printf("devi ancora generare la lista delle adiacenze\n\n");
    }while(scelta != 5);
    GRAPH_free(G);
    return 0;
}
int stampa_scelte(){
    int s;
    printf("\n[1] -> elenca i vertici in ordine alfabetico\n\te per ogni vertice indica gli archi che insistono su di esso\n");
    printf("[2] -> dati 3 vertici verificare se sono adiacenti (con matrice delle adiacenze)\n");
    printf("[3] -> dati 3 vertici verificare se sono adiacenti (con lista delle adiacenze)\n");
    printf("[4] -> genera la lista delle adiacenze a partire dalla matrice delle adiacenze\n");
    printf("[5] -> termina il programma\n");
    scanf("%d",&s);
    return s;
}