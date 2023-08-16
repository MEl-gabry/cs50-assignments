#include <ctype.h>
#include <cs50.c>
#include <stdio.h>
#include <string.h>
#include <math.h>

int letter_counter(string the_text);
int word_counter(string text);
int sentence_counter(string text);

int main(void)
{
    string text = get_string("", "Text: ");
    int letters = letter_counter(text);
    int words = word_counter(text);
    int sentences = sentence_counter(text);
    float wp = (float) words / 100;
    float index = 0.0588 * (letters / wp) - 0.296 * (sentences / wp) - 15.8;
    int grade = round(index);
    
    if (grade > 16)
    {
        printf("Grade 16+");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", grade);
    }

}

int letter_counter(string the_text)
{
    int letter_count = 0;
    for (int i = 0, length = strlen(the_text); i < length; i++)
    {
        char letter = the_text[i];
        if (isalpha(letter))
        {
            letter_count++;
        }
    }
    return letter_count;
}
int word_counter(string text)
{
    int word_count = 1;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char letter = text[i];
        if (letter == 32)
        {
            word_count++;
        }
    }
    return word_count;
}
int sentence_counter(string text)
{
    int sentence_count = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char letter = text[i];
        if (letter == 46 || letter == 63 || letter == 33)
        {
            sentence_count++;
        }
    }
    return sentence_count;
}


