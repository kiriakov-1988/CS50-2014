#include <stdio.h>
#include <cs50.h>

void sort(int array[], int n);

int step = 0;
int shag = 0;

int main(void)
{ 
    int arr[] = {4, 40, 2, 7, 10, 15, 1, 8, 4, 20, 30, 9, 3};
    int nn = 13; // 36 шагов
    
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
    int sort_array[size];
    
    // сортируем пары
    for (int i = 0; i < size - 1; i = i + 2)
    {
        if (array[i] > array[i+1])
        {
            int temp = array[i];
            array[i] = array[i+1];
            array[i+1] = temp;
            
            step++; // замены
        }
        
        shag++;  // шаги
    }
    
    // объединяем   /// {4, 40, 2, 7, 10, 15, 1, 8, 4, 20, 30, 9, 3} ////// 4 40 2 7 10 15 1 8 4 20 9 30 3 
    
    for (int n = 2; n < size; n = 2 * n)
    {

            for (int j = 0, k = n, i = 0; i < 2 * n; i++)
            {
                if (array[j] <= array[k])
                {
                    sort_array[i] = array[j];
                    j++;
                    
                    step++; // замены
                }
                else if (array[j] > array[k])
                {
                    sort_array[i] = array[k];
                    k++;
                    
                    step++; // замены
                }
                
                shag++;  // шаги
            }

    }
    
    for (int i = 0; i < size; i++)
    {
        printf("%i ", sort_array[i]);
    }
    printf("\n");

    
}




// данный алгоритм еще требует доработки !!
