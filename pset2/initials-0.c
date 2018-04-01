#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    string name = GetString();
      
    int s = 0, f = strlen(name) - 1;
    
    for (int i = 0; name[i] == ' '; i++)
    {
        s++;
    }
      
    for (int j = f; name[j] == ' '; j--)
    {
        f--;
    }
        
    printf("%c", toupper(name[s]));
        
    for (int k = s + 1; k < f; k++)
    {
        if (name[k-1] == ' ')
        {
            if (name[k] != ' ')
            {
                printf("%c", toupper(name[k]));
            }
        }
    }
    
    printf("\n");
    
}
