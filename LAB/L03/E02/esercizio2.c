#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

void int_to_bin(int n, char bin[]);
void codifica(unsigned char *v, int size, int BIG);
void format(char bin[], int size);

int main(int argc, char* argv[]){

    float af;
    double ad;
    long double ald;
    int big_endian, a;
    unsigned int c = 1;
    unsigned char *p = (unsigned char *)&c;

    printf("FLOAT :\n");
    scanf("%f", &af);
    printf("\nDOUBLE :\n");
    scanf("%lf", &ad);
    printf("\nLONG DOUBLE :\n");
    scanf("%Lf", &ald);
    printf("\n");

    if (p[0] == 1)          //se il primo bit puntato e' 1 allora Little endian
        big_endian = 0;
    else
        big_endian = 1;

    printf("tipo |FLOAT|\ndimensione in byte : |%d|\ndimensione in bit : |%d|\n\n", sizeof(af), sizeof(af) * 8);
    codifica((void *)&af, sizeof(af), big_endian);
    printf("tipo |DOUBLE|\ndimensione in byte : |%d|\ndimensione in bit : |%d|\n\n", sizeof(ad), sizeof(ad) * 8);
    codifica((void *)&ad, sizeof(ad), big_endian);
    printf("tipo |LONG DOUBLE|\ndimensione in byte : |%d|\ndimensione in bit : |%d|\n", sizeof(long double), sizeof(long double) * 8);
    codifica((void *)&ald, sizeof(long double), big_endian);

    return 0;
}

void codifica(unsigned char *v, int size, int BIG){
    int i;
    char binary[200] = "\0";
    
    if(BIG){
        for(i=0;i<size;i++){
            
            int_to_bin(v[i],binary);        //v[i]= intero di un byte puntato da *v
        }
    }
    else{
       for (i = size - 1; i >= 0; i--){
           
        int_to_bin(v[i], binary);
    } 
    }
    
    printf("%s\n\n", binary);
    format(binary, size);
    printf("\n");
}

void int_to_bin(int n, char bin[]){
    int i, power;
    for (i = 7; i >= 0; i--)
    {
        power = pow(2, i);
        if (n < power)
            strcat(bin, "0");
        else
        {
            strcat(bin, "1");
            n = n - power;
        }
    }
}

void format(char bin[], int size){
    int i;
    switch (size)
    {
    case 4:
        printf("1 bit di segno : %c\n", bin[0]);
        printf("8 bit di esponente: ");
        for (i = 1; i < 9; i++)
        {
            printf("%c ", bin[i]);
        }
        printf("\n");
        printf("23 bit di mantissa :");
        for (i = 9; i < 32; i++)
        {
            printf("%c ", bin[i]);
        }
        printf("\n");
        break;
    case 8:
        printf("1 bit di segno : %c\n", bin[0]);
        printf("11 bit di esponente: ");
        for (i = 1; i < 12; i++)
        {
            printf("%c ", bin[i]);
        }
        printf("\n");
        printf("52 bit di mantissa :");
        for (i = 12; i < 64; i++)
        {
            printf("%c ", bin[i]);
        }
        printf("\n");
        break;
    case 12:
        printf("1 bit di segno : %c\n", bin[0]);
        printf("15 bit di esponente: ");
        for (i = 1; i < 16; i++)
        {
            printf("%c ", bin[i]);
        }
        printf("\n");
        printf("80 bit di mantissa :");
        for (i = 16; i < 96; i++)
        {
            printf("%c ", bin[i]);
        }
        printf("\n");
        break;
    case 16:
        printf("1 bit di segno : %c\n", bin[0]);
        printf("15 bit di esponente: ");
        for (i = 1; i < 16; i++)
        {
            printf("%c ", bin[i]);
        }
        printf("\n");
        printf("113 bit di mantissa :");
        for (i = 16; i < 128; i++)
        {
            printf("%c ", bin[i]);
        }
        printf("\n");
        break;
    default:
        break;
    }
}
