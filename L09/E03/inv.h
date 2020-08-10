

#ifndef ESERCIZIO3_INV_H
#define ESERCIZIO3_INV_H
#define maxs 50

typedef struct stat_t{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stats;

typedef struct inv_t{
    char nome[maxs+1];
    char tipo[maxs+1];
    stats stat;
}Item;

void get_stats(Item item, int *hp,int *mp,int *atk,int *def, int *mag,int *spr);
int max(int a,int b);

#endif //ESERCIZIO3_INV_H
