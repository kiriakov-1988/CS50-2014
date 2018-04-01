#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    int k = atoi(argv[1]) % 26;
    
    string p = GetString();
    
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i]))
        {
            if ((islower(p[i]) && islower(p[i]+k)) || (isupper(p[i]) && isupper(p[i]+k)))
            {
                printf("%c", p[i] + k);
            }
            else 
            {
                printf("%c", p[i] + k - 26);
            }
        }
        else
        {
            printf("%c", p[i]);
        }
        
    }
    
    printf("\n");
    return 0;
}
