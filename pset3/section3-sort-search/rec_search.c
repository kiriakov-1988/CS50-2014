/**
*  Повертає значення true, якщо значення value є в масиві
*  values, інакше - false.
*/

#include <stdio.h>
#include <cs50.h>

void search(int value, int values[], int start, int end);

int main(void)
{ 
    int v = 10;
    int end = 6;
    int vs[] = {2,4,5,7,9,10};
    
    
    search(v, vs, 0, end);
    
    // return x;
}

void search(int value, int values[], int start, int end)
{
        if (start > end)
        {
          printf ("false\n");
          // return false;
        }
        else
        {
        
            int middle = (start + end) / 2;
            
            if (value == values[middle])
            {
                printf ("true\n");
                // return true;
            }
            else if (value < values[middle])
            {
                
                search(value, values, start, middle - 1);
            }
            else
            { 
                search(value, values, middle + 1, end);
            }
        }

}
