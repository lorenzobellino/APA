
#include <stdio.h>
#include "quote.h"
#define M 1000
#define T 20

int main(int argc, const char * argv[]) {
    coll_titles mTitles,mTargetTitle;
    char mTitleName[N];
    int mNumber,mMenu = 1;
    while(mMenu){
    printf("Seleziona un'operazione: \n");
    printf("1 acquisizione del contenuto di un file contenente un insieme di transazioni.\n");
    printf("2 Ricerca di un titolo azionario.\n");
    printf("3 ricerca, dato un titolo precedentemente selezionato, della sua quotazione in una certa data.\n");
    printf("4 ricerca, dato un titolo precedentemente selezionato, della sua quotazione minima e massima in un certo intervallo di date.\n");
    printf("5 ricerca, dato un titolo precedentemente selezionato, della quotazione minima e massima lungo tutto il periodo registrato.\n");
    printf("6 dato un titolo precedentemente selezionato, bilanciamento dell'albero di quotazioni se il rapporto tra il cammino più lungo e più corto nell'albero supera una certa soglia S.");
    scanf("%d",&mNumber);

    switch(mNumber){
        case 1:
            mTitles = acquisisciFile();
            break;
        case 2:
            printf("Inserisci il titolo da ricercare.\n");
            scanf("%s",mTitleName);
            stampaTitolo(ricercaTitolo(mTitles, mTitleName));
            mTargetTitle = ricercaTitolo(mTitles, mTitleName);
            break;
        case 3:
            printf("Inserisci il titolo da ricercare.\n");
            scanf("%s",mTitleName);
            if (mTargetTitle != NULL){
                printf("Inserisci una data in formato gg/mm//yyyy.\n");
                date mData;
                scanf("%d/%d/%d",&mData.day,&mData.month,&mData.year);
                //passo la data
                searchQBDSupport(mTargetTitle,mData);
            }
            break;
        case 4:
            if (mTargetTitle != NULL){
                printf("Inserisci una data in formato yyyy/mm/dd.\n");
                date mData1;
                scanf("%d/%d/%d",&mData1.year,&mData1.month,&mData1.day);

                printf("Inserisci una data in formato yyyy/mm/dd \n");
                date mData2;
                scanf("%d/%d/%d",&mData2.year,&mData2.month,&mData2.day);
                searchQuoteInterval(mTargetTitle,mData1,mData2);

            }
            break;
        case 5:
            if (mTargetTitle != NULL){
                maxandminquoteBST(mTargetTitle);
            }
            break;
        case 6:
            if (mTargetTitle != NULL){
                balanceBSTPrep(mTargetTitle);
            }
            break;
        case 7:
            mMenu=0;
            break;
        default:
            printf("numero non valido\n");
            break;
    }
    return 0;
}

    
