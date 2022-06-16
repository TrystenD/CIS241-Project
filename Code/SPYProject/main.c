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

/** Month LUT */
char months[12][15] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"}; 

/** Function Prototypes */
void promptMenu(void);
int maxRatio(float ratio[]); // remove lines as arg
int minRatio(float ratio[]); 
int maxVolume(int volume[]);
int minVolume(int volume[]);
void displayMainMenu(void);
void displayMaxMenu(void);
void displayMinMenu(void);
float avgPutCallRatioByYear(char dates[][10], float ratios[], int year);
float avgPutCallRatioByMonth(char dates[][10], float ratios[], int month);

int main()
{
    int selection = 0;
    int selectYear;
    int selectMonth;

    int lines = 0;  // total lines in text file

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
        // Skips the first line in the text file
        fscanf(fp, "%*[^\n]\n");    
        while(fscanf(fp, "%[^,],%f,%d,%d,%d\n", date[lines], &ratio[lines], &putVolume[lines], &callVolume[lines], &totalVolume[lines]) != EOF){
            lines++; 
        }

        displayMainMenu();

        do {
            printf("\nPlease enter a selection: ");
            scanf("%d", &selection);

            if (selection > 0 && selection < 11)
            {
                // Call Functions
                switch(selection)
                {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    printf("--Average Put/Call Ratio by Month--\n");
                    for(int i = 0; i < 12; i++)
                        printf("%-15s\t\t%f\n", months[i], avgPutCallRatioByMonth(date, ratio, i + 1));
                    break;
                case 5:
                    printf("Enter the year you would like to calculate the average put/call ratio of: ");
                    scanf("%d", &selectYear);
                    printf("The average put/call ratio for 20%d was: %f", selectYear, avgPutCallRatioByYear(date, ratio, selectYear));
                    break;
                case 8:
                    // conclusions drawn from the data
                    //char netChangeText[1][9] = {""}; 

                    //(ratio[NUM_DATA_LINES-1] - ratio[0]) > 1 ? netChangeText[0] = "increase" : netChangeText = "decrease"; 
                    
                    //printf("Over the last decade, the SPY put/call ratio had a net %s of %.2f\n", netChangeText, ratio[NUM_DATA_LINES-1] - ratio[0]);

                    break;
                case 9:
                    displayMainMenu();
                    break;
                case 10:
                    printf("Thank you for playing!\n");
                    break;
                default:
                    break;
                }
            }
            else
            {
                printf("Invalid input!");
            }
        } while (selection != 9);

        printf("The minimum put/call ratio occured on %s at %0.2f\n", date[minRatio(ratio)], ratio[minRatio(ratio)]);
        printf("The maximum put/call ratio occured on %s at %0.2f\n", date[maxRatio(ratio)], ratio[maxRatio(ratio)]);
        printf("\nAverage Put/Call Ratio: %f\n\n", avgPutCallRatioByYear(date, ratio, 12));
    }

    return 0;
}

/** Function Definitions */

/**
 * @brief Displays the program's main menu.
 *
 * @return void
 */
void displayMainMenu(void) {
    printf("\nSPY Statistics Menu\n");
    printf("   (1) Maximum\n");
    printf("   (2) Minimum\n");
    printf("   (3) Average by All Months\n");
    printf("   (4) Average by Select Month\n");
    printf("   (5) Average by Select Year\n");
    printf("   (8) 2010-2019 Summary & Trends\n");
    printf("   (9) Redisplay Menu\n");
    printf("  (10) Quit\n");
}


/**
 * @brief Displays the find-maximum submenu.
 *
 * @return void
 */
void displayMaxMenu(void) {
    printf("\nFind Maximum Menu\n");
    printf("   (1) SPY Put Volume\n");
    printf("   (2) SPY Call Volume\n");
    printf("   (3) Total SPY Options Volume\n");
}


/**
 * @brief Displays the find-minimum submenu.
 *
 * @return void
 */
void displayMinMenu(void) {
    printf("\nFind Minimum Menu\n");
    printf("   (1) SPY Put Volume\n");
    printf("   (2) SPY Call Volume\n");
    printf("   (3) Total SPY Options Volume\n");
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

    // Go through all data and determine
    for(i = 0; i < NUM_DATA_LINES; i++)
    {
        strcpy(tempDate, dates[i]);     // Make copy of date string
        token = strtok(tempDate, "/");  // Tokenize to day (ignore)
        token = strtok(NULL, "/");      // Tokenize to month (ignore)
        token = strtok(NULL, "/");      // Token is year

        yearToken = atoi(token);        // Convert string year to int year

        // Add ratio to sum if year in file is same as selected year
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
float avgPutCallRatioByMonth(char dates[][10], float ratios[], int month)  {
    char *token;
    char tempDate[10];
    float ratioSum = 0;
    int monthToken,ratiosCnt = 0;

    for (int i = 0; i < NUM_DATA_LINES; i++) {
        strcpy(tempDate, dates[i]);
        token = strtok(tempDate, "/");

        monthToken = atoi(token);   // Convert string month to int month

        if (monthToken == month) {
            ratioSum += ratios[i];
            ratiosCnt++;
        }
    }

    return (ratioSum / ratiosCnt);
}

/**
 * @brief Finds index of maximum put/call volumes
 *
 * @param  int volume[]: array of put/call/total volumes
 * @param  int lines:    total number of dates
 * @return int maxIndex: index of maximum
 */
int maxVolume(int volume[]){
    int max = volume[0];
    int maxIndex = 0; 

    for(int i = 0; i < NUM_DATA_LINES; i++){
        if(volume[i] > max){
            max = volume[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

/**
 * @brief Finds index of minimum put/call volumes
 *
 * @param  int volume[]: array of put/call/total volumes
 * @param  int lines:    total number of dates
 * @return int minIndex: index of minimum
 */
int minVolume(int volume[]){
    int min = volume[0];
    int minIndex = 0; 

    for(int i = 0; i < NUM_DATA_LINES; i++){
        if(volume[i] < min){
            min = volume[i];
            minIndex = i;
        }
    }

    return minIndex;
}

/**
 * @brief Finds index of maximum put/call ratio
 *
 * @param  float volume[]: array of put/call/total ratio
 * @param  int lines:      total number of dates
 * @return int maxIndex: index of maximum
 */
int maxRatio(float ratio[]){
    float max = ratio[0]; 
    int maxIndex = 0;

    for(int i = 0; i < NUM_DATA_LINES; i++){
        if(ratio[i] > max){
            max = ratio[i]; 
            maxIndex = i;
        }
    }

    return maxIndex;
}

/**
 * @brief Finds index of minimum put/call ratio
 *
 * @param  float volume[]: array of put/call/total ratio
 * @param  int lines:      total number of dates
 * @return int minIndex: index of minimum
 */
int minRatio(float ratio[]){
    float min = ratio[0];
    int minIndex = 0; 

    for(int i = 0; i < NUM_DATA_LINES; i++){
        if(ratio[i] < min){
            min = ratio[i]; 
            minIndex = i;
        }
    }

    return minIndex;
  }

