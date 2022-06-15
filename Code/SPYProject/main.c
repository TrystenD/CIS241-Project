/**
 * @brief This program parses data from a data file
 *        containing SPY put call information and performs
 *        statistical calculations to make inferences
 *        on the state of the market.
 *
 * @author Trysten Dembeck
 *
 * @file main.c
 *
 * @note Assignmnet: SPY Project
 *       Course:     CIS241-01
 *       Instructor: Prof. Bhuse
 */

#include <stdio.h>
#include <stdlib.h>
#include "monthly.h"

#define SIZE 2500
#define MONTHS 12

void maximum(int volume[]);
void minimum(int volume[]);

int main()
{

    int lines = 0;  // total lines in text file is currently 2331

    char *date[SIZE];    
    float ratio[SIZE]; 
    int putVolume[SIZE]; 
    int callVolume[SIZE]; 
    int totalVolume[SIZE]; 

    int monthlyRatioAvg[MONTHS];

    FILE *fp;

    if((fp = fopen("SPY241Project.txt", "r")) == NULL) // Open SPY241Project.txt file for reading
    {
        puts("File could not be opened\n");
    }
    else
    {
        printf("File opened\n");
        // File was opened

        while(fscanf(fp, "%[^,],%f,%d,%d,%d", date[lines], &ratio[lines], &putVolume[lines], &callVolume[lines], &totalVolume[lines]) != EOF){
            printf("%s,%.2f,%d,%d,%d\n", date[lines], ratio[lines], putVolume[lines], callVolume[lines], totalVolume[lines]);
            lines++;
        }

    }


    return 0;
}

/**
 * @brief
 *
 * @param
 * @return
 */

