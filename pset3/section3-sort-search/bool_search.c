/**
*  Повертає значення true, якщо значення value є в масиві
*  values, інакше - false.
*/

#include <stdio.h>
#include <cs50.h>

bool search(int value, int values[], int n);

int main(void)
{ 
    int v = 10;
    int nn = 6;
    int vs[] = {2,4,5,7,9,10};
    
    
    search(v, vs, nn);
    
    // return x;
}

bool search(int value, int values[], int n)
    {
      // Встановити значення верхньої і нижньої межі пошуку
      int lower = 0;
      int upper = n - 1;
      
      while(lower <= upper)
      {
        // Що треба робити тут?
        int middle = (lower + upper) / 2;
        
        if (value == values[middle])
        {
            printf ("true\n");
            return true;
        }
        else if (value < values[middle])
        {
            upper = middle - 1;
        }
        else
        { 
            lower = middle + 1;
        }
      }
      
      printf ("false\n");
      return false;
    }
 
