#include <stdio.h>
#include <cs50.c>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int times = 1; times <= height; times++)
    {
        int space = height - times;
        for (int space_print = 0; space_print < space; space_print++)
        {
            printf(" ");
        }
        for (int hash = 0; hash < times; hash++)
        {
            printf("#");
        }    
        printf("  ");
        for (int hash = 0; hash < times; hash++)
        {
            printf("#");
        }   
        if (times != height)
        {   
            printf("\n");
        }

    }

}