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
    
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("Usage: ./vigenere key\n");
            return 1;
        }
    }
    
    int m = strlen(k);
    
    string p = GetString();
    
    int j = 0;
    
    
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i]))
        {
            
                int key;
                
                if (isupper(k[j])) // проверка регистра буквы ключа
                {
                    key = k[j] - 65;
                }
                else
                {
                    key = k[j] - 97;
                }
                
                if ((islower(p[i]) && islower(p[i]+key)) || (isupper(p[i]) && isupper(p[i]+key)))
                {
                    printf("%c", p[i] + key);
                }
                else 
                {
                    printf("%c", p[i] + key - 26);
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
