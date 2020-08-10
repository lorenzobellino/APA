
#include "titles.h"
#include "quote.h"
#include <string.h>

struct title{
    char mTitle[N];
    int mTransAmount;
    mTransactions Transactions;
};

struct coll_titles{
    title singleTitle;
    mQuote mQuotazioni;
    coll_titles next;
};

coll_titles newNodoTitolo(title mVal, coll_titles mTitles){
    coll_titles mTitle = malloc(sizeof(*mTitle));
    //copio i dati del singolo titolo all'interno del nuovo nodo della collezione
    mTitle->singleTitle = mVal;
    //genero quotazione giornaliera
    mTitle->mQuotazioni = CalcoloQuotaGiornaliera(mVal.Transactions,mVal.mTransAmount);
    mTitle->next = mTitles;
    return mTitle;
}

coll_titles acquisisciFile(){
    char mTitle[N], mTime[N],mFilein[20];
    title Titolo;
    int mNumberTransactions,i,j;
    printf("Inserisci la path del file");
    scanf("%s",mFilein);
    FILE *fp;
    fp = fopen(mFilein,"r");
    if (fp == NULL){
        printf("Errore durante l'apertura del file.\n");
        return NULL;
    }
    //prima acquisizione
    //acquisisco il titolo ed il numero di transazioni
    fscanf(fp,"%s %d", mTitle,&mNumberTransactions);
    printf("%s %d \n",mTitle,mNumberTransactions);
    strcpy(Titolo.mTitle, mTitle);
    Titolo.mTransAmount = mNumberTransactions;
    //alloco la memoria per il numero di transazioni
    Titolo.Transactions = (transaction *)malloc(mNumberTransactions*sizeof(transaction));
    Titolo.Transactions[0].mark = 0;

    for (i=0;i<mNumberTransactions;i++){
        fscanf(fp,"%d/%d/%d %s %f %d", &Titolo.Transactions[i].mDate.year,&Titolo.Transactions[i].mDate.month,&Titolo.Transactions[i].mDate.day,mTime, &Titolo.Transactions[i].mValue,&Titolo.Transactions[i].mAmount);
        printf("%d/%d/%d %s %f %d \n",(Titolo).Transactions[i].mDate.year,(Titolo).Transactions[i].mDate.month,(Titolo).Transactions[i].mDate.day,mTime, Titolo.Transactions[i].mValue,Titolo.Transactions[i].mAmount);
    }
 
    //trovo il numero di quotazioni
    for (i=1;i<mNumberTransactions;i++){
        //posso fare questo controllo perché le date sono ordinate, altrimenti altra funzione di search oppure sort + search...
        if (Titolo.Transactions[i].mDate.day != Titolo.Transactions[i-1].mDate.day && Titolo.Transactions[i].mDate.month != Titolo.Transactions[i-1].mDate.month && Titolo.Transactions[i].mDate.year != Titolo.Transactions[i-1].mDate.year){
            Titolo.Transactions[0].mark = 0;
        }
    }
    //alloco spazio per farci entrare le mie quote
   
    
    //inizializzo con nodo next->null
    coll_titles mCollHead =  insertOrd(NULL, Titolo) ;// salvo la testa
        free(Titolo.Transactions);
    
    while( fscanf(fp,"%s %d", mTitle,&mNumberTransactions) == 2){
        //fscanf(fp,"%s %d", mTitle,&mNumberTransactions);
        printf("%s %d \n",mTitle,mNumberTransactions);
        //titolo della serie di transazioni
        strcpy(Titolo.mTitle, mTitle);
        Titolo.mTransAmount = mNumberTransactions;
        Titolo.Transactions[0].mark = 0;
        //alloco la memoria per il numero di transazioni
        Titolo.Transactions = (transaction *)malloc(mNumberTransactions*sizeof(transaction));
        //impacchetto la mia transazine
        
        for (i=0;i<mNumberTransactions;i++){
            fscanf(fp,"%d/%d/%d %s %f %d", &Titolo.Transactions[i].mDate.year,&Titolo.Transactions[i].mDate.month,&Titolo.Transactions[i].mDate.day,mTime, &Titolo.Transactions[i].mValue,&Titolo.Transactions[i].mAmount);
            printf("%d/%d/%d %s %f %d \n",(Titolo).Transactions[i].mDate.year,(Titolo).Transactions[i].mDate.month,(Titolo).Transactions[i].mDate.day,mTime, Titolo.Transactions[i].mValue,Titolo.Transactions[i].mAmount);
        }
        
        //trovo il numero di quotazioni
        for (i=1;i<mNumberTransactions;i++){
            //posso fare questo controllo perché le date sono ordinate, altrimenti altra funzione di search oppure sort + search...
            if (Titolo.Transactions[i].mDate.day != Titolo.Transactions[i-1].mDate.day && Titolo.Transactions[i].mDate.month != Titolo.Transactions[i-1].mDate.month && Titolo.Transactions[i].mDate.year != Titolo.Transactions[i-1].mDate.year){
                Titolo.Transactions[0].mark = 0;
            }
        }
        
        
    mCollHead = insertOrd(mCollHead, Titolo);
     //   mCollHead = mCollTitles; // salvo la testa
        free(Titolo.Transactions);

    }
    coll_titles x;
    printf("Stampa in ordine dei titoli:\n");
    for(x = mCollHead;x!= NULL; x =x->next){
        printf("%s \n",x->singleTitle.mTitle);
    }
    return mCollHead;
}

coll_titles insertOrd(coll_titles mCollHead,title mTitolo){
    coll_titles x,p;
    x = malloc(sizeof(*x));
    //se la testa è nulla creo un nuovo nodo che diventa la mia testa
    if (mCollHead == NULL){
        return newNodoTitolo(mTitolo,NULL);
    }
    //se in ordine alfabetico mTitle precede la testa, la vecchia testa diventa next della nuova testa
    if(strcmp(mTitolo.mTitle,mCollHead->singleTitle.mTitle)<0){
        x = newNodoTitolo(mTitolo, mCollHead);
        mCollHead = x;
    } else {
        //altrimenti vado avanti fino ad inserire in mezzo alla lista
        for( p=x, x=mCollHead; x != NULL &&  (strcmp(mTitolo.mTitle,x->singleTitle.mTitle)>0) ;p=x,x=x->next);
        p->next = newNodoTitolo(mTitolo, x);
    }
    
    return mCollHead;
}
//funzione che accetta come parametri la testa della collezione e il nome del titolo
coll_titles ricercaTitolo(coll_titles mHeadTitle, char mTitleName[]){
    coll_titles x;
    //giro la lista e comparo la stringa
    for(x=mHeadTitle; x != NULL; x = x->next){
        if (strcmp(x->singleTitle.mTitle,mTitleName) == 0){
        return x;
        }
    }
    return NULL;
}


void searchQBDSupport(coll_titles mTargetTitle,date mData){
    // passo data e collezione di titoli
    fsupport(mData, mTargetTitle->mQuotazioni);
}


void stampaTitolo(coll_titles mTitle){
    if (mTitle != NULL){
        printf("%s Trovato.\n",mTitle->singleTitle.mTitle);
    } else {
        printf("Titolo non trovato. \n");
    }
}
void balanceBSTPrep(coll_titles mTitle){
    balanceBST(mTitle->mQuotazioni);
}
void maxandminquoteBST(coll_titles mTitle){
    maxminQuoteEntireBST(mTitle->mQuotazioni);
}

void searchQuoteInterval(coll_titles mTitle, date mData1, date mData2){
    startSearchQuote(mTitle->mQuotazioni,mData1,mData2);
}
