/**
 * @brief This program packs 4 char values into a
 *        four-byte unsigned int variable.
 *
 * @author Trysten Dembeck
 *
 * @file PackBits/main.c
 *
 * @note Assignmnet: HW4 Part 1
 *       Course:     CIS241-01
 *       Instructor: Prof. Bhuse
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

unsigned int packChars(char chars[]);
void printBits(unsigned int val);

int main()
{
    int i;                  // Incrementing variable
    int userChoice = 1;     // The user's decision to enter another value or exit program
    char chars[4];          // Array of 4 chars to pack together
    unsigned int packedVar; // The variable to pack the 4 chars into

    printf("*** Welcome to the Reverse Bits Program! ***\n");

    do
    {
        /** Get unsigned int value from user */
        printf("\n\nPlease enter 4 characters to pack together: ");
        scanf("%c%c%c%c", &chars[0], &chars[1], &chars[2], &chars[3]);

        /** Display unpacked and packed results */
        // Print binary equivalent of entered characters
        for(i = 0; i < 4; i++)
        {
            printf("'%c' in 32 bits is: ", chars[i]);
            printBits(chars[i]);
        }

        // Pack chars into variable
        packedVar = packChars(chars);

        // Show result
        printf("'%c' '%c' '%c' '%c' packed is: ", chars[0], chars[1], chars[2], chars[3]);
        printBits(packedVar);

        /** See if user wants to reverse another value's bits */
        printf("\nWould you like reverse another value (1-Yes/2-Quit)? ");
        scanf("%d", &userChoice);

        while(getchar() != '\n'); // Clear input buffer to accept another message

    }while(userChoice == 1);

    return 0;
}

/**
 * @brief Packs array of 4 chars into one unsigned int variable
 *        and returns it.
 *
 * @param char chars[]: Array of 4 chars to pack into one unsigned int.
 *
 * @return unsigned int packVar: The variable with 4 characters packed into it
 */
unsigned int packChars(char chars[])
{
    int i;                  // Incrementing variable
    unsigned int packVar;   // Variable to pack chars into

    // Pack chars into variable
    packVar = chars[0];
    for(i = 1; i < 4; i++)
    {
        packVar <<= 8;       // Shift packed var left 8 to open spot for next char
        packVar |= chars[i]; // Inclusive OR the bits of next char into front of packed var
    }

    return packVar;
}

/**
 * @brief Prints the value as its binary bit equivalent
 *
 * @param unsigned int val: The value to display as binary bits
 *
 * @return void
 */
void printBits(unsigned int val)
{
    unsigned int i;
    unsigned int mask = 1 << 31;

    for(i = 1; i <= 32; i++)
    {
        putchar(val & mask ? '1' : '0'); // Print 1 if bit pos is 1 or 0 if not
        val <<= 1;                       // Shift val over 1 to check next pos

        // Print a space after 8-bits are printed
        if(i % 8 == 0)
        {
            putchar(' ');
        }
    }
    putchar('\n');
}
