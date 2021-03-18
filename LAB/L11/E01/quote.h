
#ifndef quote_h
#define quote_h

#include <stdio.h>
#include "titles.h"

typedef struct quotazioneSingola quotazioneSingola, *link;
struct quotazioneSingola{
    date mDate;
    float mQuotazione;
    int mHeight;
    link left;
    link right;
    
};
typedef struct mQuote *mQuote;

link newNodoQuotazione(float mQuota, date mData, link z);
mQuote initializeBST(link x, link z );
link addQuote(mQuote mQuoteCollection, link x, link h, link z);
link searchQuoteByData (date mData, link h, link z);
mQuote CalcoloQuotaGiornaliera(mTransactions Transactions, int n);
link fsupport(date mData, mQuote mQuota);
void maxminQuoteEntireBST(mQuote mCollBST);
void searchQuoteIntervalR(link h, link z, date mData1, date mData2);
void startSearchQuote(mQuote mCollQuote, date mData1, date mData2);
link initializeZ(link z);
link rotL(link h);
link rotR(link h);
link balanceR(link h, int r);
int calcolaBalanceMinMax(link h, link z, int mCount);
void balanceBST(mQuote mQuota);

#endif /* quote_h */
