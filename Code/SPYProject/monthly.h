#ifndef _MONTHLY_H
#define _MONTHLY_H

#define MONTHS 12
#define DATAPOINTS 2

void monthly(char *dates[], float ratios[], int avgs[], int lines);
int avgOneMonth(int month, int data[][DATAPOINTS], int lines);

#endif  //_MONTHLY_H