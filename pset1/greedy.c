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
	
	// округляем
	
	int cent = (int)(round(n*100));
	
	int count = 0;
	
	count = cent / 25;
	cent = cent % 25;
	
	count = count + cent / 10;
	cent = cent % 10;
	
	count = count + cent / 5;
	cent = cent % 5;
	
	count = count + cent / 1;

	
	printf("%i\n", count);
}
