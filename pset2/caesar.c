#include <cs50.h>
#include <stdio.h>
#include <string.h> // strlen
#include <ctype.h> // isalpha, islower, isupper
#include <stdlib.h> // atoi

int main(int argc, string argv[])
{
    if (argc != 2) // проверка на кол-во вводных
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    int k = atoi(argv[1]) % 26; // преобразуем ключ
    
    string p = GetString(); // получаем строку
    
    for (int i = 0, n = strlen(p); i < n; i++) // прогоняем по циклу каждый символ
    {
        if (isalpha(p[i]))  // проверка - буква ли это (A = 65, Z = 90, a = 97, z = 122)
        {
            if (isupper(p[i])) // Большая ?
            {
                if (isupper(p[i] + k)) // осталась Большой ?
                {
                    printf("%c", p[i] + k);
                }
                else   // выходит за рамки
                {
                    printf("%c", 65 + (p[i] + k - 91)); 
                }
            }
            
            if (islower(p[i])) // Маленькая ?
            {
                if (islower(p[i] + k)) // осталась Маленькой ?
                {
                    printf("%c", p[i] + k);
                }
                else   // выходит за рамки
                {
                    printf("%c", 97 + (p[i] + k - 123));
                }
            }
        }
        
        else // печатаем небуквы
        {
            printf("%c", p[i]); 
        }
    }
    
    printf("\n"); 
    
    return 0;
}
