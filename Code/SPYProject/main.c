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

int main()
{

    FILE *fp;

    if((fp = fopen("SPY241Project.txt", "r")) == NULL) // Open hardware.dat file for writing ("w")
    {
        puts("File could not be opened\n");
    }
    else
    {
        printf("File opened\n");
        // File was not opened
    }


    return 0;
}

/**
 * @brief
 *
 * @param
 * @return
 */

