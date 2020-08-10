#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max_d 30

void stampa(int m[][max_d], int r, int c);
void rotazione(char sele[], int ind, char dir[], int pos, int m[][max_d], int r, int c);

int main(int argc, char *argv[]){

    int nr, nc,i,j,indice,posizioni;
    char selettore[20], direzione[20];
    FILE *f;
    int matrice[max_d][max_d];
    if(argc != 2) return 0;
    f=fopen(argv[1], "r");
    if(f==NULL){
        printf("errore");
        return 0;
    }
    fscanf(f, "%d %d\n", &nr, &nc);
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            fscanf(f,"%d", &matrice[i][j]);
        }

    }
    stampa(matrice, nr,nc);


    printf("\nSELETTORE (riga,colonna,fine) : ");
    scanf("%s",selettore);
    
    while(strcmp("fine", selettore)!=0){
        
        printf("\nINDICE : ");
        scanf("%d", &indice);
        printf("\nDIREZIONE (su, giu, destra, sinistra) : ");
        scanf("%s", direzione);
        printf("\nPOSIZIONI : ");
        scanf("%d", & posizioni);
        printf("\n");

        rotazione(selettore,indice,direzione,posizioni,matrice,nr,nc);

        printf("\nSELETTORE (riga,colonna,fine) : ");
        scanf("%s",selettore);

    }
    return 0;
}

void stampa(int m[][max_d], int r, int c){
    int i=0,j=0;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("%4d ", m[i][j]);
        }
        printf("\n");
    }
}

void rotazione(char sele[], int ind, char dir[], int pos, int m[][max_d], int r, int c){
    int buf[max_d];
    int i,j=0;
    
    if(strcmp("riga", sele)==0){
        pos=pos%c;
        for(i=0;i<c;i++){
            buf[i]=m[ind][i];
        }
        if(strcmp("destra", dir)==0){
            for(i=pos;i<c;i++){
                m[ind][i]=buf[j];
                j++;
            }
            j=0;
            for(i=pos;i>0;i--){
                m[ind][j]=buf[c-i];
                j++;
            }
        }

        else{
            if(strcmp("sinistra", dir)==0){
                for(i=c-pos;i<c;i++){
                    m[ind][i]=buf[j];
                    j++;
                }
                for(i=0;i<c-pos;i++){
                    m[ind][i]=buf[i+pos];
                }
            }
            
        }
        
    }
    else{
        if(strcmp("colonna",sele)==0){
            pos = pos%r;
            for(i=0;i<r;i++){
                buf[i]=m[i][ind];
            }
            if((strcmp("giu",dir)==0) || (strcmp("giù",dir)==0)){
            for(i=pos;i<c;i++){
                m[i][ind]=buf[j];
                j++;
            }
            j=0;
            for(i=pos;i>0;i--){
                m[j][ind]=buf[c-i];
                j++;
            }
        }

        else{
            
            if(strcmp("su",dir)==0){
                for(i=0;i<c-pos;i++){
                    m[i][ind]=buf[i+pos];
                }
                for(i=c-pos;i<c;i++){
                    m[i][ind]=buf[j];
                    j++;
                }
            }
            

        }
        }
        else{
            printf("errore nei comandi\n");
        }
    }
    stampa(m,r,c);
    
}