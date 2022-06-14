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

#define SIZE 2500


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

    FILE *fp;

    if((fp = fopen("SPY241Project.txt", "r")) == NULL) // Open hardware.dat file for writing ("w")
    {
        puts("File could not be opened\n");
    }
    else
    {
        printf("File opened\n");
        // File was opened

        fscanf(fp, "%*[^\n]\n");
        while(fscanf(fp, "%[^,],%f,%d,%d,%d", date[lines], &ratio[lines], &putVolume[lines], &callVolume[lines], &totalVolume[lines]) != EOF){
            printf("%s,%.2f,%d,%d,%d\n", date[lines], ratio[lines], putVolume[lines], callVolume[lines], totalVolume[lines]);
            lines++;
        }

    }


    return 0;
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
