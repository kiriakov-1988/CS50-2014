#include <stdio.h>
#include <cs50.h>

void sort(int array[], int n);

int step = 0;
int shag = 0;

int main(void)
{ 
    int arr[] = {4, 40, 2, 7, 10, 15, 1, 8, 4, 20, 30, 9, 3};
    int nn = 13; // 36 шагов и 77
    
    sort(arr, nn);
    
    for (int i = 0; i < nn; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n"); 
    printf("%i step\n", step); 
    printf("%i shag\n", shag); 
}

void sort(int array[], int n)
{
  //Циклічний прохід по масиву
  for(int k = 0; k < n - 1; k++)
  {
    //Оптимізація: перевірка на здійснення обмінів
    int swaps = 0;
    
    //обміняти сусідні елементи, якщо вони не впорядковані
        //Пройтися по масиву
        for (int j = 0; j < n - 1 - k; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                
                swaps++;
                
                step++;
            } 
            
            shag++;
        }

     if(!swaps)
      break;
  }
}
