#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
	float n;
	do
	{
		printf("O hai! How much change is owed?\n");
		n = GetFloat();
	}
	while (n < 0);
	
	// printf("%i\n", (int)(round(n*100)));
	
	int cent = (int)(round(n*100));
	
	int count = 0;
	
	while (cent >= 25)
	{
		cent = cent - 25;
		count++;
	}
	
	while (cent >= 10)
	{
		cent = cent - 10;
		count++;
	}
	
	while (cent >= 5)
	{
		cent = cent - 5;
		count++;
	}
	
	while (cent >= 1)
	{
		cent = cent - 1;
		count++;
	}
	
	printf("%i\n", count);
}








