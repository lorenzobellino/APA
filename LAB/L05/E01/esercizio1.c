#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILENAME "brani.txt"
#define max_l 256

typedef struct{
    char **brani;
}songs;

int find_my_playlist(int pos, songs **friend, char **sol, int *t, int a, int caunt,FILE *g);
void free_brani(songs **friend,int n, int titoli[], char **sol);

int main(int argc, char *argv[]){

    int amici,*titoli,i,j;
    songs **friend;
    char **sol,buff[max_l];
    FILE *f,*g;
    f= fopen("brani.txt", "r");
    if(f==NULL) return -1;

    fscanf(f,"%d\n",&amici);
    friend = (songs **) malloc(amici*sizeof(songs*));
    sol = malloc(amici*sizeof(char*));
    titoli = malloc(amici*sizeof(int));
    for(i=0;i<amici;i++){
        fscanf(f,"%d\n",&titoli[i]);
        friend[i] = (songs*) malloc(titoli[i]*sizeof(songs));
        (*friend[i]).brani = malloc(titoli[i]*sizeof(char**)); 
        sol[i]= malloc(max_l*sizeof(char));
        for(j=0;j<titoli[i];j++){
            fscanf(f,"%s\n",buff);
            friend[i]->brani[j] = malloc((strlen(buff)+1*sizeof(char)));
            strcpy(friend[i]->brani[j], buff);
        }
    }
    fclose(f);
   
    g= fopen("solution.txt", "w");
    if(g==NULL) return -1;
    find_my_playlist(0,friend,sol,titoli,amici,0,g);
    fclose(g);
    free_brani(friend,amici,titoli,sol);
    return 0;
}

int find_my_playlist(int pos, songs **friend, char **sol, int *t, int n, int count, FILE *g){
    int i;

    if (pos >= n) {
        for (i = 0; i < n; i++) fprintf(g,"%s ", sol[i]);
        fprintf(g,"\n");
        return count+1;
        } 
    for (i = 0; i < t[pos]; i++) { 
        strcpy(sol[pos], friend[pos]->brani[i]); 
        count = find_my_playlist(pos+1, friend, sol, t,n, count,g);
        }
    return count;
}

void free_brani(songs **friend,int n, int *titoli, char **sol){
    int i,j;

    for(i=0;i<n;i++){
        for(j=0;j<titoli[i];j++){
            free(friend[i]->brani[j]);
        }
        free(friend[i]->brani);
        free(friend[i]);
        free(sol[i]);
    }
    free(friend);
    free(sol);
}