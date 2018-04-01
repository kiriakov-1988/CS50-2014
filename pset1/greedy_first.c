#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float f;
    
    // получаем сумму, которую надо выдать
    do
    {
        printf("How much change is owed?\n");
        f = GetFloat();
    }
    while (f < 0);

    // округляем число до целого
    f = 100 * f;
    f = (int) round(f);

    
    // считаем количество монеток
    int delivery = 0;
    int i;
    
    i = 25; // по 0.25
    while (i <= f)
    {
        f = f - i;
        delivery++;
    }

    i = 10; // по 0.10
    while (i <= f)
    {
        f = f - i;
        delivery++;
    }

    i = 5; // по 0.05
    while (i <= f)
    {
        f = f - i;
        delivery++;
    }

    i = 1; // по 0.01
    while (i <= f)
    {
        f = f - i;
        delivery++;
    }
    
    // выводим значение
    printf("%i\n", delivery);
}
