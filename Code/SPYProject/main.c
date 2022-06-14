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

void maximum(int volume[]);
void minimum(int volume[]); 



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

        while(fscanf(fp, "%[^,],%f,%d,%d,%d", date[lines], &ratio[lines], &putVolume[lines], &callVolume, &totalVolume[lines]) == 5){
            lines++;
            printf("%s,%f,%d,%d,%d\n", date[lines], ratio[lines], putVolume[lines], callVolume, totalVolume[lines]);
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

