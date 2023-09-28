#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for height. Limit height between 1 and 8.
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Loop as many times as the height
    for (int i = 1; i <= height; i++)
    {
        // Measure how many spaces need to be left blank on the left for the current row and print
        int blanks = height - i;
        for (int j = 0; j < blanks; j++)
        {
            printf(" ");
        }

        // Print the left side blocks of the current row
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Print the gap
        printf("  ");

        // Print the right side blocks of the current row
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}