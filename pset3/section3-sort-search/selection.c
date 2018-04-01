#include <stdio.h>
#include <cs50.h>

void sort(int array[], int size);

int step = 0;
int shag = 0;

int main(void)
{ 
    int arr[] = {40, 4, 2, 7, 10, 15, 1, 8, 4, 20, 30, 9, 3};
    int nn = 13; // 12 шагов и 78
    
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
	//Пройти по масиву
	for(int i = 0; i < size - 1; i++)
	{
		//Найменший елемент у відсортованій частині
		
		int smallest = array[i];
		int position = i;
		
		//Пройти по невідсортованій частині масиву
		for (int j = i + 1; j < size; j++)
		{
		    // Знайти наступний найменший елемент
		    if (array[j] < smallest)
		    {
		        smallest = array[j];
		        position = j;
		    }
		    shag++;
		}

		//Обміняти місцями
		int temp = array[i];
		array[i] = smallest;
		array[position] = temp;
		
		step++;
	}
}
