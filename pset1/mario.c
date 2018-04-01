#include <cs50.h>
#include <stdio.h>

int main(void)
{
	int h;
	do
	{
		printf("height: ");
		h = GetInt();
	}
	while (h < 0 || h > 23);
	
	for (int i = 0; i < h; i++)
	{
		for (int j = h-i-1; j > 0; j--)
		{
			printf(" ");
		}
		
		for (int k = i; k > 0; k--)
		{
			printf("#");
		}
				
		printf("##\n");
	}
}
