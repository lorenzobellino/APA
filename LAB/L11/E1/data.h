//
//  data.h
//  lab11
//
//  Created by Paolo Cambria on 19/01/2019.
//  Copyright © 2019 BitleApps. All rights reserved.
//

#ifndef data_h
#define data_h

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

//quasi adt per gestire la data 
typedef struct date{
    int day;
    int month;
    int year;
} date;
int compareDate(date mData1, date mData2);
int dateCompare(date mData1, date mData2);
#endif /* data_h */
