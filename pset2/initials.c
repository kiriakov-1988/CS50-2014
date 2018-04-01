#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();
    
    int i = 0, n = strlen(name);

    while (name[i] == ' ')  // отсекаем пробелы вначале
    {
       i++;
    }
    
    while (name[n-1] == ' ') // отсекаем пробелы в конце
    {
       n--;
    }

    printf("%c", toupper(name[i]));
    
    for (; i < n; i++)
    {
        if (name[i] == ' ')
        {
            if (name[i+1] != ' ')
            {
                printf("%c", toupper(name[i+1]));
            }
        }
    }

    printf("\n");
    
}
