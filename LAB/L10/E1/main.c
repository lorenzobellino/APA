#include <stdio.h>
#define maxdiag 5000


typedef struct{
    char nome[100];
    int tipologia;
    int d_in;
    int d_out;
    int prec;
    int final;
    float val;
    int diffic;
}elemento;

typedef struct{
    int diag[5];
    int dif;
    float punti;
    int bonus;
}diagonale;

static int DD;
static int DP;

int read_data(elemento elementi[]);
int diag_fit(elemento elementi[], diagonale diagonal, int pos, int e);
int acrobazie(int diag[], elemento elementi[]);
int bonus(int diag[], elemento elementi[]);
int difficolta(diagonale programma[]);
int acrobat_av_in(diagonale programma[], elemento elementi[]);
int acrobat_seq(diagonale programma[], elemento elementi[]);
float calcola_punti(diagonale programma[]);
int accettabile(diagonale programma[], elemento elementi[]);
//int conta_punti(int tmp[], elemento elementi[]);
void print_el(elemento elementi[],int n);
void find_diagonals(elemento elementi[], diagonale diagonali[],int n, int *n_d, int n_e, diagonale tmp);
void azzera_diag(diagonale diagonali[], int n);
void azzera_programma(diagonale p[], diagonale b_p[]);
void copia_diag(diagonale diagonali[], int n, diagonale tmp, int bonus);
void stampa_diag(diagonale diagonali[], int n, elemento elementi[]);
void find_program(diagonale diagonali[],int n_d,diagonale programma[],diagonale b_programma[],elemento elementi[],int p,float *punti,float *max_punti);


//GENERA PRIMA TUTTE LE DIAGONALI POSSIBILI E POI TRAMITE UN ALTRO
//SOTTOPROBLEMA RICORSIVO GENERA IL PROGRAMMA DI GARA !!


int main() {
    int n_elem,i,n_d=0,n_p=0;
    float punti=-1,max_punti=-1;
    elemento elementi[50];
    diagonale tmp,programma[3], b_programma[3];
    diagonale diagonali[maxdiag];
    n_elem = read_data(elementi);
    azzera_diag(diagonali,maxdiag);
    print_el(elementi,n_elem);
    printf("DD : \n");
    scanf("%d",&DD);
    printf("DP : \n");
    scanf("%d", &DP);
    for(i=0;i<5;i++){
        tmp.diag[i]=-1;
    }
    tmp.dif=0;
    tmp.punti=0;
    tmp.bonus=0;
    azzera_programma(programma,b_programma);
    find_diagonals(elementi,diagonali,n_elem,&n_d,n_p,tmp);
    printf("\tn_diagonali : %d\n\n",n_d);
    //stampa_diag(diagonali,n_d, elementi);
    find_program(diagonali,n_d,programma, b_programma,elementi,0, &punti, &max_punti);
    stampa_diag(b_programma,3,elementi);
    printf("\npunteggio totale : %f\n", max_punti);

    return 0;
}

int read_data(elemento elementi[]){
    int n,i;
    FILE *f;
    f=fopen("elementi.txt","r");
    fscanf(f,"%d",&n);
    for(i=0;i<n;i++){
        fscanf(f,"%s %d %d %d %d %d %f %d\n",elementi[i].nome,&elementi[i].tipologia,&elementi[i].d_in,&elementi[i].d_out,
                &elementi[i].prec,&elementi[i].final,&elementi[i].val,&elementi[i].diffic);
    }
    return n;
}

void print_el(elemento elementi[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s %d %d %d %d %d %.1f %d\n",elementi[i].nome,elementi[i].tipologia,elementi[i].d_in,elementi[i].d_out,
               elementi[i].prec,elementi[i].final,elementi[i].val,elementi[i].diffic);
    }
}

void azzera_diag(diagonale diagonali[], int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<5;j++){
            diagonali[i].diag[j]=-1;
        }
        diagonali[i].punti=0;
        diagonali[i].dif=0;
        diagonali[i].bonus=0;
    }
}

void azzera_programma(diagonale p[], diagonale b_p[]){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            p[i].diag[j]=-1;
            b_p[i].diag[j]=-1;
        }
        p[i].dif=-1;
        p[i].bonus=0;
        p[i].punti=-1;
        b_p[i].dif=-1;
        b_p[i].bonus=0;
        b_p[i].punti=-1;
    }
}

void find_diagonals(elemento elementi[], diagonale diagonali[], int n, int *n_d, int n_p, diagonale tmp) {
    int i;
    if(elementi[tmp.diag[n_p-1]].final==1 || tmp.dif==DD || n_p>=5){
        if(acrobazie(tmp.diag,elementi)){
            if(bonus(tmp.diag,elementi)) copia_diag(diagonali,*n_d,tmp,1);
            else copia_diag(diagonali, *n_d, tmp, 0);
            *n_d += 1;
        }
        return;
    }
    for(i=0;i<n;i++){
        if(diag_fit(elementi,tmp, n_p, i)){
            tmp.diag[n_p]=i;
            tmp.dif+=elementi[i].diffic;
            tmp.punti+=elementi[i].val;
            find_diagonals(elementi,diagonali,n,n_d,n_p+1,tmp);
            tmp.dif-=elementi[i].diffic;
            tmp.punti-=elementi[i].val;
            tmp.diag[n_p]=-1;
        }
    }
    if(acrobazie(tmp.diag,elementi)){
        if(bonus(tmp.diag,elementi)) copia_diag(diagonali,*n_d,tmp,1);
        else copia_diag(diagonali, *n_d, tmp, 0);
        *n_d+=1;
    }
    //copia_diag(diagonali,*n_d,tmp,);
}

int diag_fit(elemento elementi[], diagonale diagonal, int pos, int e){

    if(diagonal.dif+elementi[e].diffic>DD) return 0;
    if(pos==0 &&((elementi[e].prec==1) || (elementi[e].d_in != 1))) return 0;
    if(pos>0 && elementi[diagonal.diag[pos-1]].d_out != elementi[e].d_in) return 0;
    return 1;

}

void copia_diag( diagonale diagonali[], int n, diagonale tmp, int bonus){
    int i=0;
    while(tmp.diag[i]>=0 && i<5){
        diagonali[n].diag[i]=tmp.diag[i];
        i++;
    }
    diagonali[n].punti=tmp.punti;
    diagonali[n].dif=tmp.dif;
    diagonali[n].bonus=bonus;
}

void stampa_diag(diagonale diagonali[], int n, elemento elementi[]){
    int i=0,j=0;
    for(i=0;i<n;i++){
            printf("diagonale %d :\n",i+1);
            while(diagonali[i].diag[j]>=0 && j<5){
                printf("%s ", elementi[diagonali[i].diag[j]].nome);
                j++;
            }
            j=0;
        while(diagonali[i].diag[j]>=0 && j<5){
            printf("%d-%d ", elementi[diagonali[i].diag[j]].d_in,elementi[diagonali[i].diag[j]].d_out);
            j++;
        }
        j=0;
        printf("acrobazie ( ");
        while(diagonali[i].diag[j]>=0 && j<5){
            printf("%d ", elementi[diagonali[i].diag[j]].tipologia);
            j++;
        }
        j=0;
        printf(")\nprecedenza(");
        while(diagonali[i].diag[j]>=0 && j<5){
            printf("%d ", elementi[diagonali[i].diag[j]].prec);
            j++;
        }
        j=0;
        printf(")\nfinale(");
        while(diagonali[i].diag[j]>=0 && j<5){
            printf("%d ", elementi[diagonali[i].diag[j]].final);
            j++;
        }
        j=0;
        printf(")\n");
            printf(" \ndifficolta' : %d, punti : %f\n\n",diagonali[i].dif, diagonali[i].punti);

        }
}

int acrobazie(int diag[], elemento elementi[]){
    int i=0,ac=0;
    while(diag[i]>=0 && i<5 && !ac){
        if(elementi[diag[i]].tipologia>0) ac=1;
        i++;
    }
    return ac;
}

int bonus(int diag[], elemento elementi[]){
    int i=0, b=0;
    while(diag[i]>=0 && i<5 && !b){
        if(elementi[diag[i]].diffic>=8) b=1;
        i++;
    }
    return b;
}

void find_program(diagonale diagonali[],int n_d,diagonale programma[], diagonale b_programma[],elemento elementi[], int p,float *punti, float *max_punti){
    int i,j;
    if(p>2){
        //if(difficolta(programma) && acrobat_av_in(programma,elementi) && acrobat_seq(programma,elementi)){
        if(accettabile(programma,elementi))
            *punti = calcola_punti(programma);
            if(*punti > *max_punti){
                for(j=0;j<3;j++){
                    b_programma[j]=programma[j];
                }
                //b_programma=programma;
                *max_punti = *punti;
                //stampa_diag(b_programma,3,elementi);
                //printf("best prog : %f\n",*max_punti);
            }
            return;
        }

    for(i=0;i<n_d;i++){
        programma[p]=diagonali[i];
        find_program(diagonali, n_d, programma,b_programma,elementi,p+1, punti, max_punti);
    }
}

int accettabile(diagonale programma[], elemento elementi[]){
    int i,j=0,s=0,avanti=0, indietro=0,seq=0;
    for(i=0;i<3;i++){
        s+=programma[i].dif;
    }
    if(s>DP) return 0;
    for(i=0;i<3 && (!avanti || !indietro);i++){
        while(programma[i].diag[j]>=0 && j<5 && ((avanti==0 || indietro ==0) || seq<2)){
            if(elementi[programma[i].diag[j]].tipologia == 1){
                indietro=1;
                seq+=1;
            }
            else {
                if(elementi[programma[i].diag[j]].tipologia == 2){
                    avanti=1;
                    seq+=1;
                }
                else{
                    if(seq<2) seq=0;
                }
            }
            j++;
        }
        j=0;
    }
    if(avanti==0 || indietro==0) return 0;
    if(seq<2) return 0;
    return 1;

}

float calcola_punti(diagonale programma[]){
    int i;
    float s=0;
    for(i=0;i<2;i++){
        s+=programma[i].punti;
    }
    if(programma[2].bonus) s+=(programma[2].punti*1.5);
    else s+=programma[2].punti;
    return s;
}
