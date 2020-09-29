#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdlib.h>

#define FILENAME "mappa.txt"
#define max_r 50
#define max_c 50
#define max_n 100

int riconosci_regione(int M[][max_c],int nr, int nc, int r, int c, int *b, int *h);
void leggi_matrice(int matrice[][max_c], int *nr, int *nc, FILE *f);

int main(int argc , char argv[]){

    FILE *f;
    int matrice[max_r][max_c];
    int nr, nc, b=0, h=0, r, c;
   
    f = fopen(FILENAME, "r");

    if(f == NULL){
        printf("errore");
        return 1;
    }
    leggi_matrice(matrice, &nr, &nc, f);
    for(r=0;r<nr;r++){
        for(c=0;c<nc;c++){
            if(riconosci_regione(matrice,nr,nc,r,c, &b, &h)){
        printf("il rettangolo con vertice in (%d,%d) ha \nbase: %d\naltezza: %d\n", r,c,b,h);

            }
        }
    }
    return 0;
}

void leggi_matrice(int matrice[][max_c], int *nr, int *nc, FILE *f){
    int i,j;
    char c;
    fscanf(f,"%d %d", nr, nc);
    fgetc(f);
    for(i=0; i<*nr; i++){
    for(j=0; j< *nc; j++){
        c= fgetc(f);
        matrice[i][j]=  c-'0';
        printf("%d " ,matrice[i][j]);  
        }
        fgetc(f);
        printf("\n");
    }
}

int riconosci_regione(int M[][max_c],int nr, int nc, int r, int c, int *b, int *h){
    *b=0;
    *h=0;
    if(M[r][c]== 0) return 0;               //se il carattere e' uno zero ritorno 0
    if(r!=0 && M[r-1][c]==1) return 0;      //se il carattere sulla riga precedente e' un 1 ritorno 0
    if(c!=0 && M[r][c-1]==1) return 0;      //se il carattere sulla colonna precedente e' un 1 ritorno 0
    
        while(M[r][c+*b]==1){               //altrimenti scorro la colonna fino a che leggo 1
            *b=*b+1;                        
            
        }
        while(M[r+*h][c]==1){               //scorro sulla riga fino a che leggo 1
            *h=*h+1;
        }
        return 1;
}








