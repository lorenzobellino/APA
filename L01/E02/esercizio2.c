#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define plaintext "plaintext.txt"
#define dictionary "dizionario.txt"
#define cypher "cifrato.txt"
#define MAX_L 200
#define MAX_C 7
#define MAX_N 30

typedef struct{
	char code[MAX_C + 1];
	char word[MAX_L + 1];
	int len;
} code;

void sostituisci(char codice[], int index_start, char stringa[], int n_characters, char parola[], FILE *h, int *trovato);

void confronta(char stringa[], code all[], int max_code, FILE *h);

int main(int argc, char argv[]){

	FILE *p, *d, *c;
	code dizionario[MAX_N];
	int sostituzioni, i;
	char new_line[MAX_L + 2];

	c = fopen(cypher, "w");
	d = fopen(dictionary, "r");
	p = fopen(plaintext, "r");

	if (c == NULL || d == NULL || p == NULL){
		printf("errore");
		return -1;
	}

	fscanf(d, "%d", &sostituzioni);

	for (i = 0; i < sostituzioni; i++){
		fscanf(d, "%s %s", dizionario[i].code, dizionario[i].word);
		dizionario[i].len = strlen(dizionario[i].word);
	}

	fclose(d);

	while (fgets(new_line, MAX_L, p) != NULL){
		confronta(new_line, dizionario, sostituzioni, c);
	}

	fclose(p);
	fclose(c);

	return 0;
}

void confronta(char line[], code dizionario[], int n, FILE *c){

	int i, j, find = 0;

	for (i = 0; i < n; i++){
		for (j = 0; j <= (strlen(line) - dizionario[i].len); j++){

			if (strncmp(dizionario[i].word, line + j, dizionario[i].len) == 0){   // compara n caratteri della riga (n= lunghezza parola nel dizionario
																				  // con ogni parola del dizionario scandendo per ogni indice di partenza possibille
				sostituisci(dizionario[i].code, j, line, dizionario[i].len, dizionario[i].word, c, &find); //sostituisci la parola nel file ricodificato
			}
		}
	}

	if (find == 1)
		fprintf(c, "%s\n", line); //se lultimo carattere della riga e' stato modificato stampa linea + '\n'
	else
		fprintf(c, "%s", line); //altrimenti stampa solo la linea
}

void sostituisci(char codice[], int index_start, char line[], int n_characters, char sostituzione[], FILE *c, int *find){

	char sub_string1[MAX_L] = "";
	char sub_string2[MAX_L] = "";

	if (index_start == 0){														//SE I CARATTERI DA SOSTITUIRE PARTONO DALLA POSIZIONE ZERO
		strcpy(sub_string1, codice);											//copio il codice in una stringa di buffer
		strncat(sub_string1, line + n_characters, strlen(line) - n_characters); //concateno il buffer e la liea (meno i caratteri da sostituire)
		strcpy(line, sub_string1);												// copio la stringa generata nellla linea di partenza
	}
	else if (index_start == strlen(line) - n_characters - 1){		 //SE I CARATTERI DA SOSTITUIRE SONO GLI ULTIMI DELLA LINEA
		strncpy(sub_string1, line, strlen(line) - n_characters - 1); //copio la linea (fino al primo dei caratteri da sostituire in un buffer
		strcat(sub_string1, codice);								 //concateno la stringa generata con il codice sostitutivo
		strcpy(line, sub_string1);									 //copio la stringa finale sulla stringa di partenza
		*find = 1;													 //set find =1 come flag per stampare il carattere \n alla fine della linea
	}
	else{														  //SE I CARATTERI DA SOSTITUIRE SONO IN MEZZO ALLA STRINGA
		strncpy(sub_string1, line, index_start);				  //copio i caratteri della stringa in un buffer fino al primo carattere da sostituire
		strcat(sub_string1, codice);							  //concateno il buffer con il codice
		strcpy(sub_string2, line + (index_start + n_characters)); //copio la stringa ottenuta in un buffer
		strcat(sub_string1, sub_string2);						  //concaten il buffer con il resto della stringa iniziale
		strcpy(line, sub_string1);								  //copio tutto nella stringa iniziale
	}
}
