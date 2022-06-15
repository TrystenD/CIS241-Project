#ifndef _MONTHLY_H
#define _MONTHLY_H

#define MONTHS 12
#define DATAPOINTS 2

void monthly(char *dates[],int ratios[],int lines,int avgs[MONTHS]);
int avgOneMonth(int month, int data[][DATAPOINTS], int lines);

#endif  //_MONTHLY_H