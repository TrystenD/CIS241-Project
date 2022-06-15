/**
 * @brief This program separates data and calculates the average
 *        put/call ratio per month of the year for a dataset.
 *
 * @author Isaiah Hendrick
 *
 * @file monthly.c
 *
 * @note Assignmnet: SPY Project
 *       Course:     CIS241-01
 *       Instructor: Prof. Bhuse
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MONTHS 12
#define DATAPOINTS 2


int *monthly(char *dates[],int ratios[],int lines)  {
    int data[lines][DATAPOINTS];
    int monthlyAvgs[MONTHS];
    char *token, *string;
    
    for (int i = 0; i < lines; i++) {
        strcpy(string,data[i]);
        token = strtok(string, "/");
        for (int j = 0; j < 2; j++)
            data[i][j] = j ? ratios[i] : (int)token;
    }

    for (int i = 0; i < MONTHS; i++)    {
        monthlyAvgs[i] = avgOneMonth(i,data,lines);
    }

    return monthlyAvgs;
}


int avgOneMonth(int month, int data[][DATAPOINTS], int lines)   {
    int ratioAvg = 0, numPts = 0;
    
    for (int i = 0; i < lines; i++) {
        if (data[i][0] == month)    {
            ratioAvg += data[i][1];
            numPts++;
        }
    }

    ratioAvg /= numPts;

    return ratioAvg;
}