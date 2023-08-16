#include <ctype.h>
#include <cs50.c>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string key = get_string("", "Key: ");
    for (int i = 0, length = strlen(key); i < length; i++)
    {
        if (isalpha(key[i]) == false)
        {
        printf("Enter the key.");
        return 1;
        }
    }
    if (strlen(key) != 26)
    {
        printf("String must contain 26 characters.");
        return 2;
    }
    string text = get_string("", "plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char letter = toupper(text[i]);
        if (isalpha(letter))
        {    for (int x = 0; x < 26; x++)
            {
                if (letter == x + 65)
                {
                    if (isupper(text[i]))
                    {    
                        printf("%c", toupper(key[x]));
                        break;
                    }
                    else 
                    {
                        printf("%c", tolower(key[x]));
                        break;
                    }
                }
            }
        }
        else 
        {
            printf("%c", letter);
        }
    }
}