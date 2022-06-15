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
 * @note Assignment: SPY Project
 *       Course:     CIS241-01
 *       Instructor: Prof. Bhuse
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2500


void promptMenu(void);
float avgPutCallRatioByYear(char dates[][10], float ratios[], int year);

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
        while(fscanf(fp, "%[^,],%f,%d,%d,%d\n", date[lines], &ratio[lines], &putVolume[lines], &callVolume[lines], &totalVolume[lines]) != EOF){
            printf("%s,%.2f,%d,%d,%d\n", date[lines], ratio[lines], putVolume[lines], callVolume[lines], totalVolume[lines]);
            lines++;
        }

        promptMenu();


    }

    return 0;
}


/**
 * @brief Prints a menu for the user to reference and select
 *        what information they want to see
 *
 * @param
 *       void
 * @return
 *       void
 */
void promptMenu(void) {
    char *spacer = "   ";
    int selection = 0;

    printf("--------------------------\n");
    printf("|%sSPY 10-Year Review%s|\n", spacer, spacer);
    printf("--------------------------\n");
    printf("  SPY Ratio\n", spacer);
    printf("%s(1) Maximum\n", spacer);
    printf("%s(2) Minimum\n", spacer);
    printf("%s(3) Average\n", spacer);

    do {
        printf("\nPlease enter a selection: ");
        scanf("%d", &selection);

        if (selection > 0 && selection < 4)
            break;
        else
            printf("Invalid input!");
    } while (1);
}
