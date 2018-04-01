#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        printf("height: ");
        n = GetInt(); 
    }
    while (n < 0 || n > 23);
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < (n - i); j++)
        {
            printf(" ");
        }
        
        for (int k = n; k < (n + i); k++)
        {
            printf("#");
        }

        printf("#\n");
    }
}
