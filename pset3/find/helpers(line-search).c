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
    for (int i = 0; i < n; i++)
    {
        if (value == values[i])
        {
            return true;
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
