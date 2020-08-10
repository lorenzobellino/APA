#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define seq "sequenze.txt"
#define tes "testo.txt"

#define max_parola 25
#define max_s 20

void confronta(FILE *s, char stringa[] );

int main(int argc , char argv[]){

    int n_seq,i;
    FILE *s, *t;
    char sequenza[max_parola +2];
    int ricorrenze[max_s];

    s = fopen(seq, "r");
    t = fopen(tes, "r");
    if(t == NULL || s == NULL){
        printf("errore");
        return 1;
    }

    fscanf(s, "%d", &n_seq);
    for(i=0; i< n_seq; i++){
       fscanf(s, "%s", sequenza);       //per ogni seuqnzza cerco le occorrenze nel file
       confronta(t, sequenza ); 
       rewind(t);                       //mi riporto all'inizio del file
   }
    return 0;
}

void confronta(FILE *t, char stringa[] ){
    char parola[max_parola];
    int i=0,k=0,b=0,find=0,j=0,counter=0;
    int l_parola, l_stringa;

    l_stringa = strlen(stringa);

    printf("la sequenza %s e contenuta in :\n",stringa);

    while(fscanf(t,"%s",parola) != EOF && i<10){   //finche' leggo parole e finche' non ne ho trovate massimo 10
        l_parola=strlen(parola);
        k=0;
        find=0;

        while((k <= l_parola - l_stringa) && (find == 0)){      //scorro i caratteri di una parola fino a lunghezza parola - lunghezza stringa da cercare
            j=k;
            
            while(tolower(parola[j])== tolower(stringa[b]) && b < l_stringa){       //confronto carattere per carattere
                b++;
                if(b == l_stringa){
                    printf("%s (parola in posizione %d nel testo)\n", parola,counter+1);
                    find=1; 
                    i++;
                } 
                j++; 
            }
            b=0;
            k++;
        }
        counter++;
    }
    printf("\n");
    if(i==0){
        printf("nessuna parola del testo\n");
    }

}


