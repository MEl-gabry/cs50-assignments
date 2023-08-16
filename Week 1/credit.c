#include <stdio.h>
#include <cs50.c>

int main(void)
{
    long long credit = 4222222222222;
    long long credit_copy = credit;
    int digits = 0;
    int sum = 0;
    bool valid = false;
    do
    {
        credit_copy /= 10;
        digits++;
    } 
    while (credit_copy > 0);
    credit_copy = credit;
    for (int times = 1; times <= digits; times++)
    {
        if (times % 2 == 0)
        {
            int add = 2 * (credit_copy % 10);
            if (add >= 10)
            {
                do 
                {
                    sum += add % 10;
                    add /= 10;
                }
                while (add > 0);
            }
            else
            {
            sum += add;
            }
        }
        else
        {
            int add_odd = credit_copy % 10;
            sum += add_odd;
        }
        credit_copy /= 10;
    }
    if (sum % 10 == 0)
    {
        valid = true;
    }
    if (valid == true)
    {
        int starting_digits = 0;
        do 
        {
            credit /= 10;
        }
        while(credit >= 100);
        starting_digits += credit;
        if (digits == 16 && starting_digits / 10 == 5)
        {
            if (starting_digits == 51)
            {
                printf("MASTERCARD\n");
            }
            else if (starting_digits == 52)
            {
                printf("MASTERCARD\n");
            }
            else if (starting_digits == 53)
            {
                printf("MASTERCARD\n");
            }
            else if (starting_digits == 54)
            {
                printf("MASTERCARD\n");
            }
            else if (starting_digits == 55)
            {
                printf("MASTERCARD\n");
            }
        }
        else if (digits == 16 || digits == 13 && starting_digits / 10 == 4)
        {
            printf("VISA\n");
        }
        else if (digits == 15 && starting_digits / 10 == 3)
        {
            if (starting_digits == 34)
            {
                printf("AMERICAN EXPRESS\n");
            }
            else if (starting_digits == 37)
            {
                printf("AMERICAN EXPRESS\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}