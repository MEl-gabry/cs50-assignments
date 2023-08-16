#include <stdio.h>
#include <cs50.c>

    int main(void)   
    {  

       int current_pop;
       int end_pop;
       do
       {
         current_pop = get_int("Enter a starting population ");
       }
      while (current_pop < 9);
      do
       {
         end_pop = get_int("Enter an ending population ");
       }
      while (end_pop < current_pop);
      int years;
      for (years = 0; current_pop < end_pop; years++) 
      {
         current_pop = current_pop + (current_pop / 3) - (current_pop / 4);
      }
      printf("It would take %i years", years);
    }

