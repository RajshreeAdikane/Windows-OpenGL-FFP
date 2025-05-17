#include<stdio.h>

int main(void)
{
	printf("\n\n");
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; i <= 5; j++)
		{
			if (j > i)
			{
				break;
			}
			else
			{
				printf("* ");
			}
		}
		printf("\n");
	}
	printf("\n\n");
	return(0);
}