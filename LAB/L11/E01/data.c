

#include "data.h"

int compareDate(date mData1, date mData2){
    if (mData1.day == mData2.day && mData1.month == mData2.month && mData1.year == mData2.year){
        return 1;
    }
    return 0;
}


//funzione di comparazione poco elegante ma molto utile
int dateCompare(date mData1, date mData2){
    //data 1 maggiore di data 2
    if (mData1.year > mData2.year){
        return 1;
    }
    else if(mData1.year == mData2.year){
        if (mData1.month > mData2.month){
            return 1;
        } else if(mData1.month == mData2.month){
            if (mData1.day == mData2.day){
                return 0;
            } else if ( mData1.day > mData2.day) {
                return 1;
            } else {
                return -1;
            }
        } else{
            return -1;
        }
    }else {
        return -1;
    }
}
