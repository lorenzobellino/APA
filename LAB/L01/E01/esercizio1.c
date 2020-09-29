#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define campionato "campionato.txt"
#define n_max 20
#define m_max 20

void finale(int tabellone[][m_max], int final_score[], int max_r, int max_c);

int somma(int tot_punti[], int j);

void find_max(int tot_punti[], int max_r);

int main(int argc, char *argv[]){

	FILE *c;
	int i = 0, j = 0;
	char score;
	c = fopen(campionato, "r");
	int tabellone[n_max][m_max];
	int final_score[m_max];

	if (c == NULL){
		printf("errore");
		return -1;
	}

	//lettura carattere per carattere fino ad EOF
	//per caricare i dati su una matrice "tabellone"
	do{
		score = fgetc(c);
		if (feof(c))	break;

		else{
			if (score != '\n'){
				tabellone[i][j] = score - '0';
				j++;
			}
			else{
				i++;
				j = 0;
			}
		}
	} while (1);

	fclose(c);

	finale(tabellone, final_score, i, j);

	return 0;
}

void finale(int tabellone[][m_max], int final_score[], int max_r, int max_c){
	int i = 0,j=0;
	for(i=0;i<max_r;i++){
		final_score[i]=0;
	}
	
	for (i = 0; i < max_c; i++){
		for(j=0;j<max_r;j++){
			final_score[j] += tabellone[j][i];
		}
		printf("gionata %d :\n",i+1);
		find_max(final_score, max_r);
	}

	
}

int somma(int tot_punti[], int j){
	int sum = 0, i;
	for (i = 0; i <= j; i++){
		sum = sum + tot_punti[i];
	}
	return sum;
}

//ricerca sequenziale del massimo
void find_max(int tot_punti[], int max_r){
	int max = tot_punti[0];
	int i_max = 0, i;
	for (i = 1; i < max_r; i++){
		if (tot_punti[i] > max){
			max = tot_punti[i];
			i_max = i;
		}
	}
	printf("vittoria per la squadra in posizione: || %d || \ncon un totale di: || %d || punti\n", i_max + 1, max);
}
