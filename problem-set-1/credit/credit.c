#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Prompt for card number. Deal with negative numbers.
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);

    // Calculate length.
    int length;
    long numberCopy = number;
    for (length = 0; numberCopy; length++)
    {
        numberCopy /= 10;
    }

    // Invalidate number based length, according to the companies formats
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        exit(0);
    }

    // Store first digit.
    long firstDigit;
    numberCopy = number;
    for (int i = length - 1; i; i--)
    {
        numberCopy /= 10;
        firstDigit = numberCopy;
    }

    // Store first and second digits.
    long firstTwoDigits;
    numberCopy = number;
    for (int i = length - 2; i; i--)
    {
        numberCopy /= 10;
        firstTwoDigits = numberCopy;
    }

    // Invalidate number based on first and second digits, according to the companies formats
    if (firstDigit != 4 && firstTwoDigits != 34 && firstTwoDigits != 37 && (firstTwoDigits < 51 || firstTwoDigits > 55))
    {
        printf("INVALID\n");
        exit(0);
    }

    // Luhn's algorithm first step
    long luhnStep1 = 0;
    numberCopy = number;
    while (numberCopy)
    {
        // Skip digit once
        numberCopy /= 10;

        // Multiply every other digit by 2, starting at the second-to-last digit
        int luhnStep1_multiply = (numberCopy % 10) * 2;

        // Add digits of multiplication product
        int luhnStep1_add = 0;
        while (luhnStep1_multiply)
        {
            luhnStep1_add = luhnStep1_add + (luhnStep1_multiply % 10);
            luhnStep1_multiply /= 10;
        }

        // Add results of last sum
        luhnStep1 = luhnStep1 + luhnStep1_add;

        // Skip digit twice
        numberCopy /= 10;
    }

    // Luhn's algorithm second step
    long luhnStep2 = 0;
    numberCopy = number;
    while (numberCopy)
    {
        // Add digits that weren’t multiplied by 2
        luhnStep2 = luhnStep2 + (numberCopy % 10);

        // Skip a digit twice
        numberCopy /= 10;
        numberCopy /= 10;
    }

    // Luhn's algorithm last step
    long luhnStep3 = (luhnStep1 + luhnStep2) % 10;

    // Check Luhn's algorithm and validate number against companies formats
    if (luhnStep3 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // Check if AMEX. Has 15 digits and starts with 34 or 37
        if (length == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
        {
            printf("AMEX\n");
        }
        // Check if MASTERCARD. Has 16 digits, starts with 51, 52, 53, 54, or 55
        else if (length == 16 && (firstTwoDigits >= 51 && firstTwoDigits <= 55))
        {
            printf("MASTERCARD\n");
        }
        // Check if VISA. Has 13 or 16 digits, starts with 4
        else if ((length == 13 || length == 16) && firstDigit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}