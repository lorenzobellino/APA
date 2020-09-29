#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILENAME1 "matrice1.txt"
#define FILENAME2 "matrice2.txt"

int **malloc2Dr(int *r, int*c);
void malloc2Dp(int ***p, int *r, int *c);
void stampa(int **p, int r, int c);
void stampav(int *p, int n);
void separa(int **matr, int nr, int nc, int **p_b, int **p_n, int * d_b, int *d_n);
void free2d(int **m, int nr);

int main(int argc, char *argv[]){
    int **p, **q, *p_b, *p_n, r, c, i, j, dim_bianchi, dim_neri;
    
    p = malloc2Dr(&r,&c);
    malloc2Dp(&q,&r,&c);
    
    stampa(p,r,c);
    stampa(q,r,c);

    separa(p,r,c,&p_b, &p_n,&dim_bianchi,&dim_neri);
    printf("\n\n\t\t\t|||||   STAMPA VETTORE BIANCHI    |||||\n\n");
    stampav(p_b,dim_bianchi);
    printf("\n\n\t\t\t|||||   STAMPA VETTORE NERI   |||||\n\n");
    stampav(p_n,dim_neri);
    
    free2d(p,r);
    free2d(q,r);

    free(p_b);
    free(p_n);
    return 0;
}

int **malloc2Dr(int *r, int*c){
    
    FILE *f;
    int **p,i,j;
    f= fopen(FILENAME2, "r");
    if(f==NULL) return NULL;

    fscanf(f, "%d %d\n", r,c);
    p = (int **) malloc( (*r) * sizeof(int *));
    for(i=0;i<(*r);i++){
        p[i] = malloc((*c) * sizeof(int));
        for(j=0;j<(*c);j++){
            fscanf(f,"%d",&p[i][j]);
        }
    }
    fclose(f);
    return p;
}

void malloc2Dp(int ***p, int *r, int *c){
    FILE *f;
    int **m,i,j;
    f= fopen(FILENAME1, "r");
    if(f==NULL) return;

    fscanf(f, "%d %d\n", r,c);
    m = (int **) malloc( (*r) * sizeof(int *));
    for(i=0;i<(*r);i++){
        m[i] = malloc((*c) * sizeof(int));
        for(j=0;j<(*c);j++){
            fscanf(f,"%d",&m[i][j]);
        }
    }
    *p=m;
    fclose(f);
}

void stampa(int **p, int r, int c){
    int i,j;
    printf("\n\t\t|||||||||||||       STAMPA MATRICE      ||||||||||||||\n\n\n");
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    
}

void stampav(int *p, int n){
    int i=0;
    for(i=0;i<n;i++){
        printf("%d ", p[i]);
    }
}

void separa(int **matr, int nr, int nc, int **p_b, int **p_n, int *d_b, int *d_n){
    int *b,*n;
    int i,j,k=0,z=0;
    if(nr%2 == 1 && nc %2 == 1){
        *d_n = (nr*nc)/2;
        *d_b = ((nr*nc)/2)+1;
    }
    else{
        *d_n = (nr*nc)/2;
        *d_b = (nr*nc)/2;
    }
    b=(int *) malloc((*d_b)*sizeof(int));
    n=(int *) malloc((*d_n)*sizeof(int));
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if((i+j)%2==0){
                b[k]=matr[i][j];
                k++;
            } 
            else {
                n[z]= matr[i][j];
                z++;
            }
        }
    
    }
    *p_b = b;
    *p_n = n;
}

void free2d(int **m, int nr) {   
    int i;   
    for (i=0; i<nr; i++) {     
        free(m[i]);   
        }   
    free(m); 
}