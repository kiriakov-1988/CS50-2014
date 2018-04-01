#include <stdio.h>
#include <cs50.h>

void sort(int array[], int size);

int step = 0;
int shag = 0;

int main(void)
{ 
    int arr[] = {40, 4, 2, 7, 10, 15, 1, 8, 4, 20, 30, 9, 3};
    int nn = 13; // 37 шагов и 78
    
    sort(arr, nn);
    
    for (int i = 0; i < nn; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n"); 
    printf("%i step\n", step); 
    printf("%i shag\n", shag); 
}


void sort(int array[], int size)
{
    for (int i = 1; i < size; i++)
    {
        //Оптимізація: перевірка на здійснення обмінів
        int swaps = 0;
    
        // int element = array[i-1];
        for (int j = i; j > 0; j--)
        {
            if (array[j] < array[j-1])
            {
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
                
                swaps++;
                
                step++;
            }
            
            shag++;
        }
        
        if(!swaps)
         break;
        
    }
}
