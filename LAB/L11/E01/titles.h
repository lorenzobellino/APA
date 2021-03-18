
#ifndef titles_h
#define titles_h
#define N 20
#define M 1000
#include <stdio.h>
#include "data.h"

typedef struct transaction{
    date mDate;
    float mValue;
    int mAmount;
    int mark;
} transaction, *mTransactions;
typedef struct title title;
typedef struct coll_titles *coll_titles;

coll_titles acquisisciFile();
coll_titles ricercaTitolo(coll_titles mHeadTitle, char mTitleName[]);
//mQuote *collToPointer(coll_titles mTargetTitle);
coll_titles insertOrd(coll_titles mColHead,title mCollToInsert);
float calcolaQuotazione(title mTitolo, date mData);
void searchQBDSupport(coll_titles mTargetTitle,date mData);
void stampaTitolo(coll_titles mTitle);
void maxandminquoteBST(coll_titles mTitle);
void searchQuoteInterval(coll_titles mTitle, date mData1, date mData2);
void balanceBSTPrep(coll_titles mTitle);
#endif /* titles_h */
