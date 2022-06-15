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

#define NUM_DATA_LINES 2330


void promptMenu(void);
int maxRatio(float ratio[], int lines); 
int minRatio(float ratio[], int lines); 
int maxVolume(int volume[], int lines);
int minVolume(int volume[], int lines);

float avgPutCallRatioByYear(char dates[][10], float ratios[], int year);
float monthly(char dates[][10], float ratios[], int lines, int month);

int main()
{

    int lines = 0;  // total lines in text file is currently 2331

    char date[NUM_DATA_LINES][10];
    float ratio[NUM_DATA_LINES];
    int putVolume[NUM_DATA_LINES];
    int callVolume[NUM_DATA_LINES];
    int totalVolume[NUM_DATA_LINES];

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


        promptMenu();
        printf("The minimum put/call ratio was on %s at %0.2f\n", date[minRatio(ratio, lines)], ratio[minRatio(ratio, lines)]);
        printf("The maximum put/call ratio was on %s at %0.2f\n", date[maxRatio(ratio, lines)], ratio[maxRatio(ratio, lines)]);
        printf("\nAverage Put/Call Ratio: %f\n\n", avgPutCallRatioByYear(date, ratio, 12));

        printf("--Average Put/Call Ratio by Month--\n");
        printf("%-15s\t%f\n", "January:",monthly(date,ratio,lines,1));
        printf("%-15s\t%f\n", "February:",monthly(date,ratio,lines,2));
        printf("%-15s\t%f\n", "March:",monthly(date,ratio,lines,3));
        printf("%-15s\t%f\n", "April:",monthly(date,ratio,lines,4));
        printf("%-15s\t%f\n", "May:",monthly(date,ratio,lines,5));
        printf("%-15s\t%f\n", "June:",monthly(date,ratio,lines,6));
        printf("%-15s\t%f\n", "July:",monthly(date,ratio,lines,7));
        printf("%-15s\t%f\n", "August:",monthly(date,ratio,lines,8));
        printf("%-15s\t%f\n", "September:",monthly(date,ratio,lines,9));
        printf("%-15s\t%f\n", "October:",monthly(date,ratio,lines,10));
        printf("%-15s\t%f\n", "November:",monthly(date,ratio,lines,11));
        printf("%-15s\t%f\n", "December:",monthly(date,ratio,lines,12));



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

    for(i = 0; i < NUM_DATA_LINES; i++)
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
 * @brief Computes the average Put/Call ratio for a given month
 *        within the data provided in the data file.
 *
 * @param char dates[][10]: The parsed array of the date column
 * @param float ratios[]: The parsed array of the put/call ratio column
 * @param int month: The month to compute the avg put/call ratio in it
 *
 * @return float: average put/call ratio for month
 */
float monthly(char dates[][10], float ratios[], int lines, int month)  {
    char *token;
    char string[10];
    float ratioAvg = 0;
    int monthToken,numDates = 0;

    for (int i = 0; i < lines; i++) {
        strcpy(string,dates[i]);
        token = strtok(string, "/");
        monthToken = atoi(token);
        if (monthToken == month)    {
            ratioAvg += ratios[i];
            numDates++;
        }
    }

    return (ratioAvg/numDates);
}

/**
 * @brief Finds index of maximum put/call volumes
 * 
 * @param  int volume[]: array of put/call/total volumes
 * @param  int lines:    total number of dates
 * @return int max: index of maximum
 */
int maxVolume(int volume[], int lines){
    int max = volume[0];

    for(int i = 0; i < lines; i++)
        if(volume[i] > max)
            max = i;

    return max;
}

/**
 * @brief Finds index of minimum put/call volumes
 * 
 * @param  int volume[]: array of put/call/total volumes
 * @param  int lines:    total number of dates
 * @return int min: index of minimum
 */
int minVolume(int volume[], int lines){
    int min = volume[0];

    for(int i = 0; i < lines; i++)
        if(volume[i] < min)
            min = i;

    return min;
}

/**
 * @brief Finds index of maximum put/call ratio
 * 
 * @param  float volume[]: array of put/call/total ratio
 * @param  int lines:      total number of dates
 * @return int max: index of maximum
 */
int maxRatio(float ratio[], int lines){
    int max = (int)(100*ratio[0]);

    for(int i = 0; i < lines; i++)
        if((int)(100*ratio[i]) > max)
            max = i;

    return max;
}

/**
 * @brief Finds index of minimum put/call ratio
 * 
 * @param  float volume[]: array of put/call/total ratio
 * @param  int lines:      total number of dates
 * @return int min: index of minimum
 */
int minRatio(float ratio[], int lines){
    int min = (int)(100*ratio[0]);

    for(int i = 0; i < lines; i++)
        if((int)(100*ratio[i]) < min)
            min = i;

    return min;
}