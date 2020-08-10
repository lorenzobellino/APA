

#include "quote.h"
#include "titles.h"

struct mQuote{
    link root; //radice
    link z;
    float max;
    float min;
};

static int mMin=0,mMax=0;

//nuovo nodo per la quotazione singola
link newNodoQuotazione(float mQuota, date mData, link z){
    link mDailyQuot = malloc(sizeof(*mDailyQuot));
    mDailyQuot->left = z;
    mDailyQuot->right = z;
    mDailyQuot->mQuotazione = mQuota;
    mDailyQuot->mDate = mData;
    mDailyQuot->mHeight = 1;
    return mDailyQuot;
}

//inizializzo il BST
mQuote initializeBST(link x, link z ){
    mQuote mQuoteCollection;
    mQuoteCollection = malloc(sizeof(*mQuoteCollection));
    mQuoteCollection->root = x;
    //quotazione massima e minima sono uguali perché ho un solo elemento
    mQuoteCollection->max = x->mQuotazione;
    mQuoteCollection->min = x->mQuotazione;
    mQuoteCollection->z = z;
    return mQuoteCollection;
}

//aggiungo una quota all'albero ricorsivamente
link addQuote(mQuote mQuoteCollection, link x, link h, link z){
    //aggiorno massimo e minimo
    //se la data dell'elemento da aggiungere è maggiore o uguale alla radice
    //non sarà uguale perché passo la collezione e ho strutturato bene la funzione
    if (h == z){
        if (x->mQuotazione > mQuoteCollection->max){
            mQuoteCollection->max = x->mQuotazione;
        }
        if(x->mQuotazione < mQuoteCollection->min){
            mQuoteCollection->min = x->mQuotazione;
        }
        return x;
    }
    h->mHeight++;
    
    if(dateCompare(x->mDate,h->mDate)>0){
        h->right = addQuote(mQuoteCollection, x, h->right, z);
    } else {
        h->left = addQuote(mQuoteCollection, x, h->left, z);
    }
    
    return h;
}



mQuote CalcoloQuotaGiornaliera(mTransactions Transactions, int n){
    int i,j,r=n,mNumber;
    mNumber = 0;
    float mValue = 0, mQuota = 0;
    //nodo fittizio e nodo quota giornaliera
    link z;
    z = malloc(sizeof(*z));
    z = initializeZ(z);
    link mDailyQuot;
    mQuote mQuoteCollection = NULL;
    
    //calcolo quota (r = numero di date da visitare)
    for (i=0;i<n && r>0;i++){
        mValue = 0;
        mNumber = 0;
        //verifico di non aver già calcolato la quota per quella data
        if (Transactions[i].mark == 0){
            //parto più avanti se già ho visto ciò che c'era prima
            for(j=i;j<n && r>0;j++){
                if (Transactions[j].mark == 0){
                    //decido se prendere la data
                    if (compareDate(Transactions[i].mDate, Transactions[j].mDate)){
                        //prendo la data e memorizzo i dati necessari per calcolare la quota
                        Transactions[j].mark = 1;
                        r--;
                        mValue = mValue + (Transactions[j].mValue * Transactions[j].mAmount);
                        mNumber = mNumber + Transactions[j].mAmount;
                    }
                }
            }
            //calcolo la quota
            mQuota = mValue/mNumber;
            //creo un nuovo nodo quotazione
            mDailyQuot = newNodoQuotazione(mQuota, Transactions[i].mDate,z);
            //lo aggiungo alla collezione di quotazioni
            if (mQuoteCollection == NULL){
                mQuoteCollection = initializeBST(mDailyQuot,z);
            }else{
               mQuoteCollection->root = addQuote(mQuoteCollection,mDailyQuot,mQuoteCollection->root,z);
            }
        }
    }
    return mQuoteCollection;
}

link fsupport(date mData, mQuote mQuota){
    if (mQuota->root == mQuota->z){
        printf("Non esiste.\n");
        return mQuota->z;
    }
    link x = searchQuoteByData(mData, mQuota->root, mQuota->z);
    if(x != mQuota->z){
        printf("La quotazione cercata è :%f.\n",x->mQuotazione);
    }
    return x;
}
// h è il nodo alla radice del BST titolo 
link searchQuoteByData(date mData, link h, link z){
    //se la data è > della testa vado a destra
    if (dateCompare(h->mDate,mData) > 0){
        if ( h != z ) {
            h = h->right;
            searchQuoteByData(mData, h,z);
        } else {
            //se sono arrivato alla fine e non ho trovato una data = significa che non c'è  la data
            printf("Data non trovata nel BST.\n");
        }
    } else if (dateCompare(h->mDate, mData) < 0){
        if ( h != z ) {
            h = h->left;
            searchQuoteByData(mData, h,z);
        } else {
            printf("Data non trovata nel BST.\n");
        }
    } else {
        return h;
    }
    
    return h;
}



//stampa la massima e la minima quota del BST
void maxminQuoteEntireBST(mQuote mCollBST){
    printf("max: %f, min: %f \n",mCollBST->max,mCollBST->min);
};

float mMaxQuote, mMinQuote;

//funzione di supporto per mandargli la root
void startSearchQuote(mQuote mCollQuote, date mData1, date mData2){
    //inizializzo quota max e min (stavolta globali..)
    mMaxQuote =0; mMinQuote = 0;
    
    searchQuoteIntervalR(mCollQuote->root, mCollQuote->z, mData1, mData2);
    printf("Valore minimo nell'intervallo selezionato: %f.\n Valore massimo nell'intervallo selezionato : %f.\n",mMinQuote,mMaxQuote);
    
    
}

//funzione ricorsiva che stampa le date comprese nell'intervallo
void searchQuoteIntervalR(link h, link z, date mData1, date mData2){  
    //se la mia data considerata a sinistra     // se la mia data considerata a sinistra
    //è >= della più piccola                    è <= della più grande
    if (h->left != z){
    if ((dateCompare(h->left->mDate, mData1))>=0 &&  (dateCompare(h->left->mDate, mData2)<=0)){
        searchQuoteIntervalR(h->left, z, mData1, mData2);
        if(h->mQuotazione > mMaxQuote){
            mMaxQuote = h->mQuotazione;
        }
        if(h->mQuotazione < mMinQuote || mMinQuote == 0){
            mMinQuote = h->mQuotazione;
        }
    }
    }
    
    //se la mia data considerata a destra     // se la mia data considerata a destra
    //è >= della più piccola                    è <= della più grande
    if (h->right != z){
    if ((dateCompare(h->right->mDate, mData1))>=0 &&  (dateCompare(h->right->mDate, mData2)<=0)){
        searchQuoteIntervalR(h->right, z, mData1, mData2);
        if(h->mQuotazione > mMaxQuote){
            mMaxQuote = h->mQuotazione;
        }
        if(h->mQuotazione < mMinQuote || mMinQuote == 0){
            mMinQuote = h->mQuotazione;
        }
    }
    }
}

link initializeZ(link z){
    z->left = NULL;
    z->right = NULL;
    z->mHeight = 0;
    z->mQuotazione = -1;
    z->mDate.day = 0;
    z->mDate.month =0;
    z->mDate.year =0;
    return z;
}


void balanceBST(mQuote mQuota){

    calcolaBalanceMinMax(mQuota->root, mQuota->z, 0);
    printf("%d,%d \n",mMin,mMax);
    //se S è maggiore di 1 inizia il bilanciamento
    int S = mMax/mMin;
    if(S>1){
    //la mia chiave mediana la calcolo a partire dall'altezza dell'albero
    int mPivot = mQuota->root->mHeight;
    mPivot = (mPivot+1)/2;
    balanceR(mQuota->root, mPivot);
    printf("Albero bilanciato con successo. \n");
    } else {
        printf("L'albero è già bilanciato. \n");
    }
    
}

//funzione più interessante, ordino tutto rispetto al pivot (chiave mediana)
link balanceR(link h, int r){
    //guardo l'altezza di ciò che sta a sinistra, se è il nodo z sarà = 0
    int t = h->left->mHeight;
    if (t > r) {
        h->left = balanceR(h->left, r);
        h = rotR(h);
    }
    //se ho il nodo z o qualcosa di < scendo in questa condizione
    if (t < r) {
        h->right = balanceR(h->right, r-t-1);
        h = rotL(h);
    }
    return h;
}

//calcola equilibrio min e max
int calcolaBalanceMinMax(link h, link z, int mCount){
    //condizione di terminazione
    if(h->right == NULL && h->left == NULL){
        if(mMax == 0){
            mMax = mCount;
        }
        if (mMin==0){
            mMin = mCount;
        }
        if(mCount > mMax){
            mMax = mCount;
        }
        if (mCount < mMin){
            mMin = mCount;
        }
    }
    if(h->left != NULL){
        mCount++;
       calcolaBalanceMinMax(h->left, z,mCount);
    }
    if(h->right != NULL){
        mCount++;
        calcolaBalanceMinMax(h->right, z, mCount);
    }
    
    return mCount;
    
}

//se volessi optare per qualcosa di "greedy"
int calcolaBalanceMin(link h,link z, int mRic){
   //condizione di terminazione, entrambi = 0
    if(h->left == z && h->right == z){
        return mRic;
    }
    //se i figli a sx sono < di quelli a dx
    if (h->left->mHeight < h->right->mHeight){
        mRic++;
        calcolaBalanceMin(h->left, z,mRic);
    } else{
        mRic++;
        calcolaBalanceMin(h->right, z,mRic);
    }
    
    return mRic;
}

int calcolaBalanceMax(link h,link z, int mRic){
    //condizione di terminazione, entrambi = 0
    if(h->left == z && h->right == z){
        return mRic;
    }
    //se i figli a sx sono > di quelli a dx
    if (h->left->mHeight > h->right->mHeight){
        mRic++;
        calcolaBalanceMin(h->left, z,mRic);
    } else{
        mRic++;
        calcolaBalanceMin(h->right, z,mRic);
    }
    
    return mRic;
}
//rotazione a sinistra
link rotL(link h){
    link x = h->right;
    h->right = x->left;
    x->left = h;
    x->mHeight = h ->mHeight;
    h->mHeight = h->left->mHeight  + h->right->mHeight +1;
    return x;
}
//rotazione a destra
link rotR(link h){
    link x = h->left;
    h->left = x->right;
    x->right = h;
    h->left = x->right;
    x->mHeight = h->mHeight;
    h->mHeight = h->right->mHeight + h->left->mHeight +1;
    return x;
}

