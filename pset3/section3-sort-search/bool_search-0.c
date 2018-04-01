/**
*  Повертає значення true, якщо значення value є в масиві
*  values, інакше - false.
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{ 
    int value = 100;
    int values[] = {2,4,5,7,9,10,12,15,20,30,45,64,99};
    int n = 13;
    
    // Встановити значення верхньої і нижньої межі пошуку
      int lower = 0;
      int upper = n - 1;
      
      int step = 0;
      
      while(lower <= upper)
      {
        // Що треба робити тут?
        int middle = (lower + upper) / 2;
        
        if (value == values[middle])
        {
            printf ("true - %i\n", step);
            return true;
        }
        else if (value < values[middle])
        {
            upper = middle - 1;
            printf ("%i _ %i\n", values[middle], middle);
        }
        else
        {
            lower = middle + 1;
            printf ("%i _ %i\n", values[middle], middle);
        }
        
        step++;
        
      }
      
      printf ("false - %i\n", step);
      return false;
}

