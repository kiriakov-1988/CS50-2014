/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    
      // Встановити значення верхньої і нижньої межі пошуку
      int lower = 0;
      int upper = n - 1;
      
      while(lower <= upper)
      {
        // Що треба робити тут?
        int middle = (lower + upper) / 2;
        
        if (value == values[middle])
        {
            //printf ("true\n");
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
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
        
      //Циклічний прохід по масиву
      for(int k = 0; k < n - 1; k++)
      {
        //Оптимізація: перевірка на здійснення обмінів
        int swaps = 0;
        
        //обміняти сусідні елементи, якщо вони не впорядковані
            //Пройтися по масиву
            for (int j = 0; j < n - 1 - k; j++)
            {
                if (values[j] > values[j + 1])
                {
                    int temp = values[j];
                    values[j] = values[j + 1];
                    values[j + 1] = temp;
                    
                    swaps++;
                } 
            }

         if(!swaps)
          break;
      }
    
    return;
}
