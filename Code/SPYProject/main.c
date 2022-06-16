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

/*************************************************** Macros */
#define NUM_DATA_LINES 2330 // Total number of data lines in data text file

/*************************************************** LUTs */
char months[12][15] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

/*************************************************** Function Prototypes */
void promptMenu(void);
int maxRatio(float ratio[]);
int minRatio(float ratio[]);
int maxVolume(int volume[]);
int minVolume(int volume[]);
void displayMainMenu(void);
void displayMaxMenu(void);
void displayMinMenu(void);
float avgPutCallRatioByYear(char dates[][10], float ratios[], int year);
float avgPutCallRatioByMonth(char dates[][10], float ratios[], int month);

/*************************************************** Main Program Entry */
int main()
{
    int selection;                    // User's menu item selection
    int selectYear;                   // Month selected to view data for
    int selectMonth;                  // Year selected to view data for
    int lines = 0;                    // Data lines read in text file
    char dates[NUM_DATA_LINES][10];   // Dates column of data file
    float ratios[NUM_DATA_LINES];     // Put/Call ratios column of data file
    int putVolumes[NUM_DATA_LINES];   // Put volumes column of data file
    int callVolumes[NUM_DATA_LINES];  // Call volumes column of data file
    int totalVolumes[NUM_DATA_LINES]; // Total SPY options volyme (Puts + Calls)

    FILE *fp;                         // Pointer to data file

    if((fp = fopen("SPY241Project.txt", "r")) == NULL) // Attempt to open SPY241Project.txt file for reading
    {
        puts("File could not be opened\n");
    }
    else
    {
        fscanf(fp, "%*[^\n]\n");                       // Skips the first line in the text file
        while(fscanf(fp, "%[^,],%f,%d,%d,%d\n",        // Reads data lines from text file row by row
                     dates[lines],
                     &ratios[lines],
                     &putVolumes[lines],
                     &callVolumes[lines],
                     &totalVolumes[lines]) != EOF){
            lines++;                                   // Counts the # of data lines read for indexing
        }

        printf("****** Welcome to the 2010-2019 SPY Data Program! ******");

        do {
            displayMainMenu();
            printf("\nPlease enter a new selection: ");
            scanf("%d", &selection);

            if (selection >= 1 && selection <= 7)
            {
                switch(selection)
                {
                    // Max submenu
                    case 1:
                        displayMaxMenu();
                        printf("\nPlease enter a new selection: ");
                        scanf("%d", &selection);

                        // Handles maximum submenu
                        switch(selection)
                        {
                            case 1:
                                printf("\nThe maximum SPY put volume was seen on %s at %d.\n",
                                       dates[maxVolume(putVolumes)],
                                       putVolumes[maxVolume(putVolumes)]);
                                break;
                            case 2:
                                printf("\nThe maximum SPY call volume was seen on %s at %d.\n",
                                       dates[maxVolume(callVolumes)],
                                       callVolumes[maxVolume(callVolumes)]);
                                break;
                            case 3:
                                printf("\nThe maximum total SPY options volume was seen on %s at %d.\n",
                                       dates[maxVolume(totalVolumes)],
                                       totalVolumes[maxVolume(totalVolumes)]);
                                break;
                            case 4:
                                printf("\nThe maximum SPY put/call ratio volume on %s at %.2f.\n",
                                       dates[maxRatio(ratios)],
                                       ratios[maxRatio(ratios)]);
                                break;
                            default:
                                break;
                        }
                        break;
                    // Min submenu
                    case 2:
                        displayMinMenu();
                        printf("\nPlease enter a new selection: ");
                        scanf("%d", &selection);

                        // Handles minimum submenu
                        switch(selection)
                        {
                            case 1:
                                printf("\nThe minimum SPY put volume was seen on %s at %d.\n",
                                       dates[minVolume(putVolumes)],
                                       putVolumes[minVolume(putVolumes)]);
                                break;
                            case 2:
                                printf("\nThe minimum SPY call volume was seen on %s at %d.\n",
                                       dates[minVolume(callVolumes)],
                                       callVolumes[minVolume(callVolumes)]);
                                break;
                            case 3:
                                printf("\nThe minimum total SPY options volume was seen on %s at %d.\n",
                                       dates[minVolume(totalVolumes)],
                                       totalVolumes[minVolume(totalVolumes)]);
                                break;
                            case 4:
                                printf("\nThe minimum SPY put/call ratio volume on %s at %.2f.\n",
                                       dates[minRatio(ratios)],
                                       ratios[minRatio(ratios)]);
                                break;
                            default:
                                break;
                        }
                        break;
                    // Average put/call ratio over all months
                    case 3:
                        printf("\n--Average Put/Call Ratio by All Months--\n");
                        for(int i = 0; i < 12; i++)
                        {
                            printf("%-15s\t\t%f\n", months[i], avgPutCallRatioByMonth(dates, ratios, i + 1));
                        }
                        break;
                    // Average put/call ratio by select month
                    case 4:
                        printf("\nEnter the month you would like view the average put/call ratio of (1-12): ");
                        scanf("%d", &selectMonth);
                        printf("\nThe average put/call ratio for %s was: %f", months[selectMonth - 1],
                               avgPutCallRatioByMonth(dates, ratios, selectMonth));
                        break;
                    // Average put/call ratio by select year
                    case 5:
                        printf("\nEnter the year you would like to calculate the average put/call ratio of (10-19): ");
                        scanf("%d", &selectYear);
                        printf("\nThe average put/call ratio for 20%d was: %f", selectYear,
                               avgPutCallRatioByYear(dates, ratios, selectYear));
                        break;
                    // Conclusions drawn from the data on market
                    case 6:
                        break;
                    // Quit
                    case 7:
                        printf("\n\n\n****** Thank you for playing! ******\n\n\n");
                        break;
                    default:
                        break;
                } // End switch
            } // End if
            else
            {
                printf("Invalid input!");
            }
        } while (selection != 7);
    } // End else

    return 0;
}

/*************************************************** Function Definitions */

/**
 * @brief Displays the program's main menu.
 *
 * @return void
 */
void displayMainMenu(void) {
    printf("\n\n\nSPY Statistics Menu\n");
    printf("   (1) Maximum\n");
    printf("   (2) Minimum\n");
    printf("   (3) Average by All Months\n");
    printf("   (4) Average by Select Month\n");
    printf("   (5) Average by Select Year\n");
    printf("   (6) 2010-2019 Summary & Trends\n");
    printf("   (7) Quit\n");
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
    printf("   (4) Put/Call Ratio\n");
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
    printf("   (4) Put/Call Ratio\n");
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
 * @param  float volume[]: array of put/call ratios
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
 * @param  float ratio[]: array of put/call ratios
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

