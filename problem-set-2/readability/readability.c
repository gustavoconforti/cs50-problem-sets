#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float coleman_liau(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    // Call Coleman Liau algorithm function using other three functions as input and rounding final result to nearest integer
    int grade = round(coleman_liau(count_letters(text), count_words(text), count_sentences(text)));
    if (grade <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}

int count_letters(string text)
{
    int letter_count = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        // Check if current character is uppercase or lowercase letter
        if ((text[i] >= 'a' && text[i] <= 'z') || ((text[i] >= 'A' && text[i] <= 'Z')))
        {
            letter_count++;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int word_count = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        // Check if current character marks end of word
        if (text[i] == ' ' || text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            // Check if next character is not empty space
            if (text[i + 1] != ' ')
            {
                word_count++;
            }
        }
    }
    return word_count;
}

int count_sentences(string text)
{
    int sentence_count = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        // Check if current character marks end of sentence
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count++;
        }
    }
    return sentence_count;
}

float coleman_liau(int letters, int words, int sentences)
{
    // Calculate Coleman Liau algorithm maintaining decimal precision with type casting
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}