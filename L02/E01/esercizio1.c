#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdlib.h>

#define FILENAME "mappa.txt"
#define max_r 50
#define max_n 125

typedef struct{
    int altezza;
    int base;
    int area;
    int vertice[2];
}figure;

void max_altezza(int n_rett, figure rettangolo[]);
void max_larghezza(int n_rett, figure rettangolo[]);
void max_area(int n_rett, figure rettangolo[]);
void leggi_matrice(int matrice[][max_r], int nr, int nc, FILE *f);
int assimila(int matrice[][max_r], int i, int j, figure rettangolo[]);

int main(int argc , char argv[]){
    
    FILE *f;
    int matrice[max_r][max_r];
    int nr, nc;
    int b=0, h=0;
    int r,c;
    int n_rett;
    figure rettangolo[max_n];

    f = fopen(FILENAME, "r");

    if(f == NULL){
        printf("errore");
        return 1;
    }

    fscanf(f,"%d %d\n", &nr, &nc);

    leggi_matrice(matrice, nr, nc, f);
    n_rett=assimila(matrice,nr, nc, rettangolo);
    max_altezza(n_rett,rettangolo);
    max_larghezza(n_rett,rettangolo);
    max_area(n_rett,rettangolo);

    return 0;
}

int assimila(int matrice[][max_r], int i, int j, figure rettangolo[]){
    int a,b,x,y,w;
    int c=0,d;
    for(a=0;a<i;a++){                       
        for(b=0;b<j;b++){
            if(matrice[a][b]==1){           //ogni volta che trovo un 1 nella matrice
                x=a;
                y=b;
                while(matrice[x][y]==1 && y<j){     //scorro sulle colonne finche' leggo 1
                    matrice[x][y]=0;                //se trovo un uno lo cancello per evitare di leggerlo un altra volta
                    y++;
                }
                rettangolo[c].base=y-b;
                y=b;
                x++;
                while(matrice[x][y]==1 && x<i){             //scorro sulle righe finche' leggo 1
                    for(d=b;d<b+rettangolo[c].base;d++){    //per ogni 1 che trovo sulle righe cancello tutta la riga del rettangolo composta da 1
                        matrice[x][d]=0;
                        
                    }
                    x++;
                }
                rettangolo[c].altezza=x-a;
                rettangolo[c].area=rettangolo[c].base* rettangolo[c].altezza;
                rettangolo[c].vertice[0]=a;
                rettangolo[c].vertice[1]=b;
                
                c++;
            }
            
        }
    }
    return c;
}

void leggi_matrice(int matrice[][max_r], int nr, int nc, FILE *f){
    int i,j;
    char c;
    
    for(i=0; i<nr; i++){
    for(j=0; j< nc; j++){
        c= fgetc(f);
        matrice[i][j]=  c-'0';
        printf("%d " ,matrice[i][j]);  
        }
        fgetc(f);
        printf("\n");
    }
}

//ricerche sequenziali sul vettore di struct

void max_altezza(int n_rett, figure rettangolo[] ){
    int a;
    int max_a=0;
    int max_val = rettangolo[0].altezza;
    for(a=1;a<n_rett;a++){
        if(rettangolo[a].altezza > max_val){
            max_a=a;
            max_val=rettangolo[a].altezza;
        }
    }
    printf("\n");
    printf("rettangolo di altezza maggiore:\n");
    printf("vertice superiore sinistro : ( %d , %d) \naltezza : | %d |\nbase    : | %d |\narea    : | %d |\n"
    ,rettangolo[max_a].vertice[0],rettangolo[max_a].vertice[1],rettangolo[max_a].altezza,rettangolo[max_a].base,rettangolo[max_a].area);
    
}

void max_larghezza(int n_rett, figure rettangolo[] ){
    int b;
    int max_b=0;
    int max_val = rettangolo[0].base;
    for(b=1;b<n_rett;b++){
        if(rettangolo[b].base > max_val){
            max_b=b;
            max_val=rettangolo[b].base;
        }
    }
    printf("\n");
    printf("rettangolo di base maggiore:\n");
    printf("vertice superiore sinistro : ( %d , %d) \naltezza : | %d |\nbase    : | %d |\narea    : | %d |\n"
    ,rettangolo[max_b].vertice[0],rettangolo[max_b].vertice[1],rettangolo[max_b].altezza,rettangolo[max_b].base,rettangolo[max_b].area);
    
}

void max_area(int n_rett, figure rettangolo[] ){
    int s;
    int max_s=0;
    int max_val = rettangolo[0].area;
    for(s=1;s<n_rett;s++){
        if(rettangolo[s].area > max_val){
            max_s=s;
            max_val=rettangolo[s].area;
        }
    }
    printf("\n");
    printf("rettangolo di area maggiore:\n");
    printf("vertice superiore sinistro : ( %d , %d) \naltezza : | %d |\nbase    : | %d |\narea    : | %d |\n"
    ,rettangolo[max_s].vertice[0],rettangolo[max_s].vertice[1],rettangolo[max_s].altezza,rettangolo[max_s].base,rettangolo[max_s].area);
}









