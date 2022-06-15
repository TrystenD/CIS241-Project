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

float avgPutCallRatioByYear(char dates[][10], float ratios[], int year);
int maximum(int volume[], int lines);
int minimum(int volume[], int lines);

int main()
{

    int lines = 0;  // total lines in text file is currently 2331

    char date[SIZE][10];
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

        fscanf(fp, "%*[^\n]\n");
        while(fscanf(fp, "%[^,],%f,%d,%d,%d\n", date[lines], &ratio[lines], &putVolume[lines], &callVolume[lines], &totalVolume[lines]) != EOF){
            //printf("%s,%.2f,%d,%d,%d\n", date[lines], ratio[lines], putVolume[lines], callVolume[lines], totalVolume[lines]);
            lines++;
        }

        printf("The minimum put volume is %d\n", putVolume[minimum(putVolume, lines)]);
        printf("The maximum put volume is %d\n", putVolume[maximum(putVolume, lines)]);
        printf("Average Put/Call Ratio: %f\n", avgPutCallRatioByYear(date, ratio, 12));

    }

    return 0;
}

/**
 * @brief Computes the average Put/Call ratio for a given year
 *        within the data provided in the data file.
 *
 * @param char dates[][10]: The parsed array of the date column
 * @param float ratios[]: The parsed array of the put/call ratio column
 * @param int year: The year (in yy format) to compute the avg put/call ratio in it
 *
 * @return void
 */
float avgPutCallRatioByYear(char dates[][10], float ratios[], int year)
{
    char tempDate[10];
    char *token;
    int i;
    int yearToken;
    float ratioSum = 0;
    int ratiosCnt = 0;

    for(i = 0; i < 2330; i++)
    {
        strcpy(tempDate, dates[i]);     // Make copy of date string
        token = strtok(tempDate, "/");  // Tokenize string until token is year
        token = strtok(NULL, "/");
        token = strtok(NULL, "/");

        yearToken = atoi(token);        // Convert string year to int year
        //printf("%d\n", yearToken);

        if(yearToken == year)
        {
            ratioSum += ratios[i];
            ratiosCnt++;
        }

    }

    return (ratioSum / ratiosCnt);

}

/**
 * @brief Finds index of maximum put/call volumes
 *
 * @param
 *       int volume[]: array of put/call/total volumes
 *       int lines:    total number of dates
 * @return
 *       int max: index of maximum
 */
int maximum(int volume[], int lines){
    int max = volume[0];

    for(int i = 0; i < lines; i++)
        if(volume[i] > max)
            max = i;

    return max;
}

/**
 * @brief Finds index of minimum put/call volumes
 *
 * @param
 *       int volume[]: array of put/call/total volumes
 *       int lines:    total number of dates
 * @return
 *       int min: index of minimum
 */
int minimum(int volume[], int lines){
    int min = volume[0];

    for(int i = 0; i < lines; i++)
        if(volume[i] < min)
            min = i;

    return min;
}
