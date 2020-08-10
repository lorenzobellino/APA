#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct{
    int punti_1,punti_2;
    char colore_1, colore_2;
    int scelta;
}tessera;

typedef struct{
    int i_tessera;
    int rotazione;
}configurazione;

tessera *read_tiles(tessera *Tessere, int *n);
configurazione **read_board(configurazione **board, int *R, int *C,tessera *T);
configurazione **inizializza(configurazione ** best_b, int r, int c);
void solution(tessera *Tessere, configurazione **board, configurazione **best_b, int n, int r, int c);
void count_point(configurazione **B,tessera *T ,int r, int c, int *p_r, int *p_c);
void copiasol(int *p_r,int *p_c, int *mp_r, int *mp_c, int r, int c,configurazione **B,configurazione ** best_b);
void stampa_board(configurazione **board, int r, int c,FILE *f,int *maxp_r, int *maxp_c);
void recursive_sol(tessera *T, configurazione **B,int n,int max_r,int max_c, int r, int c,configurazione ** best_b, int *p_r,int *p_c,int *maxp_r, int  *maxp_c);
void free2d(configurazione **b,int r);
int check_tessera(configurazione **B,int r, int c);
int confronto_sol(int *p_r,int *p_c, int *mp_r, int *mp_c, int r, int c);


int main() {
    tessera *Tessere;
    configurazione **board, **best_b;
    int n,R,C;
    Tessere= read_tiles(Tessere, &n);
    board = read_board(board ,&R,&C,Tessere);
    best_b = inizializza(best_b, R,C);
    solution(Tessere,board,best_b,n,R,C);
    free(Tessere);
    free2d(board,R);
    return 0;
}

tessera *read_tiles(tessera *Tessere, int *n){
    int i;
    FILE *f = fopen("tiles.txt","r");
    if(f!=NULL){
        fscanf(f,"%d\n",n);
        Tessere = malloc((*n )* sizeof(tessera));
        for(i=0;i<*n;i++){
            fscanf(f,"%c %d %c %d\n",&Tessere[i].colore_1, &Tessere[i].punti_1,&Tessere[i].colore_2,
                   &Tessere[i].punti_2);
            Tessere[i].scelta=0;
        }
        fclose(f);
        return Tessere;
    }
    else return NULL;
}

configurazione **read_board(configurazione **board, int *R, int *C, tessera *T){
    int i,j;
    FILE *f = fopen("board.txt","r");
    if(f!=NULL){
        fscanf(f,"%d %d\n",R,C);
        board = malloc((*R)*sizeof(configurazione *));
        for(i=0;i<*R;i++){
            board[i] = malloc((*C)*sizeof(configurazione));
            for(j=0;j<*C;j++){
                fscanf(f,"%d/%d\n",&(board[i][j].i_tessera),&(board[i][j].rotazione));
                if(board[i][j].rotazione!=-1) T[board[i][j].i_tessera].scelta=1;
            }
        }
        fclose(f);
        return board;
    }
    else return NULL;
}

configurazione **inizializza(configurazione ** best_b, int r, int c){
    int i,j;
    best_b = malloc(r*sizeof(configurazione *));
    for(i=0;i<r;i++){
        best_b[i]=malloc(c*sizeof(configurazione));
        for(j=0;j<c;j++){
            best_b[i][j].i_tessera=-1;
            best_b[i][j].rotazione=-1;
        }
    }
    return best_b;
}

void solution(tessera *Tessere, configurazione **board, configurazione **best_b, int n, int r, int c){
    int i,R=0,C=0;
    int *p_r, *p_c,*maxp_r,*maxp_c;
    FILE *f;
    f=fopen("soluzione.txt","w+");
    p_r=malloc(r*sizeof(int));
    p_c=malloc(c*sizeof(int));
    maxp_r=calloc(r,sizeof(int));
    maxp_c=calloc(c,sizeof(int));

    while(board[R][C].i_tessera!=-1 && R<r){
        if(C<c) C+=1;
        else{
            C=0;
            R+=1;
        }
    }
    for(i=0;i<n;i++){
        if(!Tessere[i].scelta){
            board[R][C].i_tessera=i;
            board[R][C].rotazione=0;
            Tessere[i].scelta=1;
            recursive_sol(Tessere,board,n,r,c,R,C,best_b,p_r,p_c,maxp_r,maxp_c);
            board[R][C].rotazione=1;
            recursive_sol(Tessere,board,n,r,c,R,C, best_b, p_r,p_c,maxp_r,maxp_c);
            Tessere[i].scelta=0;
        }

    }
    stampa_board(best_b,r,c,f,maxp_r,maxp_c);
    free(best_b);
    free(p_c);
    free(p_r);
    free(maxp_c);
    free(maxp_r);
    fclose(f);
}

void recursive_sol(tessera *T, configurazione **B, int n,int max_r,int max_c, int r, int c,configurazione ** best_b, int *p_r,int *p_c, int *maxp_r, int *maxp_c){
    int i;
    if(c>=max_c){
        c=0;
        r+=1;
    }
    if(r>=max_r || c >=max_c){
        count_point(B,T,max_r,max_c,p_r, p_c);
        if(confronto_sol(p_r,p_c,maxp_r,maxp_c,max_r,max_c)){
            copiasol(p_r,p_c,maxp_r,maxp_c,max_r,max_c,B,best_b);
        }
        return ;
    }
    if(check_tessera(B,r,c)){
        for(i=0;i<n;i++){
            if(!T[i].scelta){
                T[i].scelta=1;
                B[r][c].i_tessera=i;
                B[r][c].rotazione=0;
                recursive_sol(T,B,n,max_r,max_c,r,c+1,best_b,p_r,p_c,maxp_r,maxp_c);
                B[r][c].rotazione=1;
                recursive_sol(T,B,n,max_r,max_c,r,c+1,best_b,p_r,p_c,maxp_r,maxp_c);
                T[i].scelta=0;
                B[r][c].i_tessera=-1;
                B[r][c].rotazione=-1;
            }
        }
    }
    else recursive_sol(T,B,n,max_r,max_c,r,c+1,best_b,p_r,p_c,maxp_r,maxp_c);

}

int check_tessera(configurazione **B,int r, int c){
    if(B[r][c].i_tessera==-1) return 1;
    else return 0;
}

void count_point(configurazione **B,tessera *T, int r, int c, int *p_r, int *p_c){
    int i,j,fine=0;
    for(i=0;i<r;i++){
        fine=0;
        if(B[i][0].rotazione) p_r[i]=T[B[i][0].i_tessera].punti_2;
        else p_r[i]=T[B[i][0].i_tessera].punti_1;
        for(j=1;j<c && !fine;j++){
            if(B[i][j].rotazione){
                if(B[i][j-1].rotazione){
                    if(T[B[i][j].i_tessera].colore_2!=T[B[i][j-1].i_tessera].colore_2) fine=1;
                    else p_r[i]+=T[B[i][j].i_tessera].punti_2;
                }
                else{
                    if(T[B[i][j].i_tessera].colore_2!=T[B[i][j-1].i_tessera].colore_1) fine=1;
                    else p_r[i]+=T[B[i][j].i_tessera].punti_2;
                }
            }
            else{
                if(B[i][j-1].rotazione){
                    if(T[B[i][j].i_tessera].colore_1!=T[B[i][j-1].i_tessera].colore_2) fine=1;
                    else p_r[i]+=T[B[i][j].i_tessera].punti_1;
                }
                else{
                    if(T[B[i][j].i_tessera].colore_1!=T[B[i][j-1].i_tessera].colore_1) fine=1;
                    else p_r[i]+=T[B[i][j].i_tessera].punti_1;
                }
            }
        }
        if(fine) p_r[i]=0;
        }

    for(i=0;i<c;i++){
        fine=0;
        if(B[0][i].rotazione) p_c[i]=T[B[0][i].i_tessera].punti_1;
        else p_c[i]=T[B[0][i].i_tessera].punti_2;
        for(j=1;j<r && !fine;j++){
            if(B[j][i].rotazione){
                if(B[j-1][i].rotazione){
                    if(T[B[j][i].i_tessera].colore_1!=T[B[j-1][i].i_tessera].colore_1) fine=1;
                    else p_c[i]+=T[B[j][i].i_tessera].punti_1;
                }
                else{
                    if(T[B[j][i].i_tessera].colore_1!=T[B[j-1][i].i_tessera].colore_2) fine=1;
                    else p_c[i]+=T[B[j][i].i_tessera].punti_1;
                }
            }
            else{
                if(B[j-1][i].rotazione){
                    if(T[B[j][i].i_tessera].colore_2!=T[B[j-1][i].i_tessera].colore_1) fine=1;
                    else p_c[i]+=T[B[j][i].i_tessera].punti_2;
                }
                else{
                    if(T[B[j][i].i_tessera].colore_2!=T[B[j-1][i].i_tessera].colore_2) fine=1;
                    else p_c[i]+=T[B[j][i].i_tessera].punti_2;
                }
            }
        }
        if(fine) p_c[i]=0;
    }
}

int confronto_sol(int *p_r,int *p_c, int *mp_r, int *mp_c, int r, int c){
    int i;
    int s_att=0, s_max=0;
    for(i=0;i<r;i++){
        s_att+=p_r[i];
        s_max+=mp_r[i];
    }
    for(i=0;i<c;i++){
        s_att+=p_c[i];
        s_max+=mp_c[i];
    }

    if(s_att>s_max) return 1;
    else return 0;
}

void copiasol(int *p_r,int *p_c, int *mp_r, int *mp_c, int r, int c,configurazione **B,configurazione ** best_b){
    int i,j;
    for(i=0;i<r;i++){
        mp_r[i]=p_r[i];
        for(j=0;j<c;j++){
            best_b[i][j].rotazione=B[i][j].rotazione;
            best_b[i][j].i_tessera=B[i][j].i_tessera;
            mp_c[j]=p_c[j];
        }
    }
}

void stampa_board(configurazione **board, int r, int c, FILE *f,int *maxp_r, int *maxp_c){
    int i,j,P_TOT=0;
    fprintf(f,"SOLUZIONE OTTIMALE: \n\n");
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            fprintf(f,"%d / %d\t",(board[i][j].i_tessera),(board[i][j].rotazione));
        }
        fprintf(f," = [%d]\n",maxp_r[i]);
        P_TOT += maxp_r[i];
    }

    fprintf(f,"\n ");
    for(i=0;i<c;i++){
        fprintf(f,"[%d] \t",maxp_c[i]);
        P_TOT+=maxp_c[i];
    }
    fprintf(f,"\n\nPUNTI TOTALI : %d\n",P_TOT);
}

void free2d(configurazione **b, int r){
    int i,j;
    for(i=0;i<r;i++){
        free(b[i]);
    }
    free(b);
}
