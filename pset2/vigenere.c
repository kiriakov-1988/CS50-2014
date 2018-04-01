#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere key\n");
        return 1;
    }
    
    string k = argv[1];
    int m = strlen(k);
        
    int key[m];
    
    for (int i = 0; i < m; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("Usage: ./vigenere key\n");
            return 1;
        }
        else
        {
            if (isupper(k[i]))
            {
                key[i] = (int)k[i] - 65;
            }
            else
            {
                key[i] = (int)k[i] - 97;
            }
        }
    }
    
    string p = GetString();
    
    int n = strlen(p);

    for (int i = 0, j = 0; i < n; i++)
    {
        if (isalpha(p[i]))
        {
                if ((islower(p[i]) && islower(p[i]+key[j])) || (isupper(p[i]) && isupper(p[i]+key[j])))
                {
                    printf("%c", p[i] + key[j]);
                }
                else 
                {
                    printf("%c", p[i] + key[j] - 26);
                }
            
                j++;
                
                j = j % m;
        }
        
        else // не буква
        {
            printf("%c", p[i]);
        }
        
    }
    
    printf("\n");
    
    return 0;
}
